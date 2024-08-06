//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>
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
            .def("applyCache", &PxArticulationReducedCoordinate::applyCache)
            .def("copyInternalStateToCache", &PxArticulationReducedCoordinate::copyInternalStateToCache)
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
            .def("updateKinematic", &PxArticulationReducedCoordinate::updateKinematic)
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

    nb::class_<PxArticulationCache>(m, "PxArticulationCache")
            .def("release", &PxArticulationCache::release)
            .def("denseJacobian", [](PxArticulationCache* cache, PxArticulationReducedCoordinate* articulation) {
                auto dofs = articulation->getDofs();
                return Eigen::Map<Eigen::VectorXf>(cache->denseJacobian, dofs);
            });
}