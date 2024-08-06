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

void bindHeightField(nb::module_& m) {
    nb::class_<PxHeightField>(m, "PxHeightField")
            .def("release", &PxHeightField::release)
            .def("modifySamples", &PxHeightField::modifySamples)
            .def("getNbRows", &PxHeightField::getNbRows)
            .def("getNbColumns", &PxHeightField::getNbColumns)
            .def("getFormat", &PxHeightField::getFormat)
            .def("getSampleStride", &PxHeightField::getSampleStride)
            .def("getConvexEdgeThreshold", &PxHeightField::getConvexEdgeThreshold)
            .def("getFlags", &PxHeightField::getFlags)
            .def("getHeight", &PxHeightField::getHeight)
            .def("getTriangleMaterialIndex", &PxHeightField::getTriangleMaterialIndex)
            .def("getTriangleNormal", &PxHeightField::getTriangleNormal)
            .def("getSample", &PxHeightField::getSample)
            .def("getTimestamp", &PxHeightField::getTimestamp);
}