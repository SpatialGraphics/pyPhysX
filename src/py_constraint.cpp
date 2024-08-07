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
            .def("getScene", &PxConstraint::getScene, nb::rv_policy::reference)
            .def("setActors", &PxConstraint::setActors, "actor0"_a, "actor1"_a)
            .def("markDirty", &PxConstraint::markDirty)
            .def("setFlag", &PxConstraint::setFlag, "flag"_a, "value"_a)
            .def_prop_rw("flags", &PxConstraint::getFlags, &PxConstraint::setFlags)
            .def("getForce",
                 [](PxConstraint* constraint) {
                     std::tuple<PxVec3, PxVec3> result;
                     constraint->getForce(std::get<0>(result), std::get<1>(result));
                     return result;
                 })
            .def("isValid", &PxConstraint::isValid)
            .def("setBreakForce", &PxConstraint::setBreakForce, "linear"_a, "angular"_a)
            .def("getBreakForce",
                 [](PxConstraint* constraint) {
                     std::tuple<PxReal, PxReal> result;
                     constraint->getBreakForce(std::get<0>(result), std::get<1>(result));
                     return result;
                 })
            .def_prop_rw("minResponseThreshold", &PxConstraint::getMinResponseThreshold,
                         &PxConstraint::setMinResponseThreshold);
}