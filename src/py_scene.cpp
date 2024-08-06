//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>

#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

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

    nb::enum_<PxQueryFlag::Enum>(m, "PxQueryFlag")
            .value("eSTATIC", PxQueryFlag::Enum::eSTATIC)
            .value("eDYNAMIC", PxQueryFlag::Enum::eDYNAMIC)
            .value("ePREFILTER", PxQueryFlag::Enum::ePREFILTER)
            .value("ePOSTFILTER", PxQueryFlag::Enum::ePOSTFILTER)
            .value("eANY_HIT", PxQueryFlag::Enum::eANY_HIT)
            .value("eNO_BLOCK", PxQueryFlag::Enum::eNO_BLOCK)
            .value("eBATCH_QUERY_LEGACY_BEHAVIOUR", PxQueryFlag::Enum::eBATCH_QUERY_LEGACY_BEHAVIOUR)
            .value("eDISABLE_HARDCODED_FILTER", PxQueryFlag::Enum::eDISABLE_HARDCODED_FILTER);

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

    nb::class_<PxSceneDesc>(m, "PxSceneDesc")
            .def(nb::init<PxTolerancesScale>())
            .def("setToDefault", &PxSceneDesc::setToDefault)
            .def("isValid", &PxSceneDesc::isValid)
            .def("getTolerancesScale", &PxSceneDesc::getTolerancesScale, nb::rv_policy::reference)
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
            .def("setFlag", &PxScene::setFlag)
            .def("getFlags",
                 [](PxScene* scene) {
                     return scene->getFlags().operator uint32_t();
                 })
            .def("setLimits", &PxScene::setLimits)
            .def("getLimits", &PxScene::getLimits)
            .def("getPhysics", &PxScene::getPhysics)
            .def("getTimestamp", &PxScene::getTimestamp)
            .def("setName", &PxScene::setName)
            .def("getName", &PxScene::getName)
            .def("addArticulation", &PxScene::addArticulation)
            .def("removeArticulation", &PxScene::removeArticulation)
            .def("addActor",
                 [](PxScene* scene, PxActor& actor) {
                     return scene->addActor(actor);
                 })
            .def("addActors",
                 [](PxScene* scene, std::vector<PxActor*> actors) {
                     scene->addActors(actors.data(), actors.size());
                 })
            .def("removeActor", &PxScene::removeActor)
            .def("removeActors",
                 [](PxScene* scene, std::vector<PxActor*> actors, bool wakeOnLostTouch) {
                     scene->removeActors(actors.data(), actors.size(), wakeOnLostTouch);
                 })
            .def("addAggregate", &PxScene::addAggregate)
            .def("removeAggregate", &PxScene::removeAggregate)
            //            .def("addCollection", &PxScene::addCollection)
            .def("getNbActors",
                 [](PxScene* scene, int flags) {
                     return scene->getNbActors(PxActorTypeFlags(flags));
                 })
            .def("getNbSoftBodies", &PxScene::getNbSoftBodies)
            .def("getNbParticleSystems", &PxScene::getNbParticleSystems)
            .def("getNbPBDParticleSystems", &PxScene::getNbPBDParticleSystems)
            .def("getNbFEMCloths", &PxScene::getNbFEMCloths)
            .def("getNbHairSystems", &PxScene::getNbHairSystems)
            .def("getNbArticulations", &PxScene::getNbArticulations)
            .def("getNbConstraints", &PxScene::getNbConstraints)
            .def("getNbAggregates", &PxScene::getNbAggregates);

    nb::class_<PxSceneQuerySystemBase>(m, "PxSceneQuerySystemBase")
            .def("setDynamicTreeRebuildRateHint", &PxSceneQuerySystemBase::setDynamicTreeRebuildRateHint)
            .def("getDynamicTreeRebuildRateHint", &PxSceneQuerySystemBase::getDynamicTreeRebuildRateHint)
            .def("forceRebuildDynamicTree", &PxSceneQuerySystemBase::forceRebuildDynamicTree)
            .def("setUpdateMode", &PxSceneQuerySystemBase::setUpdateMode)
            .def("getUpdateMode", &PxSceneQuerySystemBase::getUpdateMode)
            .def("getStaticTimestamp", &PxSceneQuerySystemBase::getStaticTimestamp)
            .def("flushUpdates", &PxSceneQuerySystemBase::flushUpdates);
    //            .def("raycast", &PxSceneQuerySystemBase::raycast)
    //            .def("sweep", &PxSceneQuerySystemBase::sweep)
    //            .def("overlap", &PxSceneQuerySystemBase::overlap);
    nb::class_<PxSceneSQSystem, PxSceneQuerySystemBase>(m, "PxSceneSQSystem")
            .def("setSceneQueryUpdateMode", &PxSceneSQSystem::setSceneQueryUpdateMode)
            .def("getSceneQueryUpdateMode", &PxSceneSQSystem::getSceneQueryUpdateMode)
            .def("getSceneQueryStaticTimestamp", &PxSceneSQSystem::getSceneQueryStaticTimestamp)
            .def("flushQueryUpdates", &PxSceneSQSystem::flushQueryUpdates)
            .def("forceDynamicTreeRebuild", &PxSceneSQSystem::forceDynamicTreeRebuild)
            .def("getStaticStructure", &PxSceneSQSystem::getStaticStructure)
            .def("getDynamicStructure", &PxSceneSQSystem::getDynamicStructure)
            //            .def("sceneQueriesUpdate", &PxSceneSQSystem::sceneQueriesUpdate)
            .def("checkQueries", &PxSceneSQSystem::checkQueries)
            .def("fetchQueries", &PxSceneSQSystem::fetchQueries);
    nb::class_<PxSceneQuerySystem, PxSceneQuerySystemBase>(m, "PxSceneQuerySystem")
            .def("release", &PxSceneQuerySystem::release)
            .def("acquireReference", &PxSceneQuerySystem::acquireReference)
            .def("preallocate", &PxSceneQuerySystem::preallocate)
            .def("flushMemory", &PxSceneQuerySystem::flushMemory)
            .def("addSQShape", &PxSceneQuerySystem::addSQShape)
            .def("removeSQShape", &PxSceneQuerySystem::removeSQShape)
            .def("updateSQShape", &PxSceneQuerySystem::updateSQShape)
            //            .def("addSQCompound", &PxSceneQuerySystem::addSQCompound)
            .def("removeSQCompound", &PxSceneQuerySystem::removeSQCompound)
            .def("updateSQCompound", &PxSceneQuerySystem::updateSQCompound)
            .def("shiftOrigin", &PxSceneQuerySystem::shiftOrigin)
            //            .def("visualize", &PxSceneQuerySystem::visualize)
            .def("merge", &PxSceneQuerySystem::merge)
            .def("getHandle", &PxSceneQuerySystem::getHandle)
            //            .def("sync", &PxSceneQuerySystem::sync)
            .def("finalizeUpdates", &PxSceneQuerySystem::finalizeUpdates);
    //            .def("prepareSceneQueryBuildStep", &PxSceneQuerySystem::prepareSceneQueryBuildStep)
    //            .def("sceneQueryBuildStep", &PxSceneQuerySystem::sceneQueryBuildStep);

    nb::class_<PxPruningStructure>(m, "PxPruningStructure")
            .def("release", &PxPruningStructure::release)
            .def("getNbRigidActors", &PxPruningStructure::getNbRigidActors);

    nb::class_<PxCpuDispatcher>(m, "PxCpuDispatcher").def("getWorkerCount", &PxCpuDispatcher::getWorkerCount);
    nb::class_<PxDefaultCpuDispatcher, PxCpuDispatcher>(m, "PxDefaultCpuDispatcher")
            .def("setRunProfiled", &PxDefaultCpuDispatcher::setRunProfiled)
            .def("getRunProfiled", &PxDefaultCpuDispatcher::getRunProfiled);

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