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

void bindConstraint(nb::module_& m) {
    nb::enum_<PxConstraintFlag::Enum>(m, "PxConstraintFlag")
            .value("eBROKEN", PxConstraintFlag::Enum::eBROKEN)
            .value("eCOLLISION_ENABLED", PxConstraintFlag::Enum::eCOLLISION_ENABLED)
            .value("eVISUALIZATION", PxConstraintFlag::Enum::eVISUALIZATION)
            .value("eDRIVE_LIMITS_ARE_FORCES", PxConstraintFlag::Enum::eDRIVE_LIMITS_ARE_FORCES)
            .value("eIMPROVED_SLERP", PxConstraintFlag::Enum::eIMPROVED_SLERP)
            .value("eDISABLE_PREPROCESSING", PxConstraintFlag::Enum::eDISABLE_PREPROCESSING)
            .value("eENABLE_EXTENDED_LIMITS", PxConstraintFlag::Enum::eENABLE_EXTENDED_LIMITS)
            .value("eGPU_COMPATIBLE", PxConstraintFlag::Enum::eGPU_COMPATIBLE)
            .value("eALWAYS_UPDATE", PxConstraintFlag::Enum::eALWAYS_UPDATE)
            .value("eDISABLE_CONSTRAINT", PxConstraintFlag::Enum::eDISABLE_CONSTRAINT);
    bindFlags<PxConstraintFlag::Enum, PxU16>(m, "PxConstraintFlags");

    nb::class_<PxConstraint>(m, "PxConstraint")
            .def("write", &PxConstraint::release)
            .def("getScene", &PxConstraint::getScene)
            .def("setActors", &PxConstraint::setActors)
            .def("markDirty", &PxConstraint::markDirty)
            .def("setFlag", &PxConstraint::setFlag)
            .def("setFlags", &PxConstraint::setFlags)
            .def("getFlags", &PxConstraint::getFlags)
            .def("getForce", &PxConstraint::getForce)
            .def("isValid", &PxConstraint::isValid)
            .def("setBreakForce", &PxConstraint::setBreakForce)
            .def("getBreakForce", &PxConstraint::getBreakForce)
            .def("setMinResponseThreshold", &PxConstraint::setMinResponseThreshold)
            .def("getMinResponseThreshold", &PxConstraint::getMinResponseThreshold);
}