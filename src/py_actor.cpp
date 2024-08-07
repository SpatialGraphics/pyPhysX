//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/tuple.h>

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
            .def("attachShape", &PxRigidActor::attachShape, "shape"_a)
            .def("detachShape", &PxRigidActor::detachShape, "shape"_a, "wakeOnLostTouch"_a = true)
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
            .def("addForce", &PxRigidBody::addForce, "force"_a, "mode"_a = PxForceMode::eFORCE, "autowake"_a = true)
            .def("addTorque", &PxRigidBody::addTorque, "torque"_a, "mode"_a = PxForceMode::eFORCE, "autowake"_a = true)
            .def("clearForce", &PxRigidBody::clearForce, "mode"_a = PxForceMode::eFORCE)
            .def("clearTorque", &PxRigidBody::clearTorque, "mode"_a = PxForceMode::eFORCE)
            .def("setForceAndTorque", &PxRigidBody::setForceAndTorque, "force"_a, "torque"_a,
                 "mode"_a = PxForceMode::eFORCE)
            .def("setRigidBodyFlag", &PxRigidBody::setRigidBodyFlag, "flag"_a, "value"_a)
            .def_prop_rw("rigidBodyFlags", &PxRigidBody::getRigidBodyFlags, &PxRigidBody::setRigidBodyFlags)
            .def_prop_rw("minCCDAdvanceCoefficient", &PxRigidBody::getMinCCDAdvanceCoefficient,
                         &PxRigidBody::setMinCCDAdvanceCoefficient)
            .def_prop_rw("maxDepenetrationVelocity", &PxRigidBody::getMaxDepenetrationVelocity,
                         &PxRigidBody::setMaxDepenetrationVelocity)
            .def_prop_rw("maxContactImpulse", &PxRigidBody::getMaxContactImpulse, &PxRigidBody::setMaxContactImpulse)
            .def_prop_rw("contactSlopCoefficient", &PxRigidBody::getContactSlopCoefficient,
                         &PxRigidBody::setContactSlopCoefficient);

    nb::class_<PxRigidDynamic, PxRigidBody>(m, "PxRigidDynamic")
            .def("setKinematicTarget", &PxRigidDynamic::setKinematicTarget, "destination"_a)
            .def("getKinematicTarget", &PxRigidDynamic::getKinematicTarget, "target"_a)
            .def("isSleeping", &PxRigidDynamic::isSleeping)
            .def_prop_rw("sleepThreshold", &PxRigidDynamic::getSleepThreshold, &PxRigidDynamic::setSleepThreshold)
            .def_prop_rw("stabilizationThreshold", &PxRigidDynamic::getStabilizationThreshold,
                         &PxRigidDynamic::setStabilizationThreshold)
            .def_prop_rw("wakeCounter", &PxRigidDynamic::getWakeCounter, &PxRigidDynamic::setWakeCounter)
            .def("wakeUp", &PxRigidDynamic::wakeUp)
            .def("putToSleep", &PxRigidDynamic::putToSleep)
            .def_prop_rw("rigidDynamicLockFlags", &PxRigidDynamic::getRigidDynamicLockFlags,
                         &PxRigidDynamic::setRigidDynamicLockFlags)
            .def("setRigidDynamicLockFlag", &PxRigidDynamic::setRigidDynamicLockFlag, "flag"_a, "value"_a)
            .def_prop_rw("linearVelocity", &PxRigidDynamic::getLinearVelocity, &PxRigidDynamic::setLinearVelocity)
            .def_prop_rw("angularVelocity", &PxRigidDynamic::getAngularVelocity, &PxRigidDynamic::setAngularVelocity)
            .def("getSolverIterationCounts",
                 [](PxRigidDynamic* body) {
                     std::tuple<PxU32, PxU32> result;
                     body->getSolverIterationCounts(std::get<0>(result), std::get<1>(result));
                     return result;
                 })
            .def("setSolverIterationCounts", &PxRigidDynamic::setSolverIterationCounts, "minPositionIters"_a,
                 "minVelocityIters"_a = 1)
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
            .def("setSoftBodyFlag", &PxSoftBody::setSoftBodyFlag, "flag"_a, "val"_a)
            .def_prop_rw("softBodyFlags", &PxSoftBody::getSoftBodyFlag, &PxSoftBody::setSoftBodyFlags)
            .def_prop_rw("parameter", &PxSoftBody::getParameter, &PxSoftBody::setParameter)
            .def("getPositionInvMassBufferD", &PxSoftBody::getPositionInvMassBufferD)
            .def("getRestPositionBufferD", &PxSoftBody::getRestPositionBufferD)
            .def("getSimPositionInvMassBufferD", &PxSoftBody::getSimPositionInvMassBufferD)
            .def("getSimVelocityBufferD", &PxSoftBody::getSimVelocityBufferD)
            .def("markDirty", &PxSoftBody::markDirty)
            .def(
                    "setKinematicTargetBufferD",
                    [](PxSoftBody* body, const std::vector<PxVec4>& positions, const PxSoftBodyFlags& flags) {
                        return body->setKinematicTargetBufferD(positions.data(), flags);
                    },
                    "positions"_a, "flags"_a)
#ifdef SUPPORT_CUDA
            .def("getCudaContextManager", &PxSoftBody::getCudaContextManager)
#endif
            .def_prop_rw("wakeCounter", &PxSoftBody::getWakeCounter, &PxSoftBody::setWakeCounter)
            .def("isSleeping", &PxSoftBody::isSleeping)
            .def("setSolverIterationCounts", &PxSoftBody::setSolverIterationCounts, "minPositionIters"_a,
                 "minVelocityIters"_a = 1)
            .def("getSolverIterationCounts",
                 [](PxSoftBody* body) {
                     std::tuple<PxU32, PxU32> result;
                     body->getSolverIterationCounts(std::get<0>(result), std::get<1>(result));
                     return result;
                 })
            .def("getShape", &PxSoftBody::getShape)
            .def("getCollisionMesh", nb::overload_cast<>(&PxSoftBody::getCollisionMesh, nb::const_))
            .def("getSimulationMesh", nb::overload_cast<>(&PxSoftBody::getSimulationMesh, nb::const_))
            .def("getSoftBodyAuxData", nb::overload_cast<>(&PxSoftBody::getSoftBodyAuxData, nb::const_))
            .def("attachShape", &PxSoftBody::attachShape, "shape"_a)
            .def("attachSimulationMesh", &PxSoftBody::attachSimulationMesh, "simulationMesh"_a, "softBodyAuxData"_a)
            .def("detachShape", &PxSoftBody::detachShape)
            .def("detachSimulationMesh", &PxSoftBody::detachSimulationMesh)
            .def("release", &PxSoftBody::release)
            .def("addParticleFilter", &PxSoftBody::addParticleFilter, "particlesystem"_a, "buffer"_a, "particleId"_a,
                 "tetId"_a)
            .def("removeParticleFilter", &PxSoftBody::removeParticleFilter, "particlesystem"_a, "buffer"_a,
                 "particleId"_a, "tetId"_a)
            .def("addParticleAttachment", &PxSoftBody::addParticleAttachment, "particlesystem"_a, "buffer"_a,
                 "particleId"_a, "tetId"_a, "barycentric"_a)
            .def("removeParticleAttachment", &PxSoftBody::removeParticleAttachment, "particlesystem"_a, "handle"_a)
            .def("addRigidFilter", &PxSoftBody::addRigidFilter, "actor"_a, "vertId"_a)
            .def("removeRigidFilter", &PxSoftBody::removeRigidFilter, "actor"_a, "vertId"_a)
            .def("addRigidAttachment", &PxSoftBody::addRigidAttachment, "actor"_a, "vertId"_a, "actorSpacePose"_a,
                 "constraint"_a.none())
            .def("removeRigidAttachment", &PxSoftBody::removeRigidAttachment, "actor"_a, "handle"_a)
            .def("addTetRigidFilter", &PxSoftBody::addTetRigidFilter, "actor"_a, "tetIdx"_a)
            .def("removeTetRigidFilter", &PxSoftBody::removeTetRigidFilter, "actor"_a, "tetIdx"_a)
            .def("addTetRigidAttachment", &PxSoftBody::addTetRigidAttachment, "actor"_a, "tetIdx"_a, "barycentric"_a,
                 "actorSpacePose"_a, "constraint"_a.none())
            .def("addSoftBodyFilter", &PxSoftBody::addSoftBodyFilter, "otherSoftBody"_a, "otherTetIdx"_a, "tetIdx1"_a)
            .def("removeSoftBodyFilter", &PxSoftBody::removeSoftBodyFilter, "otherSoftBody"_a, "otherTetIdx"_a,
                 "tetIdx1"_a)
            .def("addSoftBodyFilters", &PxSoftBody::addSoftBodyFilters, "otherSoftBody"_a, "otherTetIndices"_a,
                 "tetIndices"_a, "tetIndicesSize"_a)
            .def("removeSoftBodyFilters", &PxSoftBody::removeSoftBodyFilters, "otherSoftBody"_a, "otherTetIndices"_a,
                 "tetIndices"_a, "tetIndicesSize"_a)
            .def("addSoftBodyAttachment", &PxSoftBody::addSoftBodyAttachment, "softbody0"_a, "tetIdx0"_a,
                 "tetBarycentric0"_a, "tetIdx1"_a, "tetBarycentric1"_a, "constraint"_a.none(),
                 "constraintOffset"_a = 0.0f)
            .def("removeSoftBodyAttachment", &PxSoftBody::removeSoftBodyAttachment, "softbody0"_a, "handle"_a)
            //            .def("addClothFilter", &PxSoftBody::addClothFilter)
            //            .def("removeClothFilter", &PxSoftBody::removeClothFilter)
            //            .def("addVertClothFilter", &PxSoftBody::addVertClothFilter)
            //            .def("removeVertClothFilter", &PxSoftBody::removeVertClothFilter)
            //            .def("addClothAttachment", &PxSoftBody::addClothAttachment)
            //            .def("removeClothAttachment", &PxSoftBody::removeClothAttachment)
            .def("getWorldBounds", &PxSoftBody::getWorldBounds, "inflation"_a = 1.01f)
            .def("getGpuSoftBodyIndex", &PxSoftBody::getGpuSoftBodyIndex);
}