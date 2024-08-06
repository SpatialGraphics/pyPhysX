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
            .def(
                    "addActor",
                    [](PxAggregate* aggregate, PxActor& actor) {
                        return aggregate->addActor(actor);
                    },
                    "actor"_a)
            .def("removeActor", &PxAggregate::removeActor, "actor"_a)
            .def("addArticulation", &PxAggregate::addArticulation, "articulation"_a)
            .def("removeArticulation", &PxAggregate::removeArticulation, "articulation"_a)
            .def("getNbActors", &PxAggregate::getNbActors)
            .def("getMaxNbActors", &PxAggregate::getMaxNbActors)
            .def("getMaxNbShapes", &PxAggregate::getMaxNbShapes)
            .def("getScene", &PxAggregate::getScene, nb::rv_policy::reference)
            .def("getSelfCollision", &PxAggregate::getSelfCollision);
}