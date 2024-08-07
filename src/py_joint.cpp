//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/tuple.h>

#include "py_utils.h"

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

void bindJoint(nb::module_& m) {
    nb::enum_<PxD6Axis::Enum>(m, "PxD6Axis")
            .value("eX", PxD6Axis::Enum::eX)
            .value("eY", PxD6Axis::Enum::eY)
            .value("eZ", PxD6Axis::Enum::eZ)
            .value("eTWIST", PxD6Axis::Enum::eTWIST)
            .value("eSWING1", PxD6Axis::Enum::eSWING1)
            .value("eSWING2", PxD6Axis::Enum::eSWING2);
    nb::enum_<PxD6Motion::Enum>(m, "PxD6Motion")
            .value("eLOCKED", PxD6Motion::Enum::eLOCKED)
            .value("eLIMITED", PxD6Motion::Enum::eLIMITED)
            .value("eFREE", PxD6Motion::Enum::eFREE);
    nb::enum_<PxD6Drive::Enum>(m, "PxD6Drive")
            .value("eX", PxD6Drive::Enum::eX)
            .value("eY", PxD6Drive::Enum::eY)
            .value("eZ", PxD6Drive::Enum::eZ)
            .value("eSWING", PxD6Drive::Enum::eSWING)
            .value("eTWIST", PxD6Drive::Enum::eTWIST)
            .value("eSLERP", PxD6Drive::Enum::eSLERP);

    nb::enum_<PxDistanceJointFlag::Enum>(m, "PxDistanceJointFlag")
            .value("eMAX_DISTANCE_ENABLED", PxDistanceJointFlag::Enum::eMAX_DISTANCE_ENABLED)
            .value("eMIN_DISTANCE_ENABLED", PxDistanceJointFlag::Enum::eMIN_DISTANCE_ENABLED)
            .value("eSPRING_ENABLED", PxDistanceJointFlag::Enum::eSPRING_ENABLED);
    bindFlags<PxDistanceJointFlag::Enum, PxU16>(m, "PxDistanceJointFlags");

    nb::enum_<PxJointActorIndex::Enum>(m, "PxJointActorIndex")
            .value("eACTOR0", PxJointActorIndex::Enum::eACTOR0)
            .value("eACTOR1", PxJointActorIndex::Enum::eACTOR1);

    nb::enum_<PxPrismaticJointFlag::Enum>(m, "PxPrismaticJointFlag")
            .value("eLIMIT_ENABLED", PxPrismaticJointFlag::Enum::eLIMIT_ENABLED);
    bindFlags<PxPrismaticJointFlag::Enum, PxU16>(m, "PxPrismaticJointFlags");

    nb::enum_<PxRevoluteJointFlag::Enum>(m, "PxRevoluteJointFlag")
            .value("eLIMIT_ENABLED", PxRevoluteJointFlag::Enum::eLIMIT_ENABLED)
            .value("eDRIVE_ENABLED", PxRevoluteJointFlag::Enum::eDRIVE_ENABLED)
            .value("eDRIVE_FREESPIN", PxRevoluteJointFlag::Enum::eDRIVE_FREESPIN);
    bindFlags<PxRevoluteJointFlag::Enum, PxU16>(m, "PxRevoluteJointFlags");

    nb::enum_<PxSphericalJointFlag::Enum>(m, "PxSphericalJointFlag")
            .value("eLIMIT_ENABLED", PxSphericalJointFlag::Enum::eLIMIT_ENABLED);
    bindFlags<PxSphericalJointFlag::Enum, PxU16>(m, "PxSphericalJointFlags");

    nb::class_<PxJoint>(m, "PxJoint")
            .def("setActors", &PxJoint::setActors)
            .def("setLocalPose", &PxJoint::setLocalPose)
            .def("getLocalPose", &PxJoint::getLocalPose)
            .def("getRelativeTransform", &PxJoint::getRelativeTransform)
            .def("getRelativeLinearVelocity", &PxJoint::getRelativeLinearVelocity)
            .def("getRelativeAngularVelocity", &PxJoint::getRelativeAngularVelocity)
            .def("setBreakForce", &PxJoint::setBreakForce)
            .def_prop_rw("constraintFlags", &PxJoint::getConstraintFlags, &PxJoint::setConstraintFlags)
            .def("setConstraintFlag", &PxJoint::setConstraintFlag)
            .def_prop_rw("invMassScale0", &PxJoint::getInvMassScale0, &PxJoint::setInvMassScale0)
            .def_prop_rw("invInertiaScale0", &PxJoint::getInvInertiaScale0, &PxJoint::setInvInertiaScale0)
            .def_prop_rw("invMassScale1", &PxJoint::getInvMassScale1, &PxJoint::setInvMassScale1)
            .def_prop_rw("invInertiaScale1", &PxJoint::getInvInertiaScale1, &PxJoint::setInvInertiaScale1)
            .def("getConstraint", &PxJoint::getConstraint)
            .def_prop_rw("name", &PxJoint::getName, &PxJoint::setName)
            .def("release", &PxJoint::release)
            .def("getScene", &PxJoint::getScene);

    m.def("PxFixedJointCreate", &PxFixedJointCreate, "physics"_a, "actor0"_a, "localFrame0"_a, "actor1"_a,
          "localFrame1"_a);
    nb::class_<PxFixedJoint, PxJoint> pxFixedJoint(m, "PxFixedJoint");

    m.def("PxPrismaticJointCreate", &PxPrismaticJointCreate, "physics"_a, "actor0"_a, "localFrame0"_a, "actor1"_a,
          "localFrame1"_a);
    nb::class_<PxPrismaticJoint, PxJoint>(m, "PxPrismaticJoint")
            .def("getPosition", &PxPrismaticJoint::getPosition)
            .def("getVelocity", &PxPrismaticJoint::getVelocity)
            .def_prop_rw("limit", &PxPrismaticJoint::getLimit, &PxPrismaticJoint::setLimit)
            .def_prop_rw("prismaticJointFlags", &PxPrismaticJoint::getPrismaticJointFlags,
                         &PxPrismaticJoint::setPrismaticJointFlags)
            .def("setPrismaticJointFlag", &PxPrismaticJoint::setPrismaticJointFlag, "flag"_a, "value"_a);

    m.def("PxDistanceJointCreate", &PxDistanceJointCreate, "physics"_a, "actor0"_a, "localFrame0"_a, "actor1"_a,
          "localFrame1"_a);
    nb::class_<PxDistanceJoint, PxJoint>(m, "PxDistanceJoint")
            .def("getDistance", &PxDistanceJoint::getDistance)
            .def_prop_rw("minDistance", &PxDistanceJoint::getMinDistance, &PxDistanceJoint::setMinDistance)
            .def_prop_rw("maxDistance", &PxDistanceJoint::getMaxDistance, &PxDistanceJoint::setMaxDistance)
            .def_prop_rw("tolerance", &PxDistanceJoint::getTolerance, &PxDistanceJoint::setTolerance)
            .def_prop_rw("stiffness", &PxDistanceJoint::getStiffness, &PxDistanceJoint::setStiffness)
            .def_prop_rw("damping", &PxDistanceJoint::getDamping, &PxDistanceJoint::setDamping)
            .def_prop_rw("setDistanceJointFlags", &PxDistanceJoint::getDistanceJointFlags,
                         &PxDistanceJoint::setDistanceJointFlags)
            .def("setDistanceJointFlag", &PxDistanceJoint::setDistanceJointFlag, "flag"_a, "value"_a);

    m.def("PxGearJointCreate", &PxGearJointCreate, "physics"_a, "actor0"_a, "localFrame0"_a, "actor1"_a,
          "localFrame1"_a);
    nb::class_<PxGearJoint, PxJoint>(m, "PxGearJoint")
            //            .def("setHinges", &PxGearJoint::setHinges)
            .def_prop_rw("gearRatio", &PxGearJoint::getGearRatio, &PxGearJoint::setGearRatio);

    m.def("PxRackAndPinionJointCreate", &PxRackAndPinionJointCreate, "physics"_a, "actor0"_a, "localFrame0"_a,
          "actor1"_a, "localFrame1"_a);
    nb::class_<PxRackAndPinionJoint, PxJoint>(m, "PxRackAndPinionJoint")
            //            .def("setJoints", &PxRackAndPinionJoint::setJoints)
            .def_prop_rw("ratio", &PxRackAndPinionJoint::getRatio, &PxRackAndPinionJoint::setRatio)
            .def("setData", &PxRackAndPinionJoint::setData, "nbRackTeeth"_a, "nbPinionTeeth"_a, "rackLength"_a);

    m.def("PxRevoluteJointCreate", &PxRevoluteJointCreate, "physics"_a, "actor0"_a, "localFrame0"_a, "actor1"_a,
          "localFrame1"_a);
    nb::class_<PxRevoluteJoint, PxJoint>(m, "PxRevoluteJoint")
            .def("getAngle", &PxRevoluteJoint::getAngle)
            .def("getVelocity", &PxRevoluteJoint::getVelocity)
            .def_prop_rw("limit", &PxRevoluteJoint::getLimit, &PxRevoluteJoint::setLimit)
            .def_prop_rw("driveVelocity", &PxRevoluteJoint::getDriveVelocity, &PxRevoluteJoint::setDriveVelocity)
            .def_prop_rw("driveForceLimit", &PxRevoluteJoint::getDriveForceLimit, &PxRevoluteJoint::setDriveForceLimit)
            .def_prop_rw("driveGearRatio", &PxRevoluteJoint::getDriveGearRatio, &PxRevoluteJoint::setDriveGearRatio)
            .def_prop_rw("revoluteJointFlags", &PxRevoluteJoint::getRevoluteJointFlags,
                         &PxRevoluteJoint::setRevoluteJointFlags)
            .def("setRevoluteJointFlag", &PxRevoluteJoint::setRevoluteJointFlag, "flag"_a, "value"_a);

    m.def("PxSphericalJointCreate", &PxSphericalJointCreate, "physics"_a, "actor0"_a, "localFrame0"_a, "actor1"_a,
          "localFrame1"_a);
    nb::class_<PxSphericalJoint, PxJoint>(m, "PxSphericalJoint")
            .def_prop_rw("limitCone", &PxSphericalJoint::getLimitCone, &PxSphericalJoint::setLimitCone)
            .def("getSwingYAngle", &PxSphericalJoint::getSwingYAngle)
            .def("getSwingZAngle", &PxSphericalJoint::getSwingZAngle)
            .def_prop_rw("sphericalJointFlags", &PxSphericalJoint::getSphericalJointFlags,
                         &PxSphericalJoint::setSphericalJointFlags)
            .def("setSphericalJointFlag", &PxSphericalJoint::setSphericalJointFlag, "flag"_a, "value"_a);

    m.def("PxD6JointCreate", &PxD6JointCreate, "physics"_a, "actor0"_a, "localFrame0"_a, "actor1"_a, "localFrame1"_a);
    nb::class_<PxD6Joint, PxJoint>(m, "PxD6Joint")
            .def("setMotion", &PxD6Joint::setMotion, "axis"_a, "type"_a)
            .def("getMotion", &PxD6Joint::getMotion, "axis"_a)
            .def("getTwistAngle", &PxD6Joint::getTwistAngle)
            .def("getSwingYAngle", &PxD6Joint::getSwingYAngle)
            .def("getSwingZAngle", &PxD6Joint::getSwingZAngle)
            .def_prop_rw("distanceLimit", &PxD6Joint::getDistanceLimit, &PxD6Joint::setDistanceLimit)
            .def("setLinearLimit",
                 nb::overload_cast<PxD6Axis::Enum, const PxJointLinearLimitPair&>(&PxD6Joint::setLinearLimit))
            .def("getLinearLimit", nb::overload_cast<PxD6Axis::Enum>(&PxD6Joint::getLinearLimit, nb::const_))
            .def_prop_rw("twistLimit", &PxD6Joint::getTwistLimit, &PxD6Joint::setTwistLimit)
            .def_prop_rw("swingLimit", &PxD6Joint::getSwingLimit, &PxD6Joint::setSwingLimit)
            .def_prop_rw("pyramidSwingLimit", &PxD6Joint::getPyramidSwingLimit, &PxD6Joint::setPyramidSwingLimit)
            .def("setDrive", &PxD6Joint::setDrive, "index"_a, "drive"_a)
            .def("getDrive", &PxD6Joint::getDrive, "index"_a)
            .def("setDrivePosition", &PxD6Joint::setDrivePosition, "pose"_a, "autowake"_a = true)
            .def("getDrivePosition", &PxD6Joint::getDrivePosition)
            .def("setDriveVelocity", &PxD6Joint::setDriveVelocity, "linear"_a, "angular"_a, "autowake"_a = true)
            .def("getDriveVelocity", [](PxD6Joint* joint) {
                std::tuple<PxVec3, PxVec3> result;
                joint->getDriveVelocity(std::get<0>(result), std::get<1>(result));
                return result;
            });
    nb::class_<PxJointLimitParameters>(m, "PxJointLimitParameters")
            .def(nb::init<>())
            .def("isValid", &PxJointLimitParameters::isValid)
            .def("isSoft", &PxJointLimitParameters::isSoft)
            .def_rw("restitution", &PxJointLimitParameters::restitution)
            .def_rw("bounceThreshold", &PxJointLimitParameters::bounceThreshold)
            .def_rw("stiffness", &PxJointLimitParameters::stiffness)
            .def_rw("damping", &PxJointLimitParameters::damping);
    nb::class_<PxJointLinearLimit, PxJointLimitParameters>(m, "PxJointLinearLimit")
            .def(nb::init<PxReal>())
            .def(nb::init<PxReal, PxSpring>())
            .def("isValid", &PxJointLinearLimit::isValid)
            .def_rw("value", &PxJointLinearLimit::value);
    nb::class_<PxJointLinearLimitPair, PxJointLimitParameters>(m, "PxJointLinearLimitPair")
            .def(nb::init<const PxTolerancesScale&, PxReal, PxReal>())
            .def(nb::init<PxReal, PxReal, const PxSpring&>())
            .def("isValid", &PxJointLinearLimitPair::isValid)
            .def_rw("upper", &PxJointLinearLimitPair::upper)
            .def_rw("lower", &PxJointLinearLimitPair::lower);
    nb::class_<PxJointAngularLimitPair, PxJointLimitParameters>(m, "PxJointAngularLimitPair")
            .def(nb::init<PxReal, PxReal>())
            .def(nb::init<PxReal, PxReal, PxSpring>())
            .def("isValid", &PxJointAngularLimitPair::isValid)
            .def_rw("upper", &PxJointAngularLimitPair::upper)
            .def_rw("lower", &PxJointAngularLimitPair::lower);
    nb::class_<PxJointLimitCone, PxJointLimitParameters>(m, "PxJointLimitCone")
            .def(nb::init<PxReal, PxReal>())
            .def(nb::init<PxReal, PxReal, PxSpring>())
            .def("isValid", &PxJointLimitCone::isValid)
            .def_rw("upper", &PxJointLimitCone::yAngle)
            .def_rw("lower", &PxJointLimitCone::zAngle);
    nb::class_<PxJointLimitPyramid, PxJointLimitParameters>(m, "PxJointLimitPyramid")
            .def(nb::init<PxReal, PxReal, PxReal, PxReal>())
            .def(nb::init<PxReal, PxReal, PxReal, PxReal, PxSpring>())
            .def("isValid", &PxJointLimitPyramid::isValid)
            .def_rw("upper", &PxJointLimitPyramid::yAngleMin)
            .def_rw("lower", &PxJointLimitPyramid::yAngleMax)
            .def_rw("lower", &PxJointLimitPyramid::zAngleMin)
            .def_rw("lower", &PxJointLimitPyramid::zAngleMax);

    nb::class_<PxSpring>(m, "PxSpring")
            .def(nb::init<PxReal, PxReal>())
            .def_rw("upper", &PxSpring::stiffness)
            .def_rw("lower", &PxSpring::damping);
    nb::class_<PxD6JointDrive, PxSpring>(m, "PxD6JointDrive")
            .def(nb::init<>())
            .def(nb::init<PxReal, PxReal, PxReal, bool>())
            .def_rw("forceLimit", &PxD6JointDrive::forceLimit)
            .def_rw("lower", &PxD6JointDrive::damping)
            .def("isValid", &PxD6JointDrive::isValid);
}