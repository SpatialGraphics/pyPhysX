//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/eigen/dense.h>

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

    nb::enum_<PxArticulationKinematicFlag::Enum>(m, "PxArticulationKinematicFlag")
            .value("ePOSITION", PxArticulationKinematicFlag::Enum::ePOSITION)
            .value("eVELOCITY", PxArticulationKinematicFlag::Enum::eVELOCITY);

    nb::class_<PxArticulationReducedCoordinate>(m, "PxArticulationReducedCoordinate")
            .def("getScene", &PxArticulationReducedCoordinate::getScene, nb::rv_policy::reference)
            .def("setSolverIterationCounts", &PxArticulationReducedCoordinate::setSolverIterationCounts)
            .def("getSolverIterationCounts", &PxArticulationReducedCoordinate::getSolverIterationCounts)
            .def("isSleeping", &PxArticulationReducedCoordinate::isSleeping)
            .def("setSleepThreshold", &PxArticulationReducedCoordinate::setSleepThreshold)
            .def("getSleepThreshold", &PxArticulationReducedCoordinate::getSleepThreshold)
            .def("setStabilizationThreshold", &PxArticulationReducedCoordinate::setStabilizationThreshold)
            .def("getStabilizationThreshold", &PxArticulationReducedCoordinate::getStabilizationThreshold)
            .def("setWakeCounter", &PxArticulationReducedCoordinate::setWakeCounter)
            .def("getWakeCounter", &PxArticulationReducedCoordinate::getWakeCounter)
            .def("wakeUp", &PxArticulationReducedCoordinate::wakeUp)
            .def("putToSleep", &PxArticulationReducedCoordinate::putToSleep)
            .def("setMaxCOMLinearVelocity", &PxArticulationReducedCoordinate::setMaxCOMLinearVelocity)
            .def("getMaxCOMLinearVelocity", &PxArticulationReducedCoordinate::getMaxCOMLinearVelocity)
            .def("setMaxCOMAngularVelocity", &PxArticulationReducedCoordinate::setMaxCOMAngularVelocity)
            .def("getMaxCOMAngularVelocity", &PxArticulationReducedCoordinate::getMaxCOMAngularVelocity)
            .def("createLink", &PxArticulationReducedCoordinate::createLink)
            .def("release", &PxArticulationReducedCoordinate::release)
            .def("getNbLinks", &PxArticulationReducedCoordinate::getNbLinks)
            .def("getNbShapes", &PxArticulationReducedCoordinate::getNbShapes)
            .def("setName", &PxArticulationReducedCoordinate::setName)
            .def("getName", &PxArticulationReducedCoordinate::getName)
            .def("getWorldBounds", &PxArticulationReducedCoordinate::getWorldBounds)
            .def("getAggregate", &PxArticulationReducedCoordinate::getAggregate)
            .def("setArticulationFlags",
                 [](PxArticulationReducedCoordinate* articulation, int flags) {
                     articulation->setArticulationFlags(PxArticulationFlags(flags));
                 })
            .def("setArticulationFlag", &PxArticulationReducedCoordinate::setArticulationFlag)
            .def("getArticulationFlags",
                 [](PxArticulationReducedCoordinate* articulation) {
                     return articulation->getArticulationFlags().operator uint32_t();
                 })
            .def("getDofs", &PxArticulationReducedCoordinate::getDofs)

            .def("createCache", &PxArticulationReducedCoordinate::createCache, nb::rv_policy::reference)
            .def("getCacheDataSize", &PxArticulationReducedCoordinate::getCacheDataSize)
            .def("zeroCache", &PxArticulationReducedCoordinate::zeroCache)
            .def(
                    "applyCache",
                    [](PxArticulationReducedCoordinate* articulation, PxArticulationCache& cache, const int flags,
                       bool autowake) {
                        articulation->applyCache(cache, PxArticulationCacheFlags(flags), autowake);
                    },
                    "cache"_a, "flags"_a, "autowake"_a = true)
            .def(
                    "copyInternalStateToCache",
                    [](PxArticulationReducedCoordinate* articulation, PxArticulationCache& cache, const int flags) {
                        articulation->copyInternalStateToCache(cache, PxArticulationCacheFlags(flags));
                    },
                    "cache"_a, "flags"_a)
            .def("packJointData", &PxArticulationReducedCoordinate::packJointData)
            .def("unpackJointData", &PxArticulationReducedCoordinate::unpackJointData)
            .def("commonInit", &PxArticulationReducedCoordinate::commonInit)
            .def("computeGeneralizedGravityForce", &PxArticulationReducedCoordinate::computeGeneralizedGravityForce)
            .def("computeCoriolisAndCentrifugalForce",
                 &PxArticulationReducedCoordinate::computeCoriolisAndCentrifugalForce)
            .def("computeGeneralizedExternalForce", &PxArticulationReducedCoordinate::computeGeneralizedExternalForce)
            .def("computeJointAcceleration", &PxArticulationReducedCoordinate::computeJointAcceleration)
            .def("computeJointForce", &PxArticulationReducedCoordinate::computeJointForce)
            .def("computeDenseJacobian", &PxArticulationReducedCoordinate::computeDenseJacobian)
            .def("computeCoefficientMatrix", &PxArticulationReducedCoordinate::computeCoefficientMatrix)
            .def("computeLambda", &PxArticulationReducedCoordinate::computeLambda)
            .def("computeGeneralizedMassMatrix", &PxArticulationReducedCoordinate::computeGeneralizedMassMatrix)
            .def("addLoopJoint", &PxArticulationReducedCoordinate::addLoopJoint)
            .def("removeLoopJoint", &PxArticulationReducedCoordinate::removeLoopJoint)
            .def("getNbLoopJoints", &PxArticulationReducedCoordinate::getNbLoopJoints)
            .def("getCoefficientMatrixSize", &PxArticulationReducedCoordinate::getCoefficientMatrixSize)
            .def("setRootGlobalPose", &PxArticulationReducedCoordinate::setRootGlobalPose)
            .def("getRootGlobalPose", &PxArticulationReducedCoordinate::getRootGlobalPose)
            .def("setRootLinearVelocity", &PxArticulationReducedCoordinate::setRootLinearVelocity)
            .def("getRootLinearVelocity", &PxArticulationReducedCoordinate::getRootLinearVelocity)
            .def("setRootAngularVelocity", &PxArticulationReducedCoordinate::setRootAngularVelocity)
            .def("getRootAngularVelocity", &PxArticulationReducedCoordinate::getRootAngularVelocity)
            .def("getLinkAcceleration", &PxArticulationReducedCoordinate::getLinkAcceleration)
            .def("getGpuArticulationIndex", &PxArticulationReducedCoordinate::getGpuArticulationIndex)
            .def("getGPUIndex", &PxArticulationReducedCoordinate::getGPUIndex)
            .def("createSpatialTendon", &PxArticulationReducedCoordinate::createSpatialTendon)
            .def("createFixedTendon", &PxArticulationReducedCoordinate::createFixedTendon)
            .def("getNbSpatialTendons", &PxArticulationReducedCoordinate::getNbSpatialTendons)
            .def("getNbFixedTendons", &PxArticulationReducedCoordinate::getNbFixedTendons)
            .def("createMimicJoint", &PxArticulationReducedCoordinate::createMimicJoint)
            .def("getNbMimicJoints", &PxArticulationReducedCoordinate::getNbMimicJoints)
            .def(
                    "updateKinematic",
                    [](PxArticulationReducedCoordinate* articulation, int flags) {
                        articulation->updateKinematic(PxArticulationKinematicFlags(flags));
                    },
                    "flags"_a)
            .def("getSolverResidual", &PxArticulationReducedCoordinate::getSolverResidual);

    nb::class_<PxArticulationJointReducedCoordinate>(m, "PxArticulationJointReducedCoordinate")
            .def("getParentArticulationLink", &PxArticulationJointReducedCoordinate::getParentArticulationLink)
            .def("setParentPose", &PxArticulationJointReducedCoordinate::setParentPose)
            .def("getParentPose", &PxArticulationJointReducedCoordinate::getParentPose)
            .def("getChildArticulationLink", &PxArticulationJointReducedCoordinate::getChildArticulationLink)
            .def("setChildPose", &PxArticulationJointReducedCoordinate::setChildPose)
            .def("getChildPose", &PxArticulationJointReducedCoordinate::getChildPose)
            .def("setJointType", &PxArticulationJointReducedCoordinate::setJointType)
            .def("getJointType", &PxArticulationJointReducedCoordinate::getJointType)
            .def("setMotion", &PxArticulationJointReducedCoordinate::setMotion)
            .def("getMotion", &PxArticulationJointReducedCoordinate::getMotion)
            .def("setLimitParams", &PxArticulationJointReducedCoordinate::setLimitParams)
            .def("getLimitParams", &PxArticulationJointReducedCoordinate::getLimitParams)
            .def("setDriveParams", &PxArticulationJointReducedCoordinate::setDriveParams)
            .def("getDriveParams", &PxArticulationJointReducedCoordinate::getDriveParams)
            .def("setDriveTarget", &PxArticulationJointReducedCoordinate::setDriveTarget)
            .def("getDriveTarget", &PxArticulationJointReducedCoordinate::getDriveTarget)
            .def("setDriveVelocity", &PxArticulationJointReducedCoordinate::setDriveVelocity)
            .def("getDriveVelocity", &PxArticulationJointReducedCoordinate::getDriveVelocity)
            .def("setArmature", &PxArticulationJointReducedCoordinate::setArmature)
            .def("getArmature", &PxArticulationJointReducedCoordinate::getArmature)
            .def("setFrictionCoefficient", &PxArticulationJointReducedCoordinate::setFrictionCoefficient)
            .def("getFrictionCoefficient", &PxArticulationJointReducedCoordinate::getFrictionCoefficient)
            .def("setMaxJointVelocity", &PxArticulationJointReducedCoordinate::setMaxJointVelocity)
            .def("getMaxJointVelocity", &PxArticulationJointReducedCoordinate::getMaxJointVelocity)
            .def("setJointPosition", &PxArticulationJointReducedCoordinate::setJointPosition)
            .def("getJointPosition", &PxArticulationJointReducedCoordinate::getJointPosition)
            .def("setJointVelocity", &PxArticulationJointReducedCoordinate::setJointVelocity)
            .def("getJointVelocity", &PxArticulationJointReducedCoordinate::getJointVelocity);

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
            .def_rw("force", &PxSpatialForce::force)
            .def_rw("torque", &PxSpatialForce::torque);

    nb::class_<PxSpatialVelocity>(m, "PxSpatialVelocity")
            .def_rw("linear", &PxSpatialVelocity::linear)
            .def_rw("angular", &PxSpatialVelocity::angular);

    nb::class_<PxArticulationRootLinkData>(m, "PxArticulationRootLinkData")
            .def_rw("transform", &PxArticulationRootLinkData::transform)
            .def_rw("worldLinVel", &PxArticulationRootLinkData::worldLinVel)
            .def_rw("worldAngVel", &PxArticulationRootLinkData::worldAngVel)
            .def_rw("worldLinAccel", &PxArticulationRootLinkData::worldLinAccel)
            .def_rw("worldAngAccel", &PxArticulationRootLinkData::worldAngAccel);

    nb::class_<PxArticulationCache>(m, "PxArticulationCache")
            .def("release", &PxArticulationCache::release)
            .def("externalForces",
                 [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                     auto links = articulation->getNbLinks();
                     return std::vector<PxSpatialForce>(cache->externalForces, cache->externalForces + links);
                 })
            .def("denseJacobian",
                 [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                     auto rows = articulation->getNbLinks() * 6;
                     auto cols = articulation->getDofs() + 6;
                     return Eigen::Map<Eigen::MatrixXf>(cache->denseJacobian, rows, cols);
                 })
            .def("massMatrix",
                 [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                     auto rows = articulation->getDofs();
                     return Eigen::Map<Eigen::MatrixXf>(cache->massMatrix, rows, rows);
                 })
            .def("jointVelocity",
                 [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                     auto rows = articulation->getDofs();
                     return Eigen::Map<Eigen::VectorXf>(cache->jointVelocity, rows);
                 })
            .def("jointAcceleration",
                 [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                     auto rows = articulation->getDofs();
                     return Eigen::Map<Eigen::VectorXf>(cache->jointAcceleration, rows);
                 })
            .def("jointPosition",
                 [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                     auto rows = articulation->getDofs();
                     return Eigen::Map<Eigen::VectorXf>(cache->jointPosition, rows);
                 })
            .def("jointForce",
                 [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                     auto rows = articulation->getDofs();
                     return Eigen::Map<Eigen::VectorXf>(cache->jointForce, rows);
                 })
            .def("jointTargetPositions",
                 [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                     auto rows = articulation->getDofs();
                     return Eigen::Map<Eigen::VectorXf>(cache->jointTargetPositions, rows);
                 })
            .def("jointTargetVelocities",
                 [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                     auto rows = articulation->getDofs();
                     return Eigen::Map<Eigen::VectorXf>(cache->jointTargetVelocities, rows);
                 })
            .def("linkVelocity",
                 [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                     auto links = articulation->getNbLinks();
                     return std::vector<PxSpatialVelocity>(cache->linkVelocity, cache->linkVelocity + links);
                 })
            .def("linkAcceleration",
                 [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                     auto links = articulation->getNbLinks();
                     return std::vector<PxSpatialVelocity>(cache->linkAcceleration, cache->linkAcceleration + links);
                 })
            .def("linkIncomingJointForce",
                 [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                     auto links = articulation->getNbLinks();
                     return std::vector<PxSpatialForce>(cache->linkIncomingJointForce,
                                                        cache->linkIncomingJointForce + links);
                 })
            .def("linkForce",
                 [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                     auto links = articulation->getNbLinks();
                     return std::vector<PxVec3>(cache->linkForce, cache->linkForce + links);
                 })
            .def("linkTorque",
                 [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                     auto links = articulation->getNbLinks();
                     return std::vector<PxVec3>(cache->linkTorque, cache->linkTorque + links);
                 })
            .def("rootLinkData", [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                return std::vector<PxArticulationRootLinkData>(cache->rootLinkData, cache->rootLinkData + 1);
            });

    nb::class_<PxArticulationTendon>(m, "PxArticulationTendon")
            .def("setStiffness", &PxArticulationTendon::setStiffness)
            .def("getStiffness", &PxArticulationTendon::getStiffness)
            .def("setDamping", &PxArticulationTendon::setDamping)
            .def("getDamping", &PxArticulationTendon::getDamping)
            .def("setLimitStiffness", &PxArticulationTendon::setLimitStiffness)
            .def("getLimitStiffness", &PxArticulationTendon::getLimitStiffness)
            .def("setOffset", &PxArticulationTendon::setOffset)
            .def("getOffset", &PxArticulationTendon::getOffset)
            .def("getArticulation", &PxArticulationTendon::getArticulation, nb::rv_policy::reference)
            .def("release", &PxArticulationTendon::release);

    nb::class_<PxArticulationSpatialTendon, PxArticulationTendon>(m, "PxArticulationSpatialTendon")
            .def("createAttachment", &PxArticulationSpatialTendon::createAttachment)
            .def("getNbAttachments", &PxArticulationSpatialTendon::getNbAttachments);
    nb::class_<PxArticulationAttachment>(m, "PxArticulationAttachment")
            .def("setRestLength", &PxArticulationAttachment::setRestLength)
            .def("getRestLength", &PxArticulationAttachment::getRestLength)
            .def("setLimitParameters", &PxArticulationAttachment::setLimitParameters)
            .def("getLimitParameters", &PxArticulationAttachment::getLimitParameters)
            .def("setRelativeOffset", &PxArticulationAttachment::setRelativeOffset)
            .def("getRelativeOffset", &PxArticulationAttachment::getRelativeOffset)
            .def("setCoefficient", &PxArticulationAttachment::setCoefficient)
            .def("getCoefficient", &PxArticulationAttachment::getCoefficient)
            .def("getLink", &PxArticulationAttachment::getLink, nb::rv_policy::reference)
            .def("getParent", &PxArticulationAttachment::getParent, nb::rv_policy::reference)
            .def("isLeaf", &PxArticulationAttachment::isLeaf)
            .def("getTendon", &PxArticulationAttachment::getTendon, nb::rv_policy::reference)
            .def("release", &PxArticulationAttachment::release);

    nb::class_<PxArticulationFixedTendon, PxArticulationTendon>(m, "PxArticulationFixedTendon")
            .def("createTendonJoint", &PxArticulationFixedTendon::createTendonJoint)
            .def("getNbTendonJoints", &PxArticulationFixedTendon::getNbTendonJoints)
            .def("setRestLength", &PxArticulationFixedTendon::setRestLength)
            .def("getRestLength", &PxArticulationFixedTendon::getRestLength)
            .def("setLimitParameters", &PxArticulationFixedTendon::setLimitParameters)
            .def("getLimitParameters", &PxArticulationFixedTendon::getLimitParameters);
    nb::class_<PxArticulationTendonJoint>(m, "PxArticulationTendonJoint")
            .def("setCoefficient", &PxArticulationTendonJoint::setCoefficient)
            .def("getCoefficient", &PxArticulationTendonJoint::getCoefficient)
            .def("getLink", &PxArticulationTendonJoint::getLink, nb::rv_policy::reference)
            .def("getParent", &PxArticulationTendonJoint::getParent, nb::rv_policy::reference)
            .def("getTendon", &PxArticulationTendonJoint::getTendon, nb::rv_policy::reference)
            .def("release", &PxArticulationTendonJoint::release);
    nb::class_<PxArticulationTendonLimit>(m, "PxArticulationTendonLimit")
            .def_rw("lowLimit", &PxArticulationTendonLimit::lowLimit)
            .def_rw("highLimit", &PxArticulationTendonLimit::highLimit);

    nb::class_<PxResidual>(m, "PxResidual")
            .def_rw("rmsResidual", &PxResidual::rmsResidual)
            .def_rw("maxResidual", &PxResidual::maxResidual);

    nb::class_<PxResiduals>(m, "PxResiduals")
            .def_rw("positionIterationResidual", &PxResiduals::positionIterationResidual)
            .def_rw("velocityIterationResidual", &PxResiduals::velocityIterationResidual);

    nb::class_<PxArticulationMimicJoint>(m, "PxArticulationMimicJoint")
            .def("release", &PxArticulationMimicJoint::release)
            .def("getArticulation", &PxArticulationMimicJoint::getArticulation, nb::rv_policy::reference)
            .def("getGearRatio", &PxArticulationMimicJoint::getGearRatio)
            .def("setGearRatio", &PxArticulationMimicJoint::setGearRatio)
            .def("getOffset", &PxArticulationMimicJoint::getOffset)
            .def("setOffset", &PxArticulationMimicJoint::setOffset)
            .def("getJointA", &PxArticulationMimicJoint::getJointA, nb::rv_policy::reference)
            .def("getJointB", &PxArticulationMimicJoint::getJointB, nb::rv_policy::reference)
            .def("getAxisA", &PxArticulationMimicJoint::getAxisA)
            .def("getAxisB", &PxArticulationMimicJoint::getAxisB);
}