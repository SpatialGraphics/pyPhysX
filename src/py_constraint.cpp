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

void bindConstraint(nb::module_& m) {
    nb::class_<PxConstraint>(m, "PxConstraint")
            .def("write", &PxConstraint::release)
            .def("getScene", &PxConstraint::getScene)
            .def("setActors", &PxConstraint::setActors)
            .def("markDirty", &PxConstraint::markDirty)
            .def("getForce", &PxConstraint::getForce)
            .def("isValid", &PxConstraint::isValid)
            .def("setBreakForce", &PxConstraint::setBreakForce)
            .def("getBreakForce", &PxConstraint::getBreakForce)
            .def("setMinResponseThreshold", &PxConstraint::setMinResponseThreshold)
            .def("getMinResponseThreshold", &PxConstraint::getMinResponseThreshold)
            .def("getExternalReference", &PxConstraint::getExternalReference);
}