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

void bindTriangleMesh(nb::module_& m) {
    nb::enum_<PxTriangleMeshFlag::Enum>(m, "PxTriangleMeshFlag")
            .value("e16_BIT_INDICES", PxTriangleMeshFlag::Enum::e16_BIT_INDICES)
            .value("eADJACENCY_INFO", PxTriangleMeshFlag::Enum::eADJACENCY_INFO)
            .value("ePREFER_NO_SDF_PROJ", PxTriangleMeshFlag::Enum::ePREFER_NO_SDF_PROJ);
    bindFlags<PxTriangleMeshFlag::Enum, PxU8>(m, "PxTriangleMeshFlags");

    nb::class_<PxTriangleMesh>(m, "PxTriangleMesh")
            .def("getNbVertices", &PxTriangleMesh::getNbVertices)
            .def("getVertices", &PxTriangleMesh::getVertices)
            .def("getVerticesForModification", &PxTriangleMesh::getVerticesForModification)
            .def("refitBVH", &PxTriangleMesh::refitBVH)
            .def("getNbTriangles", &PxTriangleMesh::getNbTriangles)
            .def("getTriangleMeshFlags", &PxTriangleMesh::getTriangleMeshFlags)
            .def("release", &PxTriangleMesh::release)
            .def("getTriangleMaterialIndex", &PxTriangleMesh::getTriangleMaterialIndex)
            .def("getLocalBounds", &PxTriangleMesh::getLocalBounds)
            .def("getSDFDimensions", &PxTriangleMesh::getSDFDimensions)
            .def_prop_rw("preferSDFProjection", &PxTriangleMesh::getPreferSDFProjection,
                         &PxTriangleMesh::setPreferSDFProjection)
            .def("getMassInformation", &PxTriangleMesh::getMassInformation);
}