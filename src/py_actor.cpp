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

void bindActor(nb::module_& m) {
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
    bindFlags<PxActorFlag::Enum, PxU8>(m, "PxActorFlags");

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
    bindFlags<PxRigidBodyFlag::Enum, PxU16>(m, "PxRigidBodyFlags");

    nb::enum_<PxRigidDynamicLockFlag::Enum>(m, "PxRigidDynamicLockFlag")
            .value("eLOCK_LINEAR_X", PxRigidDynamicLockFlag::Enum::eLOCK_LINEAR_X)
            .value("eLOCK_LINEAR_Y", PxRigidDynamicLockFlag::Enum::eLOCK_LINEAR_Y)
            .value("eLOCK_LINEAR_Z", PxRigidDynamicLockFlag::Enum::eLOCK_LINEAR_Z)
            .value("eLOCK_ANGULAR_X", PxRigidDynamicLockFlag::Enum::eLOCK_ANGULAR_X)
            .value("eLOCK_ANGULAR_Y", PxRigidDynamicLockFlag::Enum::eLOCK_ANGULAR_Y)
            .value("eLOCK_ANGULAR_Z", PxRigidDynamicLockFlag::Enum::eLOCK_ANGULAR_Z);
    bindFlags<PxRigidDynamicLockFlag::Enum, PxU8>(m, "PxRigidDynamicLockFlags");

    nb::class_<PxActor>(m, "PxActor")
            .def("release", &PxActor::release)
            .def("getType", &PxActor::getType)
            .def("getScene", &PxActor::getScene, nb::rv_policy::reference)
            .def("getWorldBounds", &PxActor::getWorldBounds, "inflation"_a = 1.01f)
            .def_prop_rw("name", &PxActor::getName, &PxActor::setName)
            .def("setActorFlag", &PxActor::setActorFlag, "flag"_a, "value"_a)
            .def_prop_rw("actorFlags", &PxActor::getActorFlags, &PxActor::setActorFlags)
            .def_prop_rw("dominanceGroup", &PxActor::getDominanceGroup, &PxActor::setDominanceGroup);

    nb::class_<PxRigidActor, PxActor>(m, "PxRigidActor")
            .def("release", &PxRigidActor::release)
            .def("getInternalActorIndex", &PxRigidActor::getInternalActorIndex)
            .def_prop_rw("globalPose", &PxRigidActor::getGlobalPose, &PxRigidActor::setGlobalPose)
            .def("attachShape", &PxRigidActor::attachShape)
            .def("detachShape", &PxRigidActor::detachShape)
            .def("getNbShapes", &PxRigidActor::getNbShapes)
            .def("getNbConstraints", &PxRigidActor::getNbConstraints);

    nb::class_<PxRigidStatic, PxRigidActor> pxRigidStatic(m, "PxRigidStatic");

    nb::class_<PxRigidBody, PxRigidActor>(m, "PxRigidBody")
            .def_prop_rw("cMassLocalPose", &PxRigidBody::getCMassLocalPose, &PxRigidBody::setCMassLocalPose)
            .def_prop_rw("mass", &PxRigidBody::getMass, &PxRigidBody::setMass)
            .def("getInvMass", &PxRigidBody::getInvMass)
            .def_prop_rw("massSpaceInertiaTensor", &PxRigidBody::getMassSpaceInertiaTensor,
                         &PxRigidBody::setMassSpaceInertiaTensor)
            .def("getMassSpaceInvInertiaTensor", &PxRigidBody::getMassSpaceInvInertiaTensor)
            .def_prop_rw("linearDamping", &PxRigidBody::getLinearDamping, &PxRigidBody::setLinearDamping)
            .def_prop_rw("angularDamping", &PxRigidBody::getAngularDamping, &PxRigidBody::setAngularDamping)
            .def("getLinearVelocity", &PxRigidBody::getLinearVelocity)
            .def("getAngularVelocity", &PxRigidBody::getAngularVelocity)
            .def_prop_rw("maxLinearVelocity", &PxRigidBody::getMaxLinearVelocity, &PxRigidBody::setMaxLinearVelocity)
            .def_prop_rw("maxAngularVelocity", &PxRigidBody::getMaxAngularVelocity, &PxRigidBody::setMaxAngularVelocity)
            .def("getLinearAcceleration", &PxRigidBody::getLinearAcceleration)
            .def("getAngularAcceleration", &PxRigidBody::getAngularAcceleration)
            .def("addForce", &PxRigidBody::addForce)
            .def("addTorque", &PxRigidBody::addTorque)
            .def("clearForce", &PxRigidBody::clearForce)
            .def("clearTorque", &PxRigidBody::clearTorque)
            .def("setForceAndTorque", &PxRigidBody::setForceAndTorque)
            .def("setRigidBodyFlag", &PxRigidBody::setRigidBodyFlag)
            .def_prop_rw("rigidBodyFlags", &PxRigidBody::getRigidBodyFlags, &PxRigidBody::setRigidBodyFlags)
            .def_prop_rw("minCCDAdvanceCoefficient", &PxRigidBody::getMinCCDAdvanceCoefficient,
                         &PxRigidBody::setMinCCDAdvanceCoefficient)
            .def_prop_rw("maxDepenetrationVelocity", &PxRigidBody::getMaxDepenetrationVelocity,
                         &PxRigidBody::setMaxDepenetrationVelocity)
            .def_prop_rw("maxContactImpulse", &PxRigidBody::getMaxContactImpulse, &PxRigidBody::setMaxContactImpulse)
            .def_prop_rw("contactSlopCoefficient", &PxRigidBody::getContactSlopCoefficient,
                         &PxRigidBody::setContactSlopCoefficient);

    nb::class_<PxRigidDynamic, PxRigidBody>(m, "PxRigidDynamic")
            .def("setKinematicTarget", &PxRigidDynamic::setKinematicTarget)
            .def("getKinematicTarget", &PxRigidDynamic::getKinematicTarget)
            .def("isSleeping", &PxRigidDynamic::isSleeping)
            .def_prop_rw("sleepThreshold", &PxRigidDynamic::getSleepThreshold, &PxRigidDynamic::setSleepThreshold)
            .def_prop_rw("stabilizationThreshold", &PxRigidDynamic::getStabilizationThreshold,
                         &PxRigidDynamic::setStabilizationThreshold)
            .def_prop_rw("wakeCounter", &PxRigidDynamic::getWakeCounter, &PxRigidDynamic::setWakeCounter)
            .def("wakeUp", &PxRigidDynamic::wakeUp)
            .def("putToSleep", &PxRigidDynamic::putToSleep)
            .def_prop_rw("rigidDynamicLockFlags", &PxRigidDynamic::getRigidDynamicLockFlags,
                         &PxRigidDynamic::setRigidDynamicLockFlags)
            .def("setRigidDynamicLockFlag", &PxRigidDynamic::setRigidDynamicLockFlag)
            .def_prop_rw("linearVelocity", &PxRigidDynamic::getLinearVelocity, &PxRigidDynamic::setLinearVelocity)
            .def_prop_rw("angularVelocity", &PxRigidDynamic::getAngularVelocity, &PxRigidDynamic::setAngularVelocity)
            .def("getSolverIterationCounts", &PxRigidDynamic::getSolverIterationCounts)
            .def("setSolverIterationCounts", &PxRigidDynamic::setSolverIterationCounts)
            .def_prop_rw("contactReportThreshold", &PxRigidDynamic::getContactReportThreshold,
                         &PxRigidDynamic::setContactReportThreshold)
            .def("getGPUIndex", &PxRigidDynamic::getGPUIndex);

    nb::class_<PxArticulationLink, PxRigidBody>(m, "PxArticulationLink")
            .def("release", &PxArticulationLink::release)
            .def("getArticulation", &PxArticulationLink::getArticulation)
            .def("getInboundJoint", &PxArticulationLink::getInboundJoint)
            .def("getInboundJointDof", &PxArticulationLink::getInboundJointDof)
            .def("getNbChildren", &PxArticulationLink::getNbChildren)
            .def("getLinkIndex", &PxArticulationLink::getLinkIndex)
            .def_prop_rw("cfmScale", &PxArticulationLink::getCfmScale, &PxArticulationLink::setCfmScale)
            .def("getLinearVelocity", &PxArticulationLink::getLinearVelocity)
            .def("getAngularVelocity", &PxArticulationLink::getAngularVelocity);

    //==================================================================================================================
    nb::class_<PxSoftBody, PxActor>(m, "PxSoftBody")
            .def("setSoftBodyFlag", &PxSoftBody::setSoftBodyFlag)
            .def_prop_rw("softBodyFlags", &PxSoftBody::getSoftBodyFlag, &PxSoftBody::setSoftBodyFlags)
            .def_prop_rw("parameter", &PxSoftBody::getParameter, &PxSoftBody::setParameter)
            .def("getPositionInvMassBufferD", &PxSoftBody::getPositionInvMassBufferD)
            .def("getRestPositionBufferD", &PxSoftBody::getRestPositionBufferD)
            .def("getSimPositionInvMassBufferD", &PxSoftBody::getSimPositionInvMassBufferD)
            .def("getSimVelocityBufferD", &PxSoftBody::getSimVelocityBufferD)
            .def("markDirty", &PxSoftBody::markDirty)
            .def("setKinematicTargetBufferD",
                 [](PxSoftBody* body, const std::vector<PxVec4>& positions, const PxSoftBodyFlags& flags) {
                     return body->setKinematicTargetBufferD(positions.data(), flags);
                 })
#ifdef SUPPORT_CUDA
            .def("getCudaContextManager", &PxSoftBody::getCudaContextManager)
#endif
            .def_prop_rw("wakeCounter", &PxSoftBody::getWakeCounter, &PxSoftBody::setWakeCounter)
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
}