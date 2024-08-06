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

void bindTetrahedronMesh(nb::module_& m) {
    nb::class_<PxTetrahedronMesh>(m, "PxTetrahedronMesh")
            .def("getNbVertices", &PxTetrahedronMesh::getNbVertices)
            .def("getVertices", &PxTetrahedronMesh::getVertices)
            .def("getNbTetrahedrons", &PxTetrahedronMesh::getNbTetrahedrons)
            .def("getTetrahedronMeshFlags",
                 [](PxTetrahedronMesh* mesh) {
                     return mesh->getTetrahedronMeshFlags().operator uint32_t();
                 })
            .def("getLocalBounds", &PxTetrahedronMesh::getLocalBounds)
            .def("release", &PxTetrahedronMesh::release);
}