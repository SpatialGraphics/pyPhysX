//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

void bindArticulationReducedCoordinate(nb::module_& m) {
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
            .def("setArticulationFlags", &PxArticulationReducedCoordinate::setArticulationFlags)
            .def("setArticulationFlag", &PxArticulationReducedCoordinate::setArticulationFlag)
            .def("getArticulationFlags", &PxArticulationReducedCoordinate::getArticulationFlags)
            .def("getDofs", &PxArticulationReducedCoordinate::getDofs)

            .def("createCache", &PxArticulationReducedCoordinate::createCache)
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
}