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

void bindTetrahedronMesh(nb::module_& m) {
    nb::enum_<PxTetrahedronMeshFlag::Enum>(m, "PxTetrahedronMeshFlag")
            .value("e16_BIT_INDICES", PxTetrahedronMeshFlag::Enum::e16_BIT_INDICES);
    bindFlags<PxTetrahedronMeshFlag::Enum, PxU8>(m, "PxTetrahedronMeshFlags");

    nb::class_<PxTetrahedronMesh>(m, "PxTetrahedronMesh")
            .def("getNbVertices", &PxTetrahedronMesh::getNbVertices)
            .def("getVertices", &PxTetrahedronMesh::getVertices)
            .def("getNbTetrahedrons", &PxTetrahedronMesh::getNbTetrahedrons)
            .def("getTetrahedronMeshFlags", &PxTetrahedronMesh::getTetrahedronMeshFlags)
            .def("getLocalBounds", &PxTetrahedronMesh::getLocalBounds)
            .def("release", &PxTetrahedronMesh::release);
}