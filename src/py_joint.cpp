//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>

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
            .def("setConstraintFlags", &PxJoint::setConstraintFlags)
            .def("setConstraintFlag", &PxJoint::setConstraintFlag)
            .def("getConstraintFlags", &PxJoint::getConstraintFlags)
            .def("setInvMassScale0", &PxJoint::setInvMassScale0)
            .def("getInvMassScale0", &PxJoint::getInvMassScale0)
            .def("setInvInertiaScale0", &PxJoint::setInvInertiaScale0)
            .def("getInvInertiaScale0", &PxJoint::getInvInertiaScale0)
            .def("setInvMassScale1", &PxJoint::setInvMassScale1)
            .def("getInvMassScale1", &PxJoint::getInvMassScale1)
            .def("setInvInertiaScale1", &PxJoint::setInvInertiaScale1)
            .def("getInvInertiaScale1", &PxJoint::getInvInertiaScale1)
            .def("getConstraint", &PxJoint::getConstraint)
            .def("setName", &PxJoint::setName)
            .def("getName", &PxJoint::getName)
            .def("release", &PxJoint::release)
            .def("getScene", &PxJoint::getScene);

    nb::class_<PxFixedJoint, PxJoint> pxFixedJoint(m, "PxFixedJoint");

    nb::class_<PxPrismaticJoint, PxJoint>(m, "PxPrismaticJoint")
            .def("getPosition", &PxPrismaticJoint::getPosition)
            .def("getVelocity", &PxPrismaticJoint::getVelocity)
            .def("setLimit", &PxPrismaticJoint::setLimit)
            .def("getLimit", &PxPrismaticJoint::getLimit)
            .def("setPrismaticJointFlags", &PxPrismaticJoint::setPrismaticJointFlags)
            .def("setPrismaticJointFlag", &PxPrismaticJoint::setPrismaticJointFlag)
            .def("getPrismaticJointFlags", &PxPrismaticJoint::getPrismaticJointFlags);

    nb::class_<PxDistanceJoint, PxJoint>(m, "PxDistanceJoint")
            .def("getDistance", &PxDistanceJoint::getDistance)
            .def("setMinDistance", &PxDistanceJoint::setMinDistance)
            .def("getMinDistance", &PxDistanceJoint::getMinDistance)
            .def("setMaxDistance", &PxDistanceJoint::setMaxDistance)
            .def("getMaxDistance", &PxDistanceJoint::getMaxDistance)
            .def("setTolerance", &PxDistanceJoint::setTolerance)
            .def("getTolerance", &PxDistanceJoint::getTolerance)
            .def("setStiffness", &PxDistanceJoint::setStiffness)
            .def("getStiffness", &PxDistanceJoint::getStiffness)
            .def("setDamping", &PxDistanceJoint::setDamping)
            .def("getDamping", &PxDistanceJoint::getDamping)
            .def("setDistanceJointFlags", &PxDistanceJoint::setDistanceJointFlags)
            .def("setDistanceJointFlag", &PxDistanceJoint::setDistanceJointFlag)
            .def("getDistanceJointFlags", &PxDistanceJoint::getDistanceJointFlags);

    nb::class_<PxGearJoint, PxJoint>(m, "PxGearJoint")
            //            .def("setHinges", &PxGearJoint::setHinges)
            .def("setGearRatio", &PxGearJoint::setGearRatio)
            .def("getGearRatio", &PxGearJoint::getGearRatio);

    nb::class_<PxRackAndPinionJoint, PxJoint>(m, "PxRackAndPinionJoint")
            //            .def("setJoints", &PxRackAndPinionJoint::setJoints)
            .def("setRatio", &PxRackAndPinionJoint::setRatio)
            .def("getRatio", &PxRackAndPinionJoint::getRatio)
            .def("setData", &PxRackAndPinionJoint::setData);

    nb::class_<PxRevoluteJoint, PxJoint>(m, "PxRevoluteJoint")
            .def("getAngle", &PxRevoluteJoint::getAngle)
            .def("getVelocity", &PxRevoluteJoint::getVelocity)
            .def("setLimit", &PxRevoluteJoint::setLimit)
            .def("getLimit", &PxRevoluteJoint::getLimit)
            .def("setDriveVelocity", &PxRevoluteJoint::setDriveVelocity)
            .def("getDriveVelocity", &PxRevoluteJoint::getDriveVelocity)
            .def("setDriveForceLimit", &PxRevoluteJoint::setDriveForceLimit)
            .def("getDriveForceLimit", &PxRevoluteJoint::getDriveForceLimit)
            .def("setDriveGearRatio", &PxRevoluteJoint::setDriveGearRatio)
            .def("getDriveGearRatio", &PxRevoluteJoint::getDriveGearRatio)
            .def("setRevoluteJointFlags", &PxRevoluteJoint::setRevoluteJointFlags)
            .def("setRevoluteJointFlag", &PxRevoluteJoint::setRevoluteJointFlag)
            .def("getRevoluteJointFlags", &PxRevoluteJoint::getRevoluteJointFlags);

    nb::class_<PxSphericalJoint, PxJoint>(m, "PxSphericalJoint")
            .def("getLimitCone", &PxSphericalJoint::getLimitCone)
            .def("setLimitCone", &PxSphericalJoint::setLimitCone)
            .def("getSwingYAngle", &PxSphericalJoint::getSwingYAngle)
            .def("getSwingZAngle", &PxSphericalJoint::getSwingZAngle)
            .def("setSphericalJointFlags", &PxSphericalJoint::setSphericalJointFlags)
            .def("setSphericalJointFlag", &PxSphericalJoint::setSphericalJointFlag)
            .def("getSphericalJointFlags", &PxSphericalJoint::getSphericalJointFlags);

    nb::class_<PxD6Joint, PxJoint>(m, "PxD6Joint")
            .def("setMotion", &PxD6Joint::setMotion)
            .def("getMotion", &PxD6Joint::getMotion)
            .def("getTwistAngle", &PxD6Joint::getTwistAngle)
            .def("getSwingYAngle", &PxD6Joint::getSwingYAngle)
            .def("getSwingZAngle", &PxD6Joint::getSwingZAngle)
            .def("setDistanceLimit", &PxD6Joint::setDistanceLimit)
            .def("getDistanceLimit", &PxD6Joint::getDistanceLimit)
            .def("setLinearLimit",
                 nb::overload_cast<PxD6Axis::Enum, const PxJointLinearLimitPair&>(&PxD6Joint::setLinearLimit))
            .def("getLinearLimit", nb::overload_cast<PxD6Axis::Enum>(&PxD6Joint::getLinearLimit, nb::const_))
            .def("setTwistLimit", &PxD6Joint::setTwistLimit)
            .def("getTwistLimit", &PxD6Joint::getTwistLimit)
            .def("setSwingLimit", &PxD6Joint::setSwingLimit)
            .def("getSwingLimit", &PxD6Joint::getSwingLimit)
            .def("setPyramidSwingLimit", &PxD6Joint::setPyramidSwingLimit)
            .def("getPyramidSwingLimit", &PxD6Joint::getPyramidSwingLimit)
            .def("setDrive", &PxD6Joint::setDrive)
            .def("getDrive", &PxD6Joint::getDrive)
            .def("setDrivePosition", &PxD6Joint::setDrivePosition)
            .def("getDrivePosition", &PxD6Joint::getDrivePosition)
            .def("setDriveVelocity", &PxD6Joint::setDriveVelocity)
            .def("getDriveVelocity", &PxD6Joint::getDriveVelocity);
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