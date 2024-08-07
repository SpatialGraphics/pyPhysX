//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>

#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>

#include "py_utils.h"

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

namespace {
inline PxFilterFlags TypeAffinityIgnoreFilterShader(PxFilterObjectAttributes attributes0,
                                                    PxFilterData filterData0,
                                                    PxFilterObjectAttributes attributes1,
                                                    PxFilterData filterData1,
                                                    PxPairFlags& pairFlags,
                                                    const void* constantBlock,
                                                    PxU32 constantBlockSize) {
    if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1)) {
        pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
        return PxFilterFlag::eDEFAULT;
    }

    // if top 16 bits of word3 are different, the shapes will never collide
    // e.g. they are in different scenes
    if ((filterData0.word3 & 0xffff0000) != (filterData1.word3 & 0xffff0000)) {
        return PxFilterFlag::eKILL;
    }

    // if the lower 16 bits of word3 are the same (e.g. articulation id)
    // if word2 has a matching bit (e.g. door and frame both set the same bit)
    // the shapes will not collide (e.g. ignore collisions within each articulation)
    if ((filterData0.word2 & filterData1.word2) && ((filterData0.word3 & 0xffff) == (filterData1.word3 & 0xffff))) {
        return PxFilterFlag::eKILL;
    }

    // Otherwise, apply MuJoCo's collision model to word0 and word1
    if ((filterData0.word0 & filterData1.word1) || (filterData1.word0 & filterData0.word1)) {
        pairFlags = PxPairFlag::eCONTACT_DEFAULT | PxPairFlag::eNOTIFY_CONTACT_POINTS |
                    PxPairFlag::eNOTIFY_TOUCH_PERSISTS | PxPairFlag::eNOTIFY_TOUCH_FOUND |
                    PxPairFlag::eNOTIFY_TOUCH_LOST | PxPairFlag::ePRE_SOLVER_VELOCITY |
                    PxPairFlag::ePOST_SOLVER_VELOCITY | PxPairFlag::eDETECT_CCD_CONTACT;

        return PxFilterFlag::eDEFAULT;
    }
    return PxFilterFlag::eKILL;
}

inline PxFilterFlags TypeAffinityIgnoreFilterShaderGpu(PxFilterObjectAttributes attributes0,
                                                       PxFilterData filterData0,
                                                       PxFilterObjectAttributes attributes1,
                                                       PxFilterData filterData1,
                                                       PxPairFlags& pairFlags,
                                                       const void* constantBlock,
                                                       PxU32 constantBlockSize) {
    if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1)) {
        pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
        return PxFilterFlag::eDEFAULT;
    }

    // if top 16 bits of word3 are different, the shapes will never collide
    // e.g. they are in different scenes
    if ((filterData0.word3 & 0xffff0000) != (filterData1.word3 & 0xffff0000)) {
        return PxFilterFlag::eKILL;
    }

    // if the lower 16 bits of word3 are the same (e.g. articulation id)
    // if word2 has a matching bit (e.g. door and frame both set the same bit)
    // the shapes will not collide (e.g. ignore collisions within each articulation)
    if ((filterData0.word2 & filterData1.word2) && ((filterData0.word3 & 0xffff) == (filterData1.word3 & 0xffff))) {
        return PxFilterFlag::eKILL;
    }

    // Otherwise, apply MuJoCo's collision model to word0 and word1
    if ((filterData0.word0 & filterData1.word1) || (filterData1.word0 & filterData0.word1)) {
        pairFlags = PxPairFlag::eCONTACT_DEFAULT;
        return PxFilterFlag::eDEFAULT;
    }
    return PxFilterFlag::eKILL;
}
}  // namespace

void bindScene(nb::module_& m) {
    nb::enum_<PxFrictionType::Enum>(m, "PxFrictionType").value("ePATCH", PxFrictionType::Enum::ePATCH);
    nb::enum_<PxSolverType::Enum>(m, "PxSolverType")
            .value("ePGS", PxSolverType::Enum::ePGS)
            .value("eTGS", PxSolverType::Enum::eTGS);

    nb::enum_<PxBroadPhaseType::Enum>(m, "PxBroadPhaseType")
            .value("eSAP", PxBroadPhaseType::Enum::eSAP)
            .value("eMBP", PxBroadPhaseType::Enum::eMBP)
            .value("eABP", PxBroadPhaseType::Enum::eABP)
            .value("ePABP", PxBroadPhaseType::Enum::ePABP)
            .value("eGPU", PxBroadPhaseType::Enum::eGPU);

    nb::enum_<PxActorTypeFlag::Enum>(m, "PxActorTypeFlag")
            .value("eRIGID_STATIC", PxActorTypeFlag::Enum::eRIGID_STATIC)
            .value("eRIGID_DYNAMIC", PxActorTypeFlag::Enum::eRIGID_DYNAMIC);
    bindFlags<PxActorTypeFlag::Enum, PxU16>(m, "PxActorTypeFlags");

    nb::enum_<PxHitFlag::Enum>(m, "PxHitFlag")
            .value("ePOSITION", PxHitFlag::Enum::ePOSITION)
            .value("eNORMAL", PxHitFlag::Enum::eNORMAL)
            .value("eUV", PxHitFlag::Enum::eUV)
            .value("eASSUME_NO_INITIAL_OVERLAP", PxHitFlag::Enum::eASSUME_NO_INITIAL_OVERLAP)
            .value("eANY_HIT", PxHitFlag::Enum::eANY_HIT)
            .value("eMESH_MULTIPLE", PxHitFlag::Enum::eMESH_MULTIPLE)
            .value("eMESH_ANY", PxHitFlag::Enum::eMESH_ANY)
            .value("eMESH_BOTH_SIDES", PxHitFlag::Enum::eMESH_BOTH_SIDES)
            .value("ePRECISE_SWEEP", PxHitFlag::Enum::ePRECISE_SWEEP)
            .value("eMTD", PxHitFlag::Enum::eMTD)
            .value("eFACE_INDEX", PxHitFlag::Enum::eFACE_INDEX)
            .value("eDEFAULT", PxHitFlag::Enum::eDEFAULT);
    bindFlags<PxHitFlag::Enum, PxU16>(m, "PxHitFlags");

    nb::enum_<PxQueryFlag::Enum>(m, "PxQueryFlag")
            .value("eSTATIC", PxQueryFlag::Enum::eSTATIC)
            .value("eDYNAMIC", PxQueryFlag::Enum::eDYNAMIC)
            .value("ePREFILTER", PxQueryFlag::Enum::ePREFILTER)
            .value("ePOSTFILTER", PxQueryFlag::Enum::ePOSTFILTER)
            .value("eANY_HIT", PxQueryFlag::Enum::eANY_HIT)
            .value("eNO_BLOCK", PxQueryFlag::Enum::eNO_BLOCK)
            .value("eBATCH_QUERY_LEGACY_BEHAVIOUR", PxQueryFlag::Enum::eBATCH_QUERY_LEGACY_BEHAVIOUR)
            .value("eDISABLE_HARDCODED_FILTER", PxQueryFlag::Enum::eDISABLE_HARDCODED_FILTER);
    bindFlags<PxQueryFlag::Enum, PxU16>(m, "PxQueryFlags");

    nb::enum_<PxQueryHitType::Enum>(m, "PxQueryHitType")
            .value("eNONE", PxQueryHitType::Enum::eNONE)
            .value("eBLOCK", PxQueryHitType::Enum::eBLOCK)
            .value("eTOUCH", PxQueryHitType::Enum::eTOUCH);

    nb::enum_<PxSceneQueryUpdateMode::Enum>(m, "PxSceneQueryUpdateMode")
            .value("eBUILD_ENABLED_COMMIT_ENABLED", PxSceneQueryUpdateMode::Enum::eBUILD_ENABLED_COMMIT_ENABLED)
            .value("eBUILD_ENABLED_COMMIT_DISABLED", PxSceneQueryUpdateMode::Enum::eBUILD_ENABLED_COMMIT_DISABLED)
            .value("eBUILD_DISABLED_COMMIT_DISABLED", PxSceneQueryUpdateMode::Enum::eBUILD_DISABLED_COMMIT_DISABLED);

    nb::enum_<PxPruningStructureType::Enum>(m, "PxPruningStructureType")
            .value("eNONE", PxPruningStructureType::Enum::eNONE)
            .value("eDYNAMIC_AABB_TREE", PxPruningStructureType::Enum::eDYNAMIC_AABB_TREE)
            .value("eSTATIC_AABB_TREE", PxPruningStructureType::Enum::eSTATIC_AABB_TREE);

    nb::enum_<PxParticleSolverType::Enum>(m, "PxParticleSolverType").value("eNONE", PxParticleSolverType::Enum::ePBD);

    nb::enum_<PxSceneFlag::Enum>(m, "PxSceneFlag")
            .value("eENABLE_ACTIVE_ACTORS ", PxSceneFlag::Enum::eENABLE_ACTIVE_ACTORS)
            .value("eENABLE_CCD", PxSceneFlag::Enum::eENABLE_CCD)
            .value("eDISABLE_CCD_RESWEEP", PxSceneFlag::Enum::eDISABLE_CCD_RESWEEP)
            .value("eENABLE_PCM", PxSceneFlag::Enum::eENABLE_PCM)
            .value("eDISABLE_CONTACT_REPORT_BUFFER_RESIZE", PxSceneFlag::Enum::eDISABLE_CONTACT_REPORT_BUFFER_RESIZE)
            .value("eDISABLE_CONTACT_CACHE", PxSceneFlag::Enum::eDISABLE_CONTACT_CACHE)
            .value("eREQUIRE_RW_LOCK", PxSceneFlag::Enum::eREQUIRE_RW_LOCK)
            .value("eENABLE_STABILIZATION", PxSceneFlag::Enum::eENABLE_STABILIZATION)
            .value("eENABLE_AVERAGE_POINT", PxSceneFlag::Enum::eENABLE_AVERAGE_POINT)
            .value("eEXCLUDE_KINEMATICS_FROM_ACTIVE_ACTORS", PxSceneFlag::Enum::eEXCLUDE_KINEMATICS_FROM_ACTIVE_ACTORS)
            .value("eENABLE_GPU_DYNAMICS", PxSceneFlag::Enum::eENABLE_GPU_DYNAMICS)
            .value("eENABLE_ENHANCED_DETERMINISM", PxSceneFlag::Enum::eENABLE_ENHANCED_DETERMINISM)
            .value("eENABLE_FRICTION_EVERY_ITERATION", PxSceneFlag::Enum::eENABLE_FRICTION_EVERY_ITERATION)
            .value("eENABLE_EXTERNAL_FORCES_EVERY_ITERATION_TGS",
                   PxSceneFlag::Enum::eENABLE_EXTERNAL_FORCES_EVERY_ITERATION_TGS)
            .value("eENABLE_DIRECT_GPU_API", PxSceneFlag::Enum::eENABLE_DIRECT_GPU_API)
            .value("eENABLE_BODY_ACCELERATIONS", PxSceneFlag::Enum::eENABLE_BODY_ACCELERATIONS)
            .value("eENABLE_SOLVER_RESIDUAL_REPORTING", PxSceneFlag::Enum::eENABLE_SOLVER_RESIDUAL_REPORTING);
    bindFlags<PxSceneFlag::Enum, PxU32>(m, "PxSceneFlags");

    nb::class_<PxSceneDesc>(m, "PxSceneDesc")
            .def(nb::init<PxTolerancesScale>())
            .def("setToDefault", &PxSceneDesc::setToDefault)
            .def("isValid", &PxSceneDesc::isValid)
            .def("getTolerancesScale", &PxSceneDesc::getTolerancesScale, nb::rv_policy::reference)
            .def("setFilterShaderCPU",
                 [](PxSceneDesc* desc) {
                     desc->filterShader = TypeAffinityIgnoreFilterShader;
                 })
            .def("setFilterShaderGPU",
                 [](PxSceneDesc* desc) {
                     desc->filterShader = TypeAffinityIgnoreFilterShaderGpu;
                 })
            .def_rw("gravity", &PxSceneDesc::gravity)
            .def_rw("simulationEventCallback", &PxSceneDesc::simulationEventCallback)
            .def_rw("contactModifyCallback", &PxSceneDesc::contactModifyCallback)
            .def_rw("ccdContactModifyCallback", &PxSceneDesc::ccdContactModifyCallback)
            .def_rw("filterShaderDataSize", &PxSceneDesc::filterShaderDataSize)
            .def_rw("filterCallback", &PxSceneDesc::filterCallback)
            .def_rw("kineKineFilteringMode", &PxSceneDesc::kineKineFilteringMode)
            .def_rw("staticKineFilteringMode", &PxSceneDesc::staticKineFilteringMode)
            .def_rw("broadPhaseType", &PxSceneDesc::broadPhaseType)
            .def_rw("broadPhaseCallback", &PxSceneDesc::broadPhaseCallback)
            .def_rw("limits", &PxSceneDesc::limits)
            .def_rw("frictionType", &PxSceneDesc::frictionType)
            .def_rw("solverType", &PxSceneDesc::solverType)
            .def_rw("bounceThresholdVelocity", &PxSceneDesc::bounceThresholdVelocity)
            .def_rw("frictionOffsetThreshold", &PxSceneDesc::frictionOffsetThreshold)
            .def_rw("frictionCorrelationDistance", &PxSceneDesc::frictionCorrelationDistance)
            .def_rw("cpuDispatcher", &PxSceneDesc::cpuDispatcher)
#ifdef SUPPORT_CUDA
            .def_rw("cudaContextManager", &PxSceneDesc::cudaContextManager)
#endif
            .def_rw("solverBatchSize", &PxSceneDesc::solverBatchSize)
            .def_rw("solverArticulationBatchSize", &PxSceneDesc::solverArticulationBatchSize)
            .def_rw("nbContactDataBlocks", &PxSceneDesc::nbContactDataBlocks)
            .def_rw("maxNbContactDataBlocks", &PxSceneDesc::maxNbContactDataBlocks)
            .def_rw("maxBiasCoefficient", &PxSceneDesc::maxBiasCoefficient)
            .def_rw("contactReportStreamBufferSize", &PxSceneDesc::contactReportStreamBufferSize)
            .def_rw("ccdMaxPasses", &PxSceneDesc::ccdMaxPasses)
            .def_rw("ccdThreshold", &PxSceneDesc::ccdThreshold)
            .def_rw("ccdMaxSeparation", &PxSceneDesc::ccdMaxSeparation)
            .def_rw("wakeCounterResetValue", &PxSceneDesc::wakeCounterResetValue)
            .def_rw("sanityBounds", &PxSceneDesc::sanityBounds)
            .def_rw("gpuDynamicsConfig", &PxSceneDesc::gpuDynamicsConfig)
            .def_rw("gpuMaxNumPartitions", &PxSceneDesc::gpuMaxNumPartitions)
            .def_rw("gpuMaxNumStaticPartitions", &PxSceneDesc::gpuMaxNumStaticPartitions)
            .def_rw("gpuComputeVersion", &PxSceneDesc::gpuComputeVersion)
            .def_rw("contactPairSlabSize", &PxSceneDesc::contactPairSlabSize)
            .def_rw("sceneQuerySystem", &PxSceneDesc::sceneQuerySystem);
    nb::class_<PxSceneLimits>(m, "PxSceneLimits")
            .def(nb::init<>())
            .def("setToDefault", &PxSceneLimits::setToDefault)
            .def("isValid", &PxSceneLimits::isValid)
            .def_rw("maxNbActors", &PxSceneLimits::maxNbActors)
            .def_rw("maxNbBodies", &PxSceneLimits::maxNbBodies)
            .def_rw("maxNbStaticShapes", &PxSceneLimits::maxNbStaticShapes)
            .def_rw("maxNbDynamicShapes", &PxSceneLimits::maxNbDynamicShapes)
            .def_rw("maxNbAggregates", &PxSceneLimits::maxNbAggregates)
            .def_rw("maxNbConstraints", &PxSceneLimits::maxNbConstraints)
            .def_rw("maxNbRegions", &PxSceneLimits::maxNbRegions)
            .def_rw("maxNbBroadPhaseOverlaps", &PxSceneLimits::maxNbBroadPhaseOverlaps);
    nb::class_<PxGpuDynamicsMemoryConfig>(m, "PxGpuDynamicsMemoryConfig")
            .def(nb::init<>())
            .def("isValid", &PxGpuDynamicsMemoryConfig::isValid)
            .def_rw("tempBufferCapacity", &PxGpuDynamicsMemoryConfig::tempBufferCapacity)
            .def_rw("maxRigidContactCount", &PxGpuDynamicsMemoryConfig::maxRigidContactCount)
            .def_rw("maxRigidPatchCount", &PxGpuDynamicsMemoryConfig::maxRigidPatchCount)
            .def_rw("heapCapacity", &PxGpuDynamicsMemoryConfig::heapCapacity)
            .def_rw("foundLostPairsCapacity", &PxGpuDynamicsMemoryConfig::foundLostPairsCapacity)
            .def_rw("foundLostAggregatePairsCapacity", &PxGpuDynamicsMemoryConfig::foundLostAggregatePairsCapacity)
            .def_rw("totalAggregatePairsCapacity", &PxGpuDynamicsMemoryConfig::totalAggregatePairsCapacity)
            .def_rw("maxSoftBodyContacts", &PxGpuDynamicsMemoryConfig::maxSoftBodyContacts)
            .def_rw("maxFemClothContacts", &PxGpuDynamicsMemoryConfig::maxFemClothContacts)
            .def_rw("maxParticleContacts", &PxGpuDynamicsMemoryConfig::maxParticleContacts)
            .def_rw("collisionStackSize", &PxGpuDynamicsMemoryConfig::collisionStackSize)
            .def_rw("maxHairContacts", &PxGpuDynamicsMemoryConfig::maxHairContacts);

    nb::class_<PxScene>(m, "PxScene")
            .def("release", &PxScene::release)
            .def("setFlag", &PxScene::setFlag, "flag"_a, "value"_a)
            .def("getFlags", &PxScene::getFlags)
            .def_prop_rw("limits", &PxScene::getLimits, &PxScene::setLimits)
            .def("getPhysics", &PxScene::getPhysics, nb::rv_policy::reference)
            .def("getTimestamp", &PxScene::getTimestamp)
            .def_prop_rw("name", &PxScene::getName, &PxScene::setName)
            .def("addArticulation", &PxScene::addArticulation, "articulation"_a)
            .def("removeArticulation", &PxScene::removeArticulation, "articulation"_a, "wakeOnLostTouch"_a = true)
            .def(
                    "addActor",
                    [](PxScene* scene, PxActor& actor) {
                        return scene->addActor(actor);
                    },
                    "actor"_a)
            .def(
                    "addActors",
                    [](PxScene* scene, std::vector<PxActor*> actors) {
                        scene->addActors(actors.data(), actors.size());
                    },
                    "actors"_a)
            .def("removeActor", &PxScene::removeActor, "actor"_a, "wakeOnLostTouch"_a = true)
            .def(
                    "removeActors",
                    [](PxScene* scene, std::vector<PxActor*> actors, bool wakeOnLostTouch) {
                        scene->removeActors(actors.data(), actors.size(), wakeOnLostTouch);
                    },
                    "actors"_a, "wakeOnLostTouch"_a = true)
            .def("addAggregate", &PxScene::addAggregate, "aggregate"_a)
            .def("removeAggregate", &PxScene::removeAggregate, "aggregate"_a, "wakeOnLostTouch"_a = true)
            //            .def("addCollection", &PxScene::addCollection)
            .def("getNbActors", &PxScene::getNbActors)
            .def("getNbSoftBodies", &PxScene::getNbSoftBodies)
            .def("getNbParticleSystems", &PxScene::getNbParticleSystems, "type"_a)
            .def("getNbPBDParticleSystems", &PxScene::getNbPBDParticleSystems)
            .def("getNbFEMCloths", &PxScene::getNbFEMCloths)
            .def("getNbHairSystems", &PxScene::getNbHairSystems)
            .def("getNbArticulations", &PxScene::getNbArticulations)
            .def("getNbConstraints", &PxScene::getNbConstraints)
            .def("getNbAggregates", &PxScene::getNbAggregates);

    nb::class_<PxSceneQuerySystemBase>(m, "PxSceneQuerySystemBase")
            .def_prop_rw("dynamicTreeRebuildRateHint", &PxSceneQuerySystemBase::getDynamicTreeRebuildRateHint,
                         &PxSceneQuerySystemBase::setDynamicTreeRebuildRateHint)
            .def("forceRebuildDynamicTree", &PxSceneQuerySystemBase::forceRebuildDynamicTree, "prunerIndex"_a)
            .def_prop_rw("updateMode", &PxSceneQuerySystemBase::getUpdateMode, &PxSceneQuerySystemBase::setUpdateMode)
            .def("getStaticTimestamp", &PxSceneQuerySystemBase::getStaticTimestamp)
            .def("flushUpdates", &PxSceneQuerySystemBase::flushUpdates);
    //            .def("raycast", &PxSceneQuerySystemBase::raycast)
    //            .def("sweep", &PxSceneQuerySystemBase::sweep)
    //            .def("overlap", &PxSceneQuerySystemBase::overlap);
    nb::class_<PxSceneSQSystem, PxSceneQuerySystemBase>(m, "PxSceneSQSystem")
            .def_prop_rw("sceneQueryUpdateMode", &PxSceneSQSystem::getSceneQueryUpdateMode,
                         &PxSceneSQSystem::setSceneQueryUpdateMode)
            .def("getSceneQueryStaticTimestamp", &PxSceneSQSystem::getSceneQueryStaticTimestamp)
            .def("flushQueryUpdates", &PxSceneSQSystem::flushQueryUpdates)
            .def("forceDynamicTreeRebuild", &PxSceneSQSystem::forceDynamicTreeRebuild, "rebuildStaticStructure"_a,
                 "rebuildDynamicStructure"_a)
            .def("getStaticStructure", &PxSceneSQSystem::getStaticStructure)
            .def("getDynamicStructure", &PxSceneSQSystem::getDynamicStructure)
            //            .def("sceneQueriesUpdate", &PxSceneSQSystem::sceneQueriesUpdate)
            .def("checkQueries", &PxSceneSQSystem::checkQueries, "block"_a = false)
            .def("fetchQueries", &PxSceneSQSystem::fetchQueries, "block"_a = false);
    nb::class_<PxSceneQuerySystem, PxSceneQuerySystemBase>(m, "PxSceneQuerySystem")
            .def("release", &PxSceneQuerySystem::release)
            .def("acquireReference", &PxSceneQuerySystem::acquireReference)
            .def("preallocate", &PxSceneQuerySystem::preallocate, "prunerIndex"_a, "nbShapes"_a)
            .def("flushMemory", &PxSceneQuerySystem::flushMemory)
            .def("addSQShape", &PxSceneQuerySystem::addSQShape, "actor"_a, "shape"_a, "bounds"_a, "transform"_a,
                 "compoundHandle"_a.none() = nb::none(), "hasPruningStructure"_a = false)
            .def("removeSQShape", &PxSceneQuerySystem::removeSQShape, "actor"_a, "shape"_a)
            .def("updateSQShape", &PxSceneQuerySystem::updateSQShape, "actor"_a, "shape"_a, "transform"_a)
            //            .def("addSQCompound", &PxSceneQuerySystem::addSQCompound)
            .def("removeSQCompound", &PxSceneQuerySystem::removeSQCompound, "compoundHandle"_a)
            .def("updateSQCompound", &PxSceneQuerySystem::updateSQCompound, "compoundHandle"_a, "compoundTransform"_a)
            .def("shiftOrigin", &PxSceneQuerySystem::shiftOrigin, "shift"_a)
            //            .def("visualize", &PxSceneQuerySystem::visualize)
            .def("merge", &PxSceneQuerySystem::merge, "pruningStructure"_a)
            .def("getHandle", &PxSceneQuerySystem::getHandle, "actor"_a, "shape"_a, "prunerIndex"_a)
            //            .def("sync", &PxSceneQuerySystem::sync)
            .def("finalizeUpdates", &PxSceneQuerySystem::finalizeUpdates);
    //            .def("prepareSceneQueryBuildStep", &PxSceneQuerySystem::prepareSceneQueryBuildStep)
    //            .def("sceneQueryBuildStep", &PxSceneQuerySystem::sceneQueryBuildStep);

    nb::class_<PxPruningStructure>(m, "PxPruningStructure")
            .def("release", &PxPruningStructure::release)
            .def("getNbRigidActors", &PxPruningStructure::getNbRigidActors);

    m.def(
            "PxDefaultCpuDispatcherCreate",
            [](PxU32 numThreads) {
                return PxDefaultCpuDispatcherCreate(numThreads);
            },
            nb::rv_policy::reference);
    nb::class_<PxCpuDispatcher>(m, "PxCpuDispatcher").def("getWorkerCount", &PxCpuDispatcher::getWorkerCount);
    nb::class_<PxDefaultCpuDispatcher, PxCpuDispatcher>(m, "PxDefaultCpuDispatcher")
            .def_prop_rw("runProfiled", &PxDefaultCpuDispatcher::getRunProfiled,
                         &PxDefaultCpuDispatcher::setRunProfiled);

    class SimulationEventCallback : public PxSimulationEventCallback {
    public:
        void onAdvance(const PxRigidBody* const* bodyBuffer,
                       const PxTransform* poseBuffer,
                       const PxU32 count) override {}
        void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) override {}
        void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) override {}
        void onSleep(physx::PxActor** actors, PxU32 count) override {}
        void onTrigger(physx::PxTriggerPair* pairs, PxU32 count) override {}
        void onWake(physx::PxActor** actors, PxU32 count) override {}
    };
    nb::class_<PxSimulationEventCallback> pxSimulationEventCallback(m, "PxSimulationEventCallback");
    nb::class_<SimulationEventCallback, PxSimulationEventCallback> simulationEventCallback(m,
                                                                                           "SimulationEventCallback");

    class ContactModifyCallback : public PxContactModifyCallback {
    public:
        void onContactModify(physx::PxContactModifyPair* const pairs, physx::PxU32 count) override {}
    };
    nb::class_<PxContactModifyCallback> pxContactModifyCallback(m, "PxContactModifyCallback");
    nb::class_<ContactModifyCallback, PxContactModifyCallback> contactModifyCallback(m, "ContactModifyCallback");

    class CCDContactModifyCallback : public PxCCDContactModifyCallback {
    public:
        void onCCDContactModify(physx::PxContactModifyPair* const pairs, physx::PxU32 count) override {}
    };
    nb::class_<PxCCDContactModifyCallback> pxCCDContactModifyCallback(m, "PxCCDContactModifyCallback");
    nb::class_<CCDContactModifyCallback, PxCCDContactModifyCallback> cCDContactModifyCallback(
            m, "CCDContactModifyCallback");

    class BroadPhaseCallback : public PxBroadPhaseCallback {
    public:
        void onObjectOutOfBounds(physx::PxAggregate& aggregate) override {}
        void onObjectOutOfBounds(physx::PxShape& shape, physx::PxActor& actor) override {}
    };
    nb::class_<PxBroadPhaseCallback> pxBroadPhaseCallback(m, "PxBroadPhaseCallback");
    nb::class_<BroadPhaseCallback, PxBroadPhaseCallback> broadPhaseCallback(m, "BroadPhaseCallback");
}