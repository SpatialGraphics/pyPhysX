//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/function.h>

#include "py_utils.h"

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
    bindFlags<PxControllerCollisionFlag::Enum, PxU8>(m, "PxControllerCollisionFlags");

    nb::enum_<PxControllerBehaviorFlag::Enum>(m, "PxControllerBehaviorFlag")
            .value("eCCT_CAN_RIDE_ON_OBJECT", PxControllerBehaviorFlag::Enum::eCCT_CAN_RIDE_ON_OBJECT)
            .value("eCCT_SLIDE", PxControllerBehaviorFlag::Enum::eCCT_SLIDE)
            .value("eCCT_USER_DEFINED_RIDE", PxControllerBehaviorFlag::Enum::eCCT_USER_DEFINED_RIDE);
    bindFlags<PxControllerBehaviorFlag::Enum, PxU8>(m, "PxControllerBehaviorFlags");

    nb::enum_<PxControllerDebugRenderFlag::Enum>(m, "PxControllerDebugRenderFlag")
            .value("eTEMPORAL_BV", PxControllerDebugRenderFlag::Enum::eTEMPORAL_BV)
            .value("eCACHED_BV", PxControllerDebugRenderFlag::Enum::eCACHED_BV)
            .value("eOBSTACLES", PxControllerDebugRenderFlag::Enum::eOBSTACLES)
            .value("eNONE", PxControllerDebugRenderFlag::Enum::eNONE)
            .value("eALL", PxControllerDebugRenderFlag::Enum::eALL);
    bindFlags<PxControllerDebugRenderFlag::Enum, PxU32>(m, "PxControllerDebugRenderFlags");

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
            .def("move",
                 [](PxController* controller, const PxVec3& disp, PxF32 minDist, PxF32 elapsedTime,
                    const PxControllerFilters& filters, const PxObstacleContext* obstacles) {
                     return controller->move(disp, minDist, elapsedTime, filters, obstacles).operator uint32_t();
                 })
            .def_prop_rw("position", &PxController::getPosition, &PxController::setPosition)
            .def_prop_rw("footPosition", &PxController::getFootPosition, &PxController::setFootPosition)
            .def("getActor", &PxController::getActor)
            .def_prop_rw("stepOffset", &PxController::getStepOffset, &PxController::setStepOffset)
            .def_prop_rw("nonWalkableMode", &PxController::getNonWalkableMode, &PxController::setNonWalkableMode)
            .def_prop_rw("contactOffset", &PxController::getContactOffset, &PxController::setContactOffset)
            .def_prop_rw("upDirection", &PxController::getUpDirection, &PxController::setUpDirection)
            .def_prop_rw("slopeLimit", &PxController::getSlopeLimit, &PxController::setSlopeLimit)
            .def("invalidateCache", &PxController::invalidateCache)
            .def("getScene", &PxController::getScene, nb::rv_policy::reference)
            .def("getState", &PxController::getState)
            .def("getStats", &PxController::getStats)
            .def("invalidateCache", &PxController::resize);

    nb::class_<PxCapsuleController, PxController>(m, "PxCapsuleController")
            .def_prop_rw("radius", &PxCapsuleController::getRadius, &PxCapsuleController::setRadius)
            .def_prop_rw("height", &PxCapsuleController::getHeight, &PxCapsuleController::setHeight)
            .def_prop_rw("climbingMode", &PxCapsuleController::getClimbingMode, &PxCapsuleController::setClimbingMode);

    nb::class_<PxBoxController, PxController>(m, "PxBoxController")
            .def_prop_rw("halfHeight", &PxBoxController::getHalfHeight, &PxBoxController::setHalfHeight)
            .def_prop_rw("halfSideExtent", &PxBoxController::getHalfSideExtent, &PxBoxController::setHalfSideExtent)
            .def_prop_rw("halfForwardExtent", &PxBoxController::getHalfForwardExtent,
                         &PxBoxController::setHalfForwardExtent);

    nb::class_<PxControllerState>(m, "PxControllerState")
            .def_rw("deltaXP", &PxControllerState::deltaXP)
            .def_rw("touchedShape", &PxControllerState::touchedShape)
            .def_rw("touchedActor", &PxControllerState::touchedActor)
            .def_rw("touchedObstacleHandle", &PxControllerState::touchedObstacleHandle)
            .def_rw("collisionFlags", &PxControllerState::collisionFlags)
            .def_rw("standOnAnotherCCT", &PxControllerState::standOnAnotherCCT)
            .def_rw("standOnObstacle", &PxControllerState::standOnObstacle)
            .def_rw("isMovingUp", &PxControllerState::isMovingUp);

    nb::class_<PxControllerStats>(m, "PxControllerStats")
            .def_rw("nbIterations", &PxControllerStats::nbIterations)
            .def_rw("nbFullUpdates", &PxControllerStats::nbFullUpdates)
            .def_rw("nbPartialUpdates", &PxControllerStats::nbPartialUpdates)
            .def_rw("nbTessellation", &PxControllerStats::nbTessellation);

    nb::class_<PxObstacleContext>(m, "PxObstacleContext")
            .def("release", &PxObstacleContext::release)
            .def("getControllerManager", &PxObstacleContext::getControllerManager)
            .def("addObstacle", &PxObstacleContext::addObstacle)
            .def("removeObstacle", &PxObstacleContext::removeObstacle)
            .def("updateObstacle", &PxObstacleContext::updateObstacle)
            .def("getNbObstacles", &PxObstacleContext::getNbObstacles)
            .def("getObstacle", &PxObstacleContext::getObstacle)
            .def("getObstacleByHandle", &PxObstacleContext::getObstacleByHandle);

    nb::class_<PxObstacle>(m, "PxObstacle").def("getType", &PxObstacle::getType);

    nb::class_<PxBoxObstacle, PxObstacle>(m, "PxBoxObstacle")
            .def(nb::init<>())
            .def_rw("mHalfExtents", &PxBoxObstacle::mHalfExtents);

    nb::class_<PxCapsuleObstacle, PxObstacle>(m, "PxCapsuleObstacle")
            .def(nb::init<>())
            .def_rw("mHalfHeight", &PxCapsuleObstacle::mHalfHeight)
            .def_rw("mRadius", &PxCapsuleObstacle::mRadius);

    class ControllerBehaviorCallback : public PxControllerBehaviorCallback {
    public:
        ControllerBehaviorCallback(
                const std::function<PxControllerBehaviorFlags(const PxController& controller)>& c1,
                const std::function<PxControllerBehaviorFlags(const PxObstacle& obstacle)>& c2,
                const std::function<PxControllerBehaviorFlags(const PxShape& shape, const PxActor& actor)>& c3)
            : c1{c1}, c2{c2}, c3{c3} {}

        PxControllerBehaviorFlags getBehaviorFlags(const PxController& controller) override { return c1(controller); }

        PxControllerBehaviorFlags getBehaviorFlags(const PxObstacle& obstacle) override { return c2(obstacle); }

        PxControllerBehaviorFlags getBehaviorFlags(const PxShape& shape, const PxActor& actor) override {
            return c3(shape, actor);
        }

    private:
        std::function<PxControllerBehaviorFlags(const PxController& controller)> c1;
        std::function<PxControllerBehaviorFlags(const PxObstacle& obstacle)> c2;
        std::function<PxControllerBehaviorFlags(const PxShape& shape, const PxActor& actor)> c3;
    };
    nb::class_<PxControllerBehaviorCallback> pxControllerBehaviorCallback(m, "PxControllerBehaviorCallback");
    nb::class_<ControllerBehaviorCallback, PxControllerBehaviorCallback>(m, "ControllerBehaviorCallback")
            .def(nb::init<
                    const std::function<PxControllerBehaviorFlags(const PxController& controller)>&,
                    const std::function<PxControllerBehaviorFlags(const PxObstacle& obstacle)>&,
                    const std::function<PxControllerBehaviorFlags(const PxShape& shape, const PxActor& actor)>&>());

    class UserControllerHitReport : public PxUserControllerHitReport {
    public:
        UserControllerHitReport(const std::function<void(const PxControllersHit& hit)>& c1,
                                const std::function<void(const PxControllerObstacleHit& hit)>& c2,
                                const std::function<void(const PxControllerShapeHit& hit)>& c3)
            : c1(c1), c2(c2), c3(c3) {}

        void onControllerHit(const PxControllersHit& hit) override { return c1(hit); }

        void onObstacleHit(const PxControllerObstacleHit& hit) override { return c2(hit); }

        void onShapeHit(const PxControllerShapeHit& hit) override { return c3(hit); }

    private:
        std::function<void(const PxControllersHit& hit)> c1;
        std::function<void(const PxControllerObstacleHit& hit)> c2;
        std::function<void(const PxControllerShapeHit& hit)> c3;
    };
    nb::class_<PxUserControllerHitReport> pxUserControllerHitReport(m, "PxUserControllerHitReport");
    nb::class_<UserControllerHitReport, PxUserControllerHitReport>(m, "UserControllerHitReport")
            .def(nb::init<const std::function<void(const PxControllersHit& hit)>&,
                          const std::function<void(const PxControllerObstacleHit& hit)>&,
                          const std::function<void(const PxControllerShapeHit& hit)>&>());
    nb::class_<PxControllerHit>(m, "PxControllerHit")
            .def_rw("controller", &PxControllerHit::controller)
            .def_rw("worldPos", &PxControllerHit::worldPos)
            .def_rw("worldNormal", &PxControllerHit::worldNormal)
            .def_rw("dir", &PxControllerHit::dir)
            .def_rw("length", &PxControllerHit::length);
    nb::class_<PxControllerShapeHit, PxControllerHit>(m, "PxControllerShapeHit")
            .def_rw("shape", &PxControllerShapeHit::shape)
            .def_rw("actor", &PxControllerShapeHit::actor)
            .def_rw("triangleIndex", &PxControllerShapeHit::triangleIndex);
    nb::class_<PxControllersHit, PxControllerHit>(m, "PxControllersHit").def_rw("other", &PxControllersHit::other);
    nb::class_<PxControllerObstacleHit, PxControllerHit> pxControllerObstacleHit(m, "PxControllerObstacleHit");

    class ControllerFilterCallback : public PxControllerFilterCallback {
    public:
        explicit ControllerFilterCallback(
                const std::function<bool(const physx::PxController& a, const physx::PxController& b)>& c)
            : c(c) {}

        bool filter(const physx::PxController& a, const physx::PxController& b) override { return c(a, b); }

    private:
        std::function<bool(const physx::PxController& a, const physx::PxController& b)> c;
    };
    nb::class_<PxControllerFilterCallback> pxControllerFilterCallback(m, "PxControllerFilterCallback");
    nb::class_<ControllerFilterCallback, PxControllerFilterCallback>(m, "ControllerFilterCallback")
            .def(nb::init<const std::function<bool(const physx::PxController& a, const physx::PxController& b)>&>());

    nb::class_<PxControllerFilters>(m, "PxControllerFilters")
            .def(nb::init<const PxFilterData*, PxQueryFilterCallback*, PxControllerFilterCallback*>());
}