//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/tuple.h>

#include "py_utils.h"

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

void bindConvexMesh(nb::module_& m) {
    nb::enum_<PxConvexMeshGeometryFlag::Enum>(m, "PxConvexMeshGeometryFlag")
            .value("eTIGHT_BOUNDS", PxConvexMeshGeometryFlag::Enum::eTIGHT_BOUNDS);
    bindFlags<PxConvexMeshGeometryFlag::Enum, PxU8>(m, "PxConvexMeshGeometryFlags");

    nb::class_<PxConvexMesh>(m, "PxConvexMesh")
            .def("getNbVertices", &PxConvexMesh::getNbVertices)
            .def("getVertices", &PxConvexMesh::getVertices)
            .def("getIndexBuffer", &PxConvexMesh::getIndexBuffer)
            .def("getNbPolygons", &PxConvexMesh::getNbPolygons)
            .def("getPolygonData", &PxConvexMesh::getPolygonData, "index"_a, "data"_a)
            .def("release", &PxConvexMesh::release)
            .def("getMassInformation",
                 [](PxConvexMesh* mesh) {
                     std::tuple<PxReal, PxMat33, PxVec3> result;
                     mesh->getMassInformation(std::get<0>(result), std::get<1>(result), std::get<2>(result));
                     return result;
                 })
            .def("getLocalBounds", &PxConvexMesh::getLocalBounds)
            .def("getSDF", &PxConvexMesh::getSDF)
            .def("isGpuCompatible", &PxConvexMesh::isGpuCompatible);

    nb::class_<PxHullPolygon>(m, "PxHullPolygon")
            .def(nb::init<>())
            .def_rw("mIndexBase", &PxHullPolygon::mIndexBase)
            .def_rw("mNbVerts", &PxHullPolygon::mNbVerts)
            .def_prop_ro("mPlane", [](PxHullPolygon* polygon) {
                return std::vector<PxReal>(polygon->mPlane, polygon->mPlane + 4);
            });

    nb::class_<PxConvexMeshGeometry, PxGeometry>(m, "PxConvexMeshGeometry")
            .def(nb::init<PxConvexMesh*, const PxMeshScale&, PxConvexMeshGeometryFlags>())
            .def("isValid", &PxConvexMeshGeometry::isValid);
    nb::class_<PxMeshScale>(m, "PxMeshScale")
            .def(nb::init<>())
            .def(nb::init<PxReal>())
            .def(nb::init<PxVec3>())
            .def(nb::init<PxVec3, PxQuat>())
            .def("isIdentity", &PxMeshScale::isIdentity)
            .def("getInverse", &PxMeshScale::getInverse)
            .def("toMat33", &PxMeshScale::toMat33)
            .def("hasNegativeDeterminant", &PxMeshScale::hasNegativeDeterminant)
            .def("transform", &PxMeshScale::transform, "v"_a)
            .def("isValidForTriangleMesh", &PxMeshScale::isValidForTriangleMesh)
            .def("isValidForConvexMesh", &PxMeshScale::isValidForConvexMesh);
}