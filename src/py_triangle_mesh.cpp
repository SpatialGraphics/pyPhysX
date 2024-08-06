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

void bindTriangleMesh(nb::module_& m) {
    nb::class_<PxTriangleMesh>(m, "PxTriangleMesh")
            .def("getNbVertices", &PxTriangleMesh::getNbVertices)
            .def("getVertices", &PxTriangleMesh::getVertices)
            .def("getVerticesForModification", &PxTriangleMesh::getVerticesForModification)
            .def("refitBVH", &PxTriangleMesh::refitBVH)
            .def("getNbTriangles", &PxTriangleMesh::getNbTriangles)
            .def("getTriangleMeshFlags",
                 [](PxTriangleMesh* mesh) {
                     return mesh->getTriangleMeshFlags().operator uint32_t();
                 })
            .def("release", &PxTriangleMesh::release)
            .def("getTriangleMaterialIndex", &PxTriangleMesh::getTriangleMaterialIndex)
            .def("getLocalBounds", &PxTriangleMesh::getLocalBounds)
            .def("getSDFDimensions", &PxTriangleMesh::getSDFDimensions)
            .def("setPreferSDFProjection", &PxTriangleMesh::setPreferSDFProjection)
            .def("getPreferSDFProjection", &PxTriangleMesh::getPreferSDFProjection)
            .def("getMassInformation", &PxTriangleMesh::getMassInformation);
}