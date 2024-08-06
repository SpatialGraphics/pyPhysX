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

void bindController(nb::module_& m) {
    nb::enum_<PxCapsuleClimbingMode::Enum>(m, "PxCapsuleClimbingMode")
            .value("eEASY", PxCapsuleClimbingMode::Enum::eEASY)
            .value("eCONSTRAINED", PxCapsuleClimbingMode::Enum::eCONSTRAINED)
            .value("eLAST", PxCapsuleClimbingMode::Enum::eLAST);
    nb::enum_<PxControllerShapeType::Enum>(m, "PxControllerShapeType")
            .value("eBOX", PxControllerShapeType::Enum::eBOX)
            .value("eCAPSULE", PxControllerShapeType::Enum::eCAPSULE);
    nb::enum_<PxControllerNonWalkableMode::Enum>(m, "PxControllerNonWalkableMode")
            .value("ePREVENT_CLIMBING", PxControllerNonWalkableMode::Enum::ePREVENT_CLIMBING)
            .value("ePREVENT_CLIMBING_AND_FORCE_SLIDING",
                   PxControllerNonWalkableMode::Enum::ePREVENT_CLIMBING_AND_FORCE_SLIDING);
    nb::enum_<PxControllerCollisionFlag::Enum>(m, "PxControllerCollisionFlag")
            .value("eCOLLISION_SIDES", PxControllerCollisionFlag::Enum::eCOLLISION_SIDES)
            .value("eCOLLISION_UP", PxControllerCollisionFlag::Enum::eCOLLISION_UP)
            .value("eCOLLISION_DOWN", PxControllerCollisionFlag::Enum::eCOLLISION_DOWN);

    nb::class_<PxControllerManager>(m, "PxControllerManager")
            .def("release", &PxControllerManager::release)
            .def("getScene", &PxControllerManager::getScene, nb::rv_policy::reference)
            .def("getNbControllers", &PxControllerManager::getNbControllers)
            .def("createController", &PxControllerManager::createController)
            .def("purgeControllers", &PxControllerManager::purgeControllers)
            .def("getRenderBuffer", &PxControllerManager::getRenderBuffer)
            .def("setDebugRenderingFlags", &PxControllerManager::setDebugRenderingFlags)
            .def("getNbObstacleContexts", &PxControllerManager::getNbObstacleContexts)
            .def("getObstacleContext", &PxControllerManager::getObstacleContext)
            .def("createObstacleContext", &PxControllerManager::createObstacleContext)
            .def("computeInteractions", &PxControllerManager::computeInteractions)
            .def("setTessellation", &PxControllerManager::setTessellation)
            .def("setOverlapRecoveryModule", &PxControllerManager::setOverlapRecoveryModule)
            .def("setPreciseSweeps", &PxControllerManager::setPreciseSweeps)
            .def("setPreventVerticalSlidingAgainstCeiling",
                 &PxControllerManager::setPreventVerticalSlidingAgainstCeiling)
            .def("shiftOrigin", &PxControllerManager::shiftOrigin);

    nb::class_<PxControllerDesc>(m, "PxControllerDesc")
            .def("isValid", &PxControllerDesc::isValid)
            .def("getType", &PxControllerDesc::getType)
            .def_rw("position", &PxControllerDesc::position)
            .def_rw("upDirection", &PxControllerDesc::upDirection)
            .def_rw("slopeLimit", &PxControllerDesc::slopeLimit)
            .def_rw("invisibleWallHeight", &PxControllerDesc::invisibleWallHeight)
            .def_rw("maxJumpHeight", &PxControllerDesc::maxJumpHeight)
            .def_rw("contactOffset", &PxControllerDesc::contactOffset)
            .def_rw("stepOffset", &PxControllerDesc::stepOffset)
            .def_rw("density", &PxControllerDesc::density)
            .def_rw("scaleCoeff", &PxControllerDesc::scaleCoeff)
            .def_rw("volumeGrowth", &PxControllerDesc::volumeGrowth)
            .def_rw("reportCallback", &PxControllerDesc::reportCallback)
            .def_rw("behaviorCallback", &PxControllerDesc::behaviorCallback)
            .def_rw("nonWalkableMode", &PxControllerDesc::nonWalkableMode)
            .def_rw("material", &PxControllerDesc::material)
            .def_rw("registerDeletionListener", &PxControllerDesc::registerDeletionListener)
            .def_rw("clientID", &PxControllerDesc::clientID);

    nb::class_<PxCapsuleControllerDesc, PxControllerDesc>(m, "PxCapsuleControllerDesc")
            .def("setToDefault", &PxCapsuleControllerDesc::setToDefault)
            .def("isValid", &PxCapsuleControllerDesc::isValid)
            .def_rw("radius", &PxCapsuleControllerDesc::radius)
            .def_rw("height", &PxCapsuleControllerDesc::height)
            .def_rw("climbingMode", &PxCapsuleControllerDesc::climbingMode);

    nb::class_<PxBoxControllerDesc, PxControllerDesc>(m, "PxBoxControllerDesc")
            .def("setToDefault", &PxBoxControllerDesc::setToDefault)
            .def("isValid", &PxBoxControllerDesc::isValid)
            .def_rw("halfHeight", &PxBoxControllerDesc::halfHeight)
            .def_rw("halfSideExtent", &PxBoxControllerDesc::halfSideExtent)
            .def_rw("halfForwardExtent", &PxBoxControllerDesc::halfForwardExtent);

    nb::class_<PxController>(m, "PxController")
            .def("getType", &PxController::getType)
            .def("release", &PxController::release)
            .def("move", &PxController::move)
            .def("setPosition", &PxController::setPosition)
            .def("getPosition", &PxController::getPosition)
            .def("setFootPosition", &PxController::setFootPosition)
            .def("getFootPosition", &PxController::getFootPosition)
            .def("getActor", &PxController::getActor)
            .def("setStepOffset", &PxController::setStepOffset)
            .def("getStepOffset", &PxController::getStepOffset)
            .def("setNonWalkableMode", &PxController::setNonWalkableMode)
            .def("getNonWalkableMode", &PxController::getNonWalkableMode)
            .def("getContactOffset", &PxController::getContactOffset)
            .def("setContactOffset", &PxController::setContactOffset)
            .def("getUpDirection", &PxController::getUpDirection)
            .def("setUpDirection", &PxController::setUpDirection)
            .def("getSlopeLimit", &PxController::getSlopeLimit)
            .def("setSlopeLimit", &PxController::setSlopeLimit)
            .def("invalidateCache", &PxController::invalidateCache)
            .def("getScene", &PxController::getScene, nb::rv_policy::reference)
            .def("getState", &PxController::getState)
            .def("getStats", &PxController::getStats)
            .def("invalidateCache", &PxController::resize);

    nb::class_<PxCapsuleController, PxController>(m, "PxCapsuleController")
            .def("getRadius", &PxCapsuleController::getRadius)
            .def("setRadius", &PxCapsuleController::setRadius)
            .def("getHeight", &PxCapsuleController::getHeight)
            .def("setHeight", &PxCapsuleController::setHeight)
            .def("getClimbingMode", &PxCapsuleController::getClimbingMode)
            .def("setClimbingMode", &PxCapsuleController::setClimbingMode);

    nb::class_<PxBoxController, PxController>(m, "PxBoxController")
            .def("getHalfHeight", &PxBoxController::getHalfHeight)
            .def("getHalfSideExtent", &PxBoxController::getHalfSideExtent)
            .def("getHalfForwardExtent", &PxBoxController::getHalfForwardExtent)
            .def("setHalfHeight", &PxBoxController::setHalfHeight)
            .def("setHalfSideExtent", &PxBoxController::setHalfSideExtent)
            .def("setHalfForwardExtent", &PxBoxController::setHalfForwardExtent);
}