//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/array.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

void bindJoint(nb::module_& m) {
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
            .def("setDistanceJointFlag", &PxDistanceJoint::setDistanceJointFlag);

    nb::class_<PxGearJoint, PxJoint>(m, "PxGearJoint")
            .def("setHinges", &PxGearJoint::setHinges)
            .def("setGearRatio", &PxGearJoint::setGearRatio)
            .def("getGearRatio", &PxGearJoint::getGearRatio);

    nb::class_<PxRackAndPinionJoint, PxJoint>(m, "PxRackAndPinionJoint")
            .def("setJoints", &PxRackAndPinionJoint::setJoints)
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
}