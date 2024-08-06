//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/array.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

void bindActor(nb::module_& m) {
    nb::enum_<PxParticleFlag::Enum>(m, "PxParticleFlag")
            .value("eDISABLE_SELF_COLLISION", PxParticleFlag::Enum::eDISABLE_SELF_COLLISION)
            .value("eDISABLE_RIGID_COLLISION", PxParticleFlag::Enum::eDISABLE_RIGID_COLLISION)
            .value("eFULL_DIFFUSE_ADVECTION", PxParticleFlag::Enum::eFULL_DIFFUSE_ADVECTION)
            .value("eENABLE_SPECULATIVE_CCD", PxParticleFlag::Enum::eENABLE_SPECULATIVE_CCD);
    nb::enum_<PxParticleLockFlag::Enum>(m, "PxParticleLockFlag")
            .value("eLOCK_X", PxParticleLockFlag::Enum::eLOCK_X)
            .value("eLOCK_Y", PxParticleLockFlag::Enum::eLOCK_Y)
            .value("eLOCK_Z", PxParticleLockFlag::Enum::eLOCK_Z);
    nb::enum_<PxParticleBufferFlag::Enum>(m, "PxParticleBufferFlag")
            .value("eNONE", PxParticleBufferFlag::Enum::eNONE)
            .value("eUPDATE_POSITION", PxParticleBufferFlag::Enum::eUPDATE_POSITION)
            .value("eUPDATE_VELOCITY", PxParticleBufferFlag::Enum::eUPDATE_VELOCITY)
            .value("eUPDATE_PHASE", PxParticleBufferFlag::Enum::eUPDATE_PHASE)
            .value("eUPDATE_RESTPOSITION", PxParticleBufferFlag::Enum::eUPDATE_RESTPOSITION)
            .value("eUPDATE_CLOTH", PxParticleBufferFlag::Enum::eUPDATE_CLOTH)
            .value("eUPDATE_RIGID", PxParticleBufferFlag::Enum::eUPDATE_RIGID)
            .value("eUPDATE_DIFFUSE_PARAM", PxParticleBufferFlag::Enum::eUPDATE_DIFFUSE_PARAM)
            .value("eUPDATE_ATTACHMENTS", PxParticleBufferFlag::Enum::eUPDATE_ATTACHMENTS)
            .value("eALL", PxParticleBufferFlag::Enum::eALL);

    nb::enum_<PxForceMode::Enum>(m, "PxForceMode")
            .value("eFORCE", PxForceMode::Enum::eFORCE)
            .value("eIMPULSE", PxForceMode::Enum::eIMPULSE)
            .value("eVELOCITY_CHANGE", PxForceMode::Enum::eVELOCITY_CHANGE)
            .value("eACCELERATION", PxForceMode::Enum::eACCELERATION);

    nb::enum_<PxActorFlag::Enum>(m, "PxActorFlag")
            .value("eVISUALIZATION", PxActorFlag::Enum::eVISUALIZATION)
            .value("eDISABLE_GRAVITY", PxActorFlag::Enum::eDISABLE_GRAVITY)
            .value("eSEND_SLEEP_NOTIFIES", PxActorFlag::Enum::eSEND_SLEEP_NOTIFIES)
            .value("eDISABLE_SIMULATION", PxActorFlag::Enum::eDISABLE_SIMULATION);

    nb::enum_<PxActorType::Enum>(m, "PxActorType")
            .value("eRIGID_STATIC", PxActorType::Enum::eRIGID_STATIC)
            .value("eRIGID_DYNAMIC", PxActorType::Enum::eRIGID_DYNAMIC)
            .value("eARTICULATION_LINK", PxActorType::Enum::eARTICULATION_LINK)
            .value("eSOFTBODY", PxActorType::Enum::eSOFTBODY)
            .value("eFEMCLOTH", PxActorType::Enum::eFEMCLOTH)
            .value("ePBD_PARTICLESYSTEM", PxActorType::Enum::ePBD_PARTICLESYSTEM)
            .value("eHAIRSYSTEM", PxActorType::Enum::eHAIRSYSTEM);

    nb::enum_<PxRigidBodyFlag::Enum>(m, "PxRigidBodyFlag")
            .value("eKINEMATIC", PxRigidBodyFlag::Enum::eKINEMATIC)
            .value("eUSE_KINEMATIC_TARGET_FOR_SCENE_QUERIES",
                   PxRigidBodyFlag::Enum::eUSE_KINEMATIC_TARGET_FOR_SCENE_QUERIES)
            .value("eENABLE_CCD", PxRigidBodyFlag::Enum::eENABLE_CCD)
            .value("eENABLE_CCD_FRICTION", PxRigidBodyFlag::Enum::eENABLE_CCD_FRICTION)
            .value("eENABLE_SPECULATIVE_CCD", PxRigidBodyFlag::Enum::eENABLE_SPECULATIVE_CCD)
            .value("eENABLE_POSE_INTEGRATION_PREVIEW", PxRigidBodyFlag::Enum::eENABLE_POSE_INTEGRATION_PREVIEW)
            .value("eENABLE_CCD_MAX_CONTACT_IMPULSE", PxRigidBodyFlag::Enum::eENABLE_CCD_MAX_CONTACT_IMPULSE)
            .value("eRETAIN_ACCELERATIONS", PxRigidBodyFlag::Enum::eRETAIN_ACCELERATIONS)
            .value("eFORCE_KINE_KINE_NOTIFICATIONS", PxRigidBodyFlag::Enum::eFORCE_KINE_KINE_NOTIFICATIONS)
            .value("eFORCE_STATIC_KINE_NOTIFICATIONS", PxRigidBodyFlag::Enum::eFORCE_STATIC_KINE_NOTIFICATIONS)
            .value("eENABLE_GYROSCOPIC_FORCES", PxRigidBodyFlag::Enum::eENABLE_GYROSCOPIC_FORCES);

    nb::enum_<PxRigidDynamicLockFlag::Enum>(m, "PxRigidDynamicLockFlag")
            .value("eLOCK_LINEAR_X", PxRigidDynamicLockFlag::Enum::eLOCK_LINEAR_X)
            .value("eLOCK_LINEAR_Y", PxRigidDynamicLockFlag::Enum::eLOCK_LINEAR_Y)
            .value("eLOCK_LINEAR_Z", PxRigidDynamicLockFlag::Enum::eLOCK_LINEAR_Z)
            .value("eLOCK_ANGULAR_X", PxRigidDynamicLockFlag::Enum::eLOCK_ANGULAR_X)
            .value("eLOCK_ANGULAR_Y", PxRigidDynamicLockFlag::Enum::eLOCK_ANGULAR_Y)
            .value("eLOCK_ANGULAR_Z", PxRigidDynamicLockFlag::Enum::eLOCK_ANGULAR_Z);

    nb::class_<PxActor>(m, "PxActor")
            .def("release", &PxActor::release)
            .def("getType", &PxActor::getType)
            .def("getScene", &PxActor::getScene, nb::rv_policy::reference)
            .def("setName", &PxActor::setName, "name"_a)
            .def("getName", &PxActor::getName)
            .def("getWorldBounds", &PxActor::getWorldBounds, "inflation"_a = 1.01f)
            .def("setActorFlag", &PxActor::setActorFlag, "flag"_a, "value"_a)
            .def(
                    "setActorFlags",
                    [](PxActor* actor, int flags) {
                        actor->setActorFlags(PxActorFlags(flags));
                    },
                    "flags"_a)
            .def("getActorFlags",
                 [](PxActor* actor) {
                     return actor->getActorFlags().operator uint32_t();
                 })
            .def("setDominanceGroup", &PxActor::setDominanceGroup, "dominanceGroup"_a)
            .def("getDominanceGroup", &PxActor::getDominanceGroup);

    nb::class_<PxRigidActor, PxActor>(m, "PxRigidActor")
            .def("release", &PxRigidActor::release)
            .def("getInternalActorIndex", &PxRigidActor::getInternalActorIndex)
            .def("getGlobalPose", &PxRigidActor::getGlobalPose)
            .def("setGlobalPose", &PxRigidActor::setGlobalPose)
            .def("attachShape", &PxRigidActor::attachShape)
            .def("detachShape", &PxRigidActor::detachShape)
            .def("getNbShapes", &PxRigidActor::getNbShapes)
            .def("getNbConstraints", &PxRigidActor::getNbConstraints);

    nb::class_<PxRigidStatic, PxRigidActor> pxRigidStatic(m, "PxRigidStatic");

    nb::class_<PxRigidBody, PxRigidActor>(m, "PxRigidBody")
            .def("setCMassLocalPose", &PxRigidBody::setCMassLocalPose)
            .def("getCMassLocalPose", &PxRigidBody::getCMassLocalPose)
            .def("setMass", &PxRigidBody::setMass)
            .def("getMass", &PxRigidBody::getMass)
            .def("getInvMass", &PxRigidBody::getInvMass)
            .def("setMassSpaceInertiaTensor", &PxRigidBody::setMassSpaceInertiaTensor)
            .def("getMassSpaceInertiaTensor", &PxRigidBody::getMassSpaceInertiaTensor)
            .def("getMassSpaceInvInertiaTensor", &PxRigidBody::getMassSpaceInvInertiaTensor)
            .def("setLinearDamping", &PxRigidBody::setLinearDamping)
            .def("getLinearDamping", &PxRigidBody::getLinearDamping)
            .def("setAngularDamping", &PxRigidBody::setAngularDamping)
            .def("getAngularDamping", &PxRigidBody::getAngularDamping)
            .def("getLinearVelocity", &PxRigidBody::getLinearVelocity)
            .def("getAngularVelocity", &PxRigidBody::getAngularVelocity)
            .def("setMaxLinearVelocity", &PxRigidBody::setMaxLinearVelocity)
            .def("getMaxLinearVelocity", &PxRigidBody::getMaxLinearVelocity)
            .def("setMaxAngularVelocity", &PxRigidBody::setMaxAngularVelocity)
            .def("getMaxAngularVelocity", &PxRigidBody::getMaxAngularVelocity)
            .def("getLinearAcceleration", &PxRigidBody::getLinearAcceleration)
            .def("getAngularAcceleration", &PxRigidBody::getAngularAcceleration)
            .def("addForce", &PxRigidBody::addForce)
            .def("addTorque", &PxRigidBody::addTorque)
            .def("clearForce", &PxRigidBody::clearForce)
            .def("clearTorque", &PxRigidBody::clearTorque)
            .def("setForceAndTorque", &PxRigidBody::setForceAndTorque)
            .def("setRigidBodyFlag", &PxRigidBody::setRigidBodyFlag)
            .def("setMinCCDAdvanceCoefficient", &PxRigidBody::setMinCCDAdvanceCoefficient)
            .def("getMinCCDAdvanceCoefficient", &PxRigidBody::getMinCCDAdvanceCoefficient)
            .def("setMaxDepenetrationVelocity", &PxRigidBody::setMaxDepenetrationVelocity)
            .def("getMaxDepenetrationVelocity", &PxRigidBody::getMaxDepenetrationVelocity)
            .def("setMaxContactImpulse", &PxRigidBody::setMaxContactImpulse)
            .def("getMaxContactImpulse", &PxRigidBody::getMaxContactImpulse)
            .def("setContactSlopCoefficient", &PxRigidBody::setContactSlopCoefficient)
            .def("getContactSlopCoefficient", &PxRigidBody::getContactSlopCoefficient);

    nb::class_<PxRigidDynamic, PxRigidBody>(m, "PxRigidDynamic")
            .def("setKinematicTarget", &PxRigidDynamic::setKinematicTarget)
            .def("getKinematicTarget", &PxRigidDynamic::getKinematicTarget)
            .def("isSleeping", &PxRigidDynamic::isSleeping)
            .def("setSleepThreshold", &PxRigidDynamic::setSleepThreshold)
            .def("getSleepThreshold", &PxRigidDynamic::getSleepThreshold)
            .def("setStabilizationThreshold", &PxRigidDynamic::setStabilizationThreshold)
            .def("getStabilizationThreshold", &PxRigidDynamic::getStabilizationThreshold)
            .def("setWakeCounter", &PxRigidDynamic::setWakeCounter)
            .def("getWakeCounter", &PxRigidDynamic::getWakeCounter)
            .def("wakeUp", &PxRigidDynamic::wakeUp)
            .def("putToSleep", &PxRigidDynamic::putToSleep)
            .def("setRigidDynamicLockFlags",
                 [](PxRigidDynamic* joint, int flags) {
                     return joint->setRigidDynamicLockFlags(PxRigidDynamicLockFlags(flags));
                 })
            .def("setRigidDynamicLockFlag", &PxRigidDynamic::setRigidDynamicLockFlag)
            .def("getRigidDynamicLockFlags",
                 [](PxRigidDynamic* joint, int flags) {
                     return joint->getRigidDynamicLockFlags().operator uint32_t();
                 })
            .def("getLinearVelocity", &PxRigidDynamic::getLinearVelocity)
            .def("setLinearVelocity", &PxRigidDynamic::setLinearVelocity)
            .def("getAngularVelocity", &PxRigidDynamic::getAngularVelocity)
            .def("setAngularVelocity", &PxRigidDynamic::setAngularVelocity)
            .def("setSolverIterationCounts", &PxRigidDynamic::setSolverIterationCounts)
            .def("getSolverIterationCounts", &PxRigidDynamic::getSolverIterationCounts)
            .def("getContactReportThreshold", &PxRigidDynamic::getContactReportThreshold)
            .def("setContactReportThreshold", &PxRigidDynamic::setContactReportThreshold)
            .def("getGPUIndex", &PxRigidDynamic::getGPUIndex);

    nb::class_<PxArticulationLink, PxRigidBody>(m, "PxArticulationLink")
            .def("release", &PxArticulationLink::release)
            .def("getArticulation", &PxArticulationLink::getArticulation)
            .def("getInboundJoint", &PxArticulationLink::getInboundJoint)
            .def("getInboundJointDof", &PxArticulationLink::getInboundJointDof)
            .def("getNbChildren", &PxArticulationLink::getNbChildren)
            .def("getLinkIndex", &PxArticulationLink::getLinkIndex)
            .def("setCfmScale", &PxArticulationLink::setCfmScale)
            .def("getCfmScale", &PxArticulationLink::getCfmScale)
            .def("getLinearVelocity", &PxArticulationLink::getLinearVelocity)
            .def("getAngularVelocity", &PxArticulationLink::getAngularVelocity);

    //==================================================================================================================
    nb::class_<PxSoftBody, PxActor>(m, "PxSoftBody")
            .def("setSoftBodyFlag", &PxSoftBody::setSoftBodyFlag)
            .def("setParameter", &PxSoftBody::setParameter)
            .def("getParameter", &PxSoftBody::getParameter)
            .def("getPositionInvMassBufferD", &PxSoftBody::getPositionInvMassBufferD)
            .def("getRestPositionBufferD", &PxSoftBody::getRestPositionBufferD)
            .def("getSimPositionInvMassBufferD", &PxSoftBody::getSimPositionInvMassBufferD)
            .def("getSimVelocityBufferD", &PxSoftBody::getSimVelocityBufferD)
            .def("markDirty", &PxSoftBody::markDirty)
            .def("setKinematicTargetBufferD", &PxSoftBody::setKinematicTargetBufferD)
            //            .def("getCudaContextManager", &PxSoftBody::getCudaContextManager)
            .def("setWakeCounter", &PxSoftBody::setWakeCounter)
            .def("getWakeCounter", &PxSoftBody::getWakeCounter)
            .def("isSleeping", &PxSoftBody::isSleeping)
            .def("setSolverIterationCounts", &PxSoftBody::setSolverIterationCounts)
            .def("getSolverIterationCounts", &PxSoftBody::getSolverIterationCounts)
            .def("getShape", &PxSoftBody::getShape)
            .def("getCollisionMesh", nb::overload_cast<>(&PxSoftBody::getCollisionMesh, nb::const_))
            .def("getSimulationMesh", nb::overload_cast<>(&PxSoftBody::getSimulationMesh, nb::const_))
            .def("getSoftBodyAuxData", nb::overload_cast<>(&PxSoftBody::getSoftBodyAuxData, nb::const_))
            .def("attachShape", &PxSoftBody::attachShape)
            .def("attachSimulationMesh", &PxSoftBody::attachSimulationMesh)
            .def("detachShape", &PxSoftBody::detachShape)
            .def("detachSimulationMesh", &PxSoftBody::detachSimulationMesh)
            .def("release", &PxSoftBody::release)
            .def("addParticleFilter", &PxSoftBody::addParticleFilter)
            .def("removeParticleFilter", &PxSoftBody::removeParticleFilter)
            .def("addParticleAttachment", &PxSoftBody::addParticleAttachment)
            .def("removeParticleAttachment", &PxSoftBody::removeParticleAttachment)
            .def("addRigidFilter", &PxSoftBody::addRigidFilter)
            .def("removeRigidFilter", &PxSoftBody::removeRigidFilter)
            .def("addRigidAttachment", &PxSoftBody::addRigidAttachment)
            .def("removeRigidAttachment", &PxSoftBody::removeRigidAttachment)
            .def("addTetRigidFilter", &PxSoftBody::addTetRigidFilter)
            .def("removeTetRigidFilter", &PxSoftBody::removeTetRigidFilter)
            .def("addTetRigidAttachment", &PxSoftBody::addTetRigidAttachment)
            .def("addSoftBodyFilter", &PxSoftBody::addSoftBodyFilter)
            .def("removeSoftBodyFilter", &PxSoftBody::removeSoftBodyFilter)
            .def("addSoftBodyFilters", &PxSoftBody::addSoftBodyFilters)
            .def("removeSoftBodyFilters", &PxSoftBody::removeSoftBodyFilters)
            .def("addSoftBodyAttachment", &PxSoftBody::addSoftBodyAttachment)
            .def("removeSoftBodyAttachment", &PxSoftBody::removeSoftBodyAttachment)
            //            .def("addClothFilter", &PxSoftBody::addClothFilter)
            //            .def("removeClothFilter", &PxSoftBody::removeClothFilter)
            //            .def("addVertClothFilter", &PxSoftBody::addVertClothFilter)
            //            .def("removeVertClothFilter", &PxSoftBody::removeVertClothFilter)
            //            .def("addClothAttachment", &PxSoftBody::addClothAttachment)
            //            .def("removeClothAttachment", &PxSoftBody::removeClothAttachment)
            .def("getWorldBounds", &PxSoftBody::getWorldBounds)
            .def("getGpuSoftBodyIndex", &PxSoftBody::getGpuSoftBodyIndex);

    //==================================================================================================================
    nb::class_<PxPBDParticleSystem, PxActor>(m, "PxPBDParticleSystem")
            .def("setSolverIterationCounts", &PxPBDParticleSystem::setSolverIterationCounts)
            .def("getSolverIterationCounts", &PxPBDParticleSystem::getSolverIterationCounts)
            .def("getSimulationFilterData", &PxPBDParticleSystem::getSimulationFilterData)
            .def("setSimulationFilterData", &PxPBDParticleSystem::setSimulationFilterData)
            .def("setParticleFlag", &PxPBDParticleSystem::setParticleFlag)
            .def("setMaxDepenetrationVelocity", &PxPBDParticleSystem::setMaxDepenetrationVelocity)
            .def("getMaxDepenetrationVelocity", &PxPBDParticleSystem::getMaxDepenetrationVelocity)
            .def("setMaxVelocity", &PxPBDParticleSystem::setMaxVelocity)
            .def("getMaxVelocity", &PxPBDParticleSystem::getMaxVelocity)
            //            .def("getCudaContextManager", &PxPBDParticleSystem::getCudaContextManager)
            .def("setRestOffset", &PxPBDParticleSystem::setRestOffset)
            .def("getRestOffset", &PxPBDParticleSystem::getRestOffset)
            .def("setContactOffset", &PxPBDParticleSystem::setContactOffset)
            .def("getContactOffset", &PxPBDParticleSystem::getContactOffset)
            .def("setParticleContactOffset", &PxPBDParticleSystem::setParticleContactOffset)
            .def("getParticleContactOffset", &PxPBDParticleSystem::getParticleContactOffset)
            .def("setSolidRestOffset", &PxPBDParticleSystem::setSolidRestOffset)
            .def("getSolidRestOffset", &PxPBDParticleSystem::getSolidRestOffset)
            .def("addRigidAttachment", &PxPBDParticleSystem::addRigidAttachment)
            .def("removeRigidAttachment", &PxPBDParticleSystem::removeRigidAttachment)
            .def("enableCCD", &PxPBDParticleSystem::enableCCD)
            .def("setParticleLockFlag", &PxPBDParticleSystem::setParticleLockFlag)
            .def("createPhase",
                 [](PxPBDParticleSystem* system, PxPBDMaterial* material, int flags) {
                     return system->createPhase(material, PxParticlePhaseFlags(flags));
                 })
            .def("getNbParticleMaterials", &PxPBDParticleSystem::getNbParticleMaterials)
            .def("addParticleBuffer", &PxPBDParticleSystem::addParticleBuffer)
            .def("removeParticleBuffer", &PxPBDParticleSystem::removeParticleBuffer)
            .def("getGpuParticleSystemIndex", &PxPBDParticleSystem::getGpuParticleSystemIndex)
            .def("setWind", &PxPBDParticleSystem::setWind)
            .def("getWind", &PxPBDParticleSystem::getWind)
            .def("setFluidBoundaryDensityScale", &PxPBDParticleSystem::setFluidBoundaryDensityScale)
            .def("getFluidBoundaryDensityScale", &PxPBDParticleSystem::getFluidBoundaryDensityScale)
            .def("setFluidRestOffset", &PxPBDParticleSystem::setFluidRestOffset)
            .def("getFluidRestOffset", &PxPBDParticleSystem::getFluidRestOffset)
            .def("setGridSizeX", &PxPBDParticleSystem::setGridSizeX)
            .def("getGridSizeX", &PxPBDParticleSystem::getGridSizeX)
            .def("setGridSizeY", &PxPBDParticleSystem::setGridSizeY)
            .def("getGridSizeY", &PxPBDParticleSystem::getGridSizeY)
            .def("setGridSizeZ", &PxPBDParticleSystem::setGridSizeZ)
            .def("getGridSizeZ", &PxPBDParticleSystem::getGridSizeZ);
    nb::class_<PxParticleBuffer>(m, "PxParticleBuffer")
            .def("setNbActiveParticles", &PxParticleBuffer::setNbActiveParticles)
            .def("getNbActiveParticles", &PxParticleBuffer::getNbActiveParticles)
            .def("getMaxParticles", &PxParticleBuffer::getMaxParticles)
            .def("getNbParticleVolumes", &PxParticleBuffer::getNbParticleVolumes)
            .def("setNbParticleVolumes", &PxParticleBuffer::setNbParticleVolumes)
            .def("getMaxParticleVolumes", &PxParticleBuffer::getMaxParticleVolumes)
            .def("getFlatListStartIndex", &PxParticleBuffer::getFlatListStartIndex)
            .def("raiseFlags", &PxParticleBuffer::raiseFlags)
            .def("release", &PxParticleBuffer::release)
            .def("getUniqueId", &PxParticleBuffer::getUniqueId);
}