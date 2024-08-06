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
    nb::class_<PxSoftBodyMesh>(m, "PxSoftBodyMesh")
            .def("getCollisionMesh", nb::overload_cast<>(&PxSoftBodyMesh::getCollisionMesh, nb::const_))
            .def("getCollisionMesh", nb::overload_cast<>(&PxSoftBodyMesh::getSimulationMesh, nb::const_));
}