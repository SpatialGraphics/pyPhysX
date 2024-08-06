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
            .def_rw("cudaContextManager", &PxSceneDesc::cudaContextManager)
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

    nb::class_<PxScene>(m, "PxScene")
            .def("release", &PxScene::release)
            .def("setFlag", &PxScene::setFlag)
            .def("getFlags", &PxScene::getFlags)
            .def("setLimits", &PxScene::setLimits)
            .def("getLimits", &PxScene::getLimits)
            .def("getPhysics", &PxScene::getPhysics)
            .def("getTimestamp", &PxScene::getTimestamp)
            .def("setName", &PxScene::setName)
            .def("getName", &PxScene::getName)
            .def("addArticulation", &PxScene::addArticulation)
            .def("removeArticulation", &PxScene::removeArticulation)
            .def("addActor", &PxScene::addActor)
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
            .def("addCollection", &PxScene::addCollection)
            .def("getNbActors", &PxScene::getNbActors)
            .def("getNbSoftBodies", &PxScene::getNbSoftBodies)
            .def("getNbParticleSystems", &PxScene::getNbParticleSystems)
            .def("getNbPBDParticleSystems", &PxScene::getNbPBDParticleSystems)
            .def("getNbFEMCloths", &PxScene::getNbFEMCloths)
            .def("getNbHairSystems", &PxScene::getNbHairSystems)
            .def("getNbArticulations", &PxScene::getNbArticulations)
            .def("getNbConstraints", &PxScene::getNbConstraints)
            .def("getNbAggregates", &PxScene::getNbAggregates);
}