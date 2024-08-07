//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/eigen/dense.h>

#include "py_utils.h"

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

void bindArticulationReducedCoordinate(nb::module_& m) {
    nb::enum_<PxArticulationJointType::Enum>(m, "PxArticulationJointType")
            .value("eFIX", PxArticulationJointType::Enum::eFIX)
            .value("ePRISMATIC", PxArticulationJointType::Enum::ePRISMATIC)
            .value("eREVOLUTE", PxArticulationJointType::Enum::eREVOLUTE)
            .value("eREVOLUTE_UNWRAPPED", PxArticulationJointType::Enum::eREVOLUTE_UNWRAPPED)
            .value("eSPHERICAL", PxArticulationJointType::Enum::eSPHERICAL);

    nb::enum_<PxArticulationAxis::Enum>(m, "PxArticulationAxis")
            .value("eTWIST", PxArticulationAxis::Enum::eTWIST)
            .value("eSWING1", PxArticulationAxis::Enum::eSWING1)
            .value("eSWING2", PxArticulationAxis::Enum::eSWING2)
            .value("eX", PxArticulationAxis::Enum::eX)
            .value("eY", PxArticulationAxis::Enum::eY)
            .value("eZ", PxArticulationAxis::Enum::eZ);

    nb::enum_<PxArticulationMotion::Enum>(m, "PxArticulationMotion")
            .value("eLOCKED", PxArticulationMotion::Enum::eLOCKED)
            .value("eLIMITED", PxArticulationMotion::Enum::eLIMITED)
            .value("eFREE", PxArticulationMotion::Enum::eFREE);

    nb::enum_<PxArticulationDriveType::Enum>(m, "PxArticulationDriveType")
            .value("eFORCE", PxArticulationDriveType::Enum::eFORCE)
            .value("eACCELERATION", PxArticulationDriveType::Enum::eACCELERATION);

    nb::enum_<PxArticulationFlag::Enum>(m, "PxArticulationFlag")
            .value("eFIX_BASE", PxArticulationFlag::Enum::eFIX_BASE)
            .value("eDRIVE_LIMITS_ARE_FORCES", PxArticulationFlag::Enum::eDRIVE_LIMITS_ARE_FORCES)
            .value("eDISABLE_SELF_COLLISION", PxArticulationFlag::Enum::eDISABLE_SELF_COLLISION);
    bindFlags<PxArticulationFlag::Enum, PxU8>(m, "PxArticulationFlags");

    nb::enum_<PxArticulationKinematicFlag::Enum>(m, "PxArticulationKinematicFlag")
            .value("ePOSITION", PxArticulationKinematicFlag::Enum::ePOSITION)
            .value("eVELOCITY", PxArticulationKinematicFlag::Enum::eVELOCITY);
    bindFlags<PxArticulationKinematicFlag::Enum, PxU8>(m, "PxArticulationKinematicFlags");

    nb::enum_<PxArticulationCacheFlag::Enum>(m, "PxArticulationCacheFlag")
            .value("eVELOCITY", PxArticulationCacheFlag::Enum::eVELOCITY)
            .value("eACCELERATION", PxArticulationCacheFlag::Enum::eACCELERATION)
            .value("ePOSITION", PxArticulationCacheFlag::Enum::ePOSITION)
            .value("eFORCE", PxArticulationCacheFlag::Enum::eFORCE)
            .value("eLINK_VELOCITY", PxArticulationCacheFlag::Enum::eLINK_VELOCITY)
            .value("eLINK_ACCELERATION", PxArticulationCacheFlag::Enum::eLINK_ACCELERATION)
            .value("eROOT_TRANSFORM", PxArticulationCacheFlag::Enum::eROOT_TRANSFORM)
            .value("eROOT_VELOCITIES", PxArticulationCacheFlag::Enum::eROOT_VELOCITIES)
            .value("eLINK_INCOMING_JOINT_FORCE", PxArticulationCacheFlag::Enum::eLINK_INCOMING_JOINT_FORCE)
            .value("eJOINT_TARGET_POSITIONS", PxArticulationCacheFlag::Enum::eJOINT_TARGET_POSITIONS)
            .value("eJOINT_TARGET_VELOCITIES", PxArticulationCacheFlag::Enum::eJOINT_TARGET_VELOCITIES)
            .value("eLINK_FORCE", PxArticulationCacheFlag::Enum::eLINK_FORCE)
            .value("eLINK_TORQUE", PxArticulationCacheFlag::Enum::eLINK_TORQUE)
            .value("eALL", PxArticulationCacheFlag::Enum::eALL);
    bindFlags<PxArticulationCacheFlag::Enum>(m, "PxArticulationCacheFlags");

    nb::class_<PxArticulationReducedCoordinate>(m, "PxArticulationReducedCoordinate")
            .def("getScene", &PxArticulationReducedCoordinate::getScene, nb::rv_policy::reference)
            .def("setSolverIterationCounts", &PxArticulationReducedCoordinate::setSolverIterationCounts,
                 "minPositionIters"_a, "minVelocityIters"_a = 1)
            .def("getSolverIterationCounts",
                 [](PxArticulationReducedCoordinate* body) {
                     std::tuple<PxU32, PxU32> result;
                     body->getSolverIterationCounts(std::get<0>(result), std::get<1>(result));
                     return result;
                 })
            .def("isSleeping", &PxArticulationReducedCoordinate::isSleeping)
            .def_prop_rw("sleepThreshold", &PxArticulationReducedCoordinate::getSleepThreshold,
                         &PxArticulationReducedCoordinate::setSleepThreshold)
            .def_prop_rw("stabilizationThreshold", &PxArticulationReducedCoordinate::getStabilizationThreshold,
                         &PxArticulationReducedCoordinate::setStabilizationThreshold)
            .def_prop_rw("wakeCounter", &PxArticulationReducedCoordinate::getWakeCounter,
                         &PxArticulationReducedCoordinate::setWakeCounter)
            .def("wakeUp", &PxArticulationReducedCoordinate::wakeUp)
            .def("putToSleep", &PxArticulationReducedCoordinate::putToSleep)
            .def_prop_rw("maxCOMLinearVelocity", &PxArticulationReducedCoordinate::getMaxCOMLinearVelocity,
                         &PxArticulationReducedCoordinate::setMaxCOMLinearVelocity)
            .def_prop_rw("maxCOMAngularVelocity", &PxArticulationReducedCoordinate::getMaxCOMAngularVelocity,
                         &PxArticulationReducedCoordinate::setMaxCOMAngularVelocity)
            .def("createLink", &PxArticulationReducedCoordinate::createLink, "parent"_a, "pose"_a)
            .def("release", &PxArticulationReducedCoordinate::release)
            .def("getNbLinks", &PxArticulationReducedCoordinate::getNbLinks)
            .def("getNbShapes", &PxArticulationReducedCoordinate::getNbShapes)
            .def_prop_rw("name", &PxArticulationReducedCoordinate::getName, &PxArticulationReducedCoordinate::setName)
            .def("getWorldBounds", &PxArticulationReducedCoordinate::getWorldBounds, "inflation"_a = 1.01f)
            .def("getAggregate", &PxArticulationReducedCoordinate::getAggregate)
            .def_prop_rw("articulationFlags", &PxArticulationReducedCoordinate::getArticulationFlags,
                         &PxArticulationReducedCoordinate::setArticulationFlags)
            .def("setArticulationFlag", &PxArticulationReducedCoordinate::setArticulationFlag, "flag"_a, "value"_a)
            .def("getDofs", &PxArticulationReducedCoordinate::getDofs)

            .def("createCache", &PxArticulationReducedCoordinate::createCache, nb::rv_policy::reference)
            .def("getCacheDataSize", &PxArticulationReducedCoordinate::getCacheDataSize)
            .def("zeroCache", &PxArticulationReducedCoordinate::zeroCache, "cache"_a)
            .def("applyCache", &PxArticulationReducedCoordinate::applyCache, "cache"_a, "flags"_a, "autowake"_a = true)
            .def("copyInternalStateToCache", &PxArticulationReducedCoordinate::copyInternalStateToCache, "cache"_a,
                 "flags"_a)
            .def(
                    "packJointData",
                    [](PxArticulationReducedCoordinate* coordinate, std::vector<PxReal>& maximum,
                       std::vector<PxReal>& reduced) {
                        coordinate->packJointData(maximum.data(), reduced.data());
                    },
                    "maximum"_a, "reduced"_a)
            .def(
                    "unpackJointData",
                    [](PxArticulationReducedCoordinate* coordinate, std::vector<PxReal>& maximum,
                       std::vector<PxReal>& reduced) {
                        coordinate->unpackJointData(maximum.data(), reduced.data());
                    },
                    "maximum"_a, "reduced"_a)
            .def("commonInit", &PxArticulationReducedCoordinate::commonInit)
            .def("computeGeneralizedGravityForce", &PxArticulationReducedCoordinate::computeGeneralizedGravityForce,
                 "cache"_a)
            .def("computeCoriolisAndCentrifugalForce",
                 &PxArticulationReducedCoordinate::computeCoriolisAndCentrifugalForce, "cache"_a)
            .def("computeGeneralizedExternalForce", &PxArticulationReducedCoordinate::computeGeneralizedExternalForce,
                 "cache"_a)
            .def("computeJointAcceleration", &PxArticulationReducedCoordinate::computeJointAcceleration, "cache"_a)
            .def("computeJointForce", &PxArticulationReducedCoordinate::computeJointForce, "cache"_a)
            .def(
                    "computeDenseJacobian",
                    [](PxArticulationReducedCoordinate* coordinate, PxArticulationCache& cache) {
                        std::tuple<PxU32, PxU32> result;
                        coordinate->computeDenseJacobian(cache, std::get<0>(result), std::get<1>(result));
                        return result;
                    },
                    "cache"_a)
            .def("computeCoefficientMatrix", &PxArticulationReducedCoordinate::computeCoefficientMatrix, "cache"_a)
            .def(
                    "computeLambda",
                    [](PxArticulationReducedCoordinate* coordinate, PxArticulationCache& cache,
                       PxArticulationCache& initialState, const std::vector<PxReal>& jointTorque, const PxU32 maxIter) {
                        return coordinate->computeLambda(cache, initialState, jointTorque.data(), maxIter);
                    },
                    "cache"_a, "initialState"_a, "jointTorque"_a, "maxIter"_a)
            .def("computeGeneralizedMassMatrix", &PxArticulationReducedCoordinate::computeGeneralizedMassMatrix,
                 "cache"_a)
            .def("addLoopJoint", &PxArticulationReducedCoordinate::addLoopJoint, "joint"_a)
            .def("removeLoopJoint", &PxArticulationReducedCoordinate::removeLoopJoint, "joint"_a)
            .def("getNbLoopJoints", &PxArticulationReducedCoordinate::getNbLoopJoints)
            .def("getCoefficientMatrixSize", &PxArticulationReducedCoordinate::getCoefficientMatrixSize)
            .def_prop_rw("rootGlobalPose", &PxArticulationReducedCoordinate::getRootGlobalPose,
                         &PxArticulationReducedCoordinate::setRootGlobalPose)
            .def_prop_rw("rootLinearVelocity", &PxArticulationReducedCoordinate::getRootLinearVelocity,
                         &PxArticulationReducedCoordinate::setRootLinearVelocity)
            .def_prop_rw("rootAngularVelocity", &PxArticulationReducedCoordinate::getRootAngularVelocity,
                         &PxArticulationReducedCoordinate::setRootAngularVelocity)
            .def("getLinkAcceleration", &PxArticulationReducedCoordinate::getLinkAcceleration, "linkId"_a)
            .def("getGpuArticulationIndex", &PxArticulationReducedCoordinate::getGpuArticulationIndex)
            .def("getGPUIndex", &PxArticulationReducedCoordinate::getGPUIndex)
            .def("createSpatialTendon", &PxArticulationReducedCoordinate::createSpatialTendon)
            .def("createFixedTendon", &PxArticulationReducedCoordinate::createFixedTendon)
            .def("getNbSpatialTendons", &PxArticulationReducedCoordinate::getNbSpatialTendons)
            .def("getNbFixedTendons", &PxArticulationReducedCoordinate::getNbFixedTendons)
            .def("createMimicJoint", &PxArticulationReducedCoordinate::createMimicJoint, "jointA"_a, "axisA"_a,
                 "jointB"_a, "axisB"_a, "gearRatio"_a, "offset"_a)
            .def("getNbMimicJoints", &PxArticulationReducedCoordinate::getNbMimicJoints)
            .def("updateKinematic", &PxArticulationReducedCoordinate::updateKinematic, "flags"_a)
            .def("getSolverResidual", &PxArticulationReducedCoordinate::getSolverResidual);

    nb::class_<PxArticulationJointReducedCoordinate>(m, "PxArticulationJointReducedCoordinate")
            .def("getParentArticulationLink", &PxArticulationJointReducedCoordinate::getParentArticulationLink)
            .def_prop_rw("parentPose", &PxArticulationJointReducedCoordinate::getParentPose,
                         &PxArticulationJointReducedCoordinate::setParentPose)
            .def("getChildArticulationLink", &PxArticulationJointReducedCoordinate::getChildArticulationLink)
            .def_prop_rw("childPose", &PxArticulationJointReducedCoordinate::getChildPose,
                         &PxArticulationJointReducedCoordinate::setChildPose)
            .def_prop_rw("jointType", &PxArticulationJointReducedCoordinate::getJointType,
                         &PxArticulationJointReducedCoordinate::setJointType)
            .def("setMotion", &PxArticulationJointReducedCoordinate::setMotion, "axis"_a, "motion"_a)
            .def("getMotion", &PxArticulationJointReducedCoordinate::getMotion, "axis"_a)
            .def("setLimitParams", &PxArticulationJointReducedCoordinate::setLimitParams, "axis"_a, "limit"_a)
            .def("getLimitParams", &PxArticulationJointReducedCoordinate::getLimitParams, "axis"_a)
            .def("setDriveParams", &PxArticulationJointReducedCoordinate::setDriveParams, "axis"_a, "drive"_a)
            .def("getDriveParams", &PxArticulationJointReducedCoordinate::getDriveParams, "axis"_a)
            .def("setDriveTarget", &PxArticulationJointReducedCoordinate::setDriveTarget, "axis"_a, "target"_a,
                 "autowake"_a = true)
            .def("getDriveTarget", &PxArticulationJointReducedCoordinate::getDriveTarget, "axis"_a)
            .def("setDriveVelocity", &PxArticulationJointReducedCoordinate::setDriveVelocity, "axis"_a, "targetVel"_a,
                 "autowake"_a = true)
            .def("getDriveVelocity", &PxArticulationJointReducedCoordinate::getDriveVelocity, "axis"_a)
            .def("setArmature", &PxArticulationJointReducedCoordinate::setArmature, "axis"_a, "armature"_a)
            .def("getArmature", &PxArticulationJointReducedCoordinate::getArmature, "axis"_a)
            .def_prop_rw("frictionCoefficient", &PxArticulationJointReducedCoordinate::getFrictionCoefficient,
                         &PxArticulationJointReducedCoordinate::setFrictionCoefficient)
            .def_prop_rw("maxJointVelocity", &PxArticulationJointReducedCoordinate::getMaxJointVelocity,
                         &PxArticulationJointReducedCoordinate::setMaxJointVelocity)
            .def("setJointPosition", &PxArticulationJointReducedCoordinate::setJointPosition, "axis"_a, "jointPos"_a)
            .def("getJointPosition", &PxArticulationJointReducedCoordinate::getJointPosition, "axis"_a)
            .def("setJointVelocity", &PxArticulationJointReducedCoordinate::setJointVelocity, "axis"_a, "jointVel"_a)
            .def("getJointVelocity", &PxArticulationJointReducedCoordinate::getJointVelocity, "axis"_a);

    nb::class_<PxArticulationLimit>(m, "PxArticulationLimit")
            .def(nb::init<>())
            .def(nb::init<PxReal, PxReal>())
            .def_rw("low", &PxArticulationLimit::low)
            .def_rw("high", &PxArticulationLimit::high);

    nb::class_<PxArticulationDrive>(m, "PxArticulationDrive")
            .def(nb::init<>())
            .def(nb::init<PxReal, PxReal, PxReal, PxArticulationDriveType::Enum>())
            .def_rw("stiffness", &PxArticulationDrive::stiffness)
            .def_rw("damping", &PxArticulationDrive::damping)
            .def_rw("maxForce", &PxArticulationDrive::maxForce)
            .def_rw("driveType", &PxArticulationDrive::driveType);

    nb::class_<PxSpatialForce>(m, "PxSpatialForce")
            .def(nb::init<>())
            .def_rw("force", &PxSpatialForce::force)
            .def_rw("torque", &PxSpatialForce::torque);

    nb::class_<PxSpatialVelocity>(m, "PxSpatialVelocity")
            .def(nb::init<>())
            .def_rw("linear", &PxSpatialVelocity::linear)
            .def_rw("angular", &PxSpatialVelocity::angular);

    nb::class_<PxArticulationRootLinkData>(m, "PxArticulationRootLinkData")
            .def(nb::init<>())
            .def_rw("transform", &PxArticulationRootLinkData::transform)
            .def_rw("worldLinVel", &PxArticulationRootLinkData::worldLinVel)
            .def_rw("worldAngVel", &PxArticulationRootLinkData::worldAngVel)
            .def_rw("worldLinAccel", &PxArticulationRootLinkData::worldLinAccel)
            .def_rw("worldAngAccel", &PxArticulationRootLinkData::worldAngAccel);

    nb::class_<PxArticulationCache>(m, "PxArticulationCache")
            .def("release", &PxArticulationCache::release)
            .def(
                    "externalForces",
                    [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                        auto links = articulation->getNbLinks();
                        return std::vector<PxSpatialForce>(cache->externalForces, cache->externalForces + links);
                    },
                    "articulation"_a)
            .def(
                    "denseJacobian",
                    [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                        auto rows = articulation->getNbLinks() * 6;
                        auto cols = articulation->getDofs() + 6;
                        return Eigen::Map<Eigen::MatrixXf>(cache->denseJacobian, rows, cols);
                    },
                    "articulation"_a)
            .def(
                    "massMatrix",
                    [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                        auto rows = articulation->getDofs();
                        return Eigen::Map<Eigen::MatrixXf>(cache->massMatrix, rows, rows);
                    },
                    "articulation"_a)
            .def(
                    "jointVelocity",
                    [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                        auto rows = articulation->getDofs();
                        return Eigen::Map<Eigen::VectorXf>(cache->jointVelocity, rows);
                    },
                    "articulation"_a)
            .def(
                    "jointAcceleration",
                    [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                        auto rows = articulation->getDofs();
                        return Eigen::Map<Eigen::VectorXf>(cache->jointAcceleration, rows);
                    },
                    "articulation"_a)
            .def(
                    "jointPosition",
                    [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                        auto rows = articulation->getDofs();
                        return Eigen::Map<Eigen::VectorXf>(cache->jointPosition, rows);
                    },
                    "articulation"_a)
            .def(
                    "jointForce",
                    [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                        auto rows = articulation->getDofs();
                        return Eigen::Map<Eigen::VectorXf>(cache->jointForce, rows);
                    },
                    "articulation"_a)
            .def(
                    "jointTargetPositions",
                    [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                        auto rows = articulation->getDofs();
                        return Eigen::Map<Eigen::VectorXf>(cache->jointTargetPositions, rows);
                    },
                    "articulation"_a)
            .def(
                    "jointTargetVelocities",
                    [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                        auto rows = articulation->getDofs();
                        return Eigen::Map<Eigen::VectorXf>(cache->jointTargetVelocities, rows);
                    },
                    "articulation"_a)
            .def(
                    "linkVelocity",
                    [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                        auto links = articulation->getNbLinks();
                        return std::vector<PxSpatialVelocity>(cache->linkVelocity, cache->linkVelocity + links);
                    },
                    "articulation"_a)
            .def(
                    "linkAcceleration",
                    [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                        auto links = articulation->getNbLinks();
                        return std::vector<PxSpatialVelocity>(cache->linkAcceleration, cache->linkAcceleration + links);
                    },
                    "articulation"_a)
            .def(
                    "linkIncomingJointForce",
                    [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                        auto links = articulation->getNbLinks();
                        return std::vector<PxSpatialForce>(cache->linkIncomingJointForce,
                                                           cache->linkIncomingJointForce + links);
                    },
                    "articulation"_a)
            .def(
                    "linkForce",
                    [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                        auto links = articulation->getNbLinks();
                        return std::vector<PxVec3>(cache->linkForce, cache->linkForce + links);
                    },
                    "articulation"_a)
            .def(
                    "linkTorque",
                    [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                        auto links = articulation->getNbLinks();
                        return std::vector<PxVec3>(cache->linkTorque, cache->linkTorque + links);
                    },
                    "articulation"_a)
            .def(
                    "rootLinkData",
                    [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                        return std::vector<PxArticulationRootLinkData>(cache->rootLinkData, cache->rootLinkData + 1);
                    },
                    "articulation"_a);

    nb::class_<PxArticulationTendon>(m, "PxArticulationTendon")
            .def_prop_rw("stiffness", &PxArticulationTendon::getStiffness, &PxArticulationTendon::setStiffness)
            .def_prop_rw("damping", &PxArticulationTendon::getDamping, &PxArticulationTendon::setDamping)
            .def_prop_rw("limitStiffness", &PxArticulationTendon::getLimitStiffness,
                         &PxArticulationTendon::setLimitStiffness)
            .def_prop_rw("offset", &PxArticulationTendon::getOffset, &PxArticulationTendon::setOffset)
            .def("getArticulation", &PxArticulationTendon::getArticulation, nb::rv_policy::reference)
            .def("release", &PxArticulationTendon::release);

    nb::class_<PxArticulationSpatialTendon, PxArticulationTendon>(m, "PxArticulationSpatialTendon")
            .def("createAttachment", &PxArticulationSpatialTendon::createAttachment, "parent"_a, "coefficient"_a,
                 "relativeOffset"_a, "link"_a)
            .def("getNbAttachments", &PxArticulationSpatialTendon::getNbAttachments);
    nb::class_<PxArticulationAttachment>(m, "PxArticulationAttachment")
            .def_prop_rw("restLength", &PxArticulationAttachment::getRestLength,
                         &PxArticulationAttachment::setRestLength)
            .def_prop_rw("limitParameters", &PxArticulationAttachment::getLimitParameters,
                         &PxArticulationAttachment::setLimitParameters)
            .def_prop_rw("relativeOffset", &PxArticulationAttachment::getRelativeOffset,
                         &PxArticulationAttachment::setRelativeOffset)
            .def_prop_rw("coefficient", &PxArticulationAttachment::getCoefficient,
                         &PxArticulationAttachment::setCoefficient)
            .def("getLink", &PxArticulationAttachment::getLink, nb::rv_policy::reference)
            .def("getParent", &PxArticulationAttachment::getParent, nb::rv_policy::reference)
            .def("isLeaf", &PxArticulationAttachment::isLeaf)
            .def("getTendon", &PxArticulationAttachment::getTendon, nb::rv_policy::reference)
            .def("release", &PxArticulationAttachment::release);

    nb::class_<PxArticulationFixedTendon, PxArticulationTendon>(m, "PxArticulationFixedTendon")
            .def("createTendonJoint", &PxArticulationFixedTendon::createTendonJoint, "parent"_a, "axis"_a,
                 "coefficient"_a, "recipCoefficient"_a, "link"_a)
            .def("getNbTendonJoints", &PxArticulationFixedTendon::getNbTendonJoints)
            .def_prop_rw("restLength", &PxArticulationFixedTendon::getRestLength,
                         &PxArticulationFixedTendon::setRestLength)
            .def_prop_rw("limitParameters", &PxArticulationFixedTendon::getLimitParameters,
                         &PxArticulationFixedTendon::setLimitParameters);
    nb::class_<PxArticulationTendonJoint>(m, "PxArticulationTendonJoint")
            .def("setCoefficient", &PxArticulationTendonJoint::setCoefficient, "axis"_a, "coefficient"_a,
                 "recipCoefficient"_a)
            .def("getCoefficient",
                 [](PxArticulationTendonJoint* joint) {
                     std::tuple<PxArticulationAxis::Enum, PxReal, PxReal> result;
                     joint->getCoefficient(std::get<0>(result), std::get<1>(result), std::get<2>(result));
                     return result;
                 })
            .def("getLink", &PxArticulationTendonJoint::getLink, nb::rv_policy::reference)
            .def("getParent", &PxArticulationTendonJoint::getParent, nb::rv_policy::reference)
            .def("getTendon", &PxArticulationTendonJoint::getTendon, nb::rv_policy::reference)
            .def("release", &PxArticulationTendonJoint::release);
    nb::class_<PxArticulationTendonLimit>(m, "PxArticulationTendonLimit")
            .def_rw("lowLimit", &PxArticulationTendonLimit::lowLimit)
            .def_rw("highLimit", &PxArticulationTendonLimit::highLimit);

    nb::class_<PxResidual>(m, "PxResidual")
            .def(nb::init<>())
            .def_rw("rmsResidual", &PxResidual::rmsResidual)
            .def_rw("maxResidual", &PxResidual::maxResidual);

    nb::class_<PxResiduals>(m, "PxResiduals")
            .def(nb::init<>())
            .def_rw("positionIterationResidual", &PxResiduals::positionIterationResidual)
            .def_rw("velocityIterationResidual", &PxResiduals::velocityIterationResidual);

    nb::class_<PxArticulationMimicJoint>(m, "PxArticulationMimicJoint")
            .def("release", &PxArticulationMimicJoint::release)
            .def("getArticulation", &PxArticulationMimicJoint::getArticulation, nb::rv_policy::reference)
            .def_prop_rw("gearRatio", &PxArticulationMimicJoint::getGearRatio, &PxArticulationMimicJoint::setGearRatio)
            .def_prop_rw("offset", &PxArticulationMimicJoint::getOffset, &PxArticulationMimicJoint::setOffset)
            .def("getJointA", &PxArticulationMimicJoint::getJointA, nb::rv_policy::reference)
            .def("getJointB", &PxArticulationMimicJoint::getJointB, nb::rv_policy::reference)
            .def("getAxisA", &PxArticulationMimicJoint::getAxisA)
            .def("getAxisB", &PxArticulationMimicJoint::getAxisB);
}