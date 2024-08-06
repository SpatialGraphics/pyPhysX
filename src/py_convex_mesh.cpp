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

void bindConvexMesh(nb::module_& m) {
    nb::class_<PxConvexMesh>(m, "PxConvexMesh")
            .def("getNbVertices", &PxConvexMesh::getNbVertices)
            .def("getVertices", &PxConvexMesh::getVertices)
            .def("getIndexBuffer", &PxConvexMesh::getIndexBuffer)
            .def("getNbPolygons", &PxConvexMesh::getNbPolygons)
            .def("getPolygonData", &PxConvexMesh::getPolygonData)
            .def("release", &PxConvexMesh::release)
            .def("getMassInformation", &PxConvexMesh::getMassInformation)
            .def("getLocalBounds", &PxConvexMesh::getLocalBounds)
            .def("getSDF", &PxConvexMesh::getSDF)
            .def("isGpuCompatible", &PxConvexMesh::isGpuCompatible);
}