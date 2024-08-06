//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>

#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

void bindAggregate(nb::module_& m) {
    nb::class_<PxAggregate>(m, "PxAggregate")
            .def("release", &PxAggregate::release)
            .def("addActor", &PxAggregate::addActor)
            .def("removeActor", &PxAggregate::removeActor)
            .def("addArticulation", &PxAggregate::addArticulation)
            .def("removeArticulation", &PxAggregate::removeArticulation)
            .def("getNbActors", &PxAggregate::getNbActors)
            .def("getMaxNbActors", &PxAggregate::getMaxNbActors)
            .def("getScene", &PxAggregate::getScene, nb::rv_policy::reference)
            .def("getSelfCollision", &PxAggregate::getSelfCollision);
}