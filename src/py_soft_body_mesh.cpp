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

void bindSoftBodyMesh(nb::module_& m) {
    nb::enum_<PxSoftBodyDataFlag::Enum>(m, "PxSoftBodyDataFlag")
            .value("eNONE", PxSoftBodyDataFlag::Enum::eNONE)
            .value("ePOSITION_INVMASS", PxSoftBodyDataFlag::Enum::ePOSITION_INVMASS)
            .value("eSIM_POSITION_INVMASS", PxSoftBodyDataFlag::Enum::eSIM_POSITION_INVMASS)
            .value("eSIM_VELOCITY", PxSoftBodyDataFlag::Enum::eSIM_VELOCITY)
            .value("eREST_POSITION_INVMASS", PxSoftBodyDataFlag::Enum::eREST_POSITION_INVMASS)
            .value("eALL", PxSoftBodyDataFlag::Enum::eALL);

    nb::enum_<PxSoftBodyFlag::Enum>(m, "PxSoftBodyFlag")
            .value("eDISABLE_SELF_COLLISION", PxSoftBodyFlag::Enum::eDISABLE_SELF_COLLISION)
            .value("eCOMPUTE_STRESS_TENSOR", PxSoftBodyFlag::Enum::eCOMPUTE_STRESS_TENSOR)
            .value("eENABLE_CCD", PxSoftBodyFlag::Enum::eENABLE_CCD)
            .value("eDISPLAY_SIM_MESH", PxSoftBodyFlag::Enum::eDISPLAY_SIM_MESH)
            .value("eKINEMATIC", PxSoftBodyFlag::Enum::eKINEMATIC)
            .value("ePARTIALLY_KINEMATIC", PxSoftBodyFlag::Enum::ePARTIALLY_KINEMATIC);

    nb::class_<PxFEMParameters>(m, "PxFEMParameters")
            .def(nb::init<>())
            .def_rw("velocityDamping", &PxFEMParameters::velocityDamping)
            .def_rw("settlingThreshold", &PxFEMParameters::settlingThreshold)
            .def_rw("sleepThreshold", &PxFEMParameters::sleepThreshold)
            .def_rw("sleepDamping", &PxFEMParameters::sleepDamping)
            .def_rw("selfCollisionFilterDistance", &PxFEMParameters::selfCollisionFilterDistance)
            .def_rw("selfCollisionStressTolerance", &PxFEMParameters::selfCollisionStressTolerance);

    nb::class_<PxSoftBodyAuxData>(m, "PxSoftBodyAuxData").def("release", &PxSoftBodyAuxData::release);

    nb::class_<PxConeLimitedConstraint>(m, "PxConeLimitedConstraint")
            .def(nb::init<>())
            .def_rw("mAxis", &PxConeLimitedConstraint::mAxis)
            .def_rw("mAngle", &PxConeLimitedConstraint::mAngle)
            .def_rw("mLowLimit", &PxConeLimitedConstraint::mLowLimit)
            .def_rw("mHighLimit", &PxConeLimitedConstraint::mHighLimit)
            .def("isValid", &PxConeLimitedConstraint::isValid)
            .def("setToDefault", &PxConeLimitedConstraint::setToDefault);

    nb::class_<PxSoftBodyMesh>(m, "PxSoftBodyMesh")
            .def("getCollisionMesh", nb::overload_cast<>(&PxSoftBodyMesh::getCollisionMesh, nb::const_))
            .def("getCollisionMesh", nb::overload_cast<>(&PxSoftBodyMesh::getSimulationMesh, nb::const_));
}