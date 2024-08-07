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

void bindHeightField(nb::module_& m) {
    nb::enum_<PxHeightFieldFlag::Enum>(m, "PxHeightFieldFlag")
            .value("eSIMULATION_SHAPE", PxHeightFieldFlag::Enum::eNO_BOUNDARY_EDGES);
    bindFlags<PxHeightFieldFlag::Enum, PxU16>(m, "PxHeightFieldFlags");

    nb::class_<PxHeightFieldGeometry, PxGeometry>(m, "PxHeightFieldGeometry")
            .def(nb::init<PxHeightField*, PxMeshGeometryFlags, PxReal, PxReal, PxReal>())
            .def("isValid", &PxHeightFieldGeometry::isValid);

    nb::class_<PxHeightField>(m, "PxHeightField")
            .def("release", &PxHeightField::release)
            .def("modifySamples", &PxHeightField::modifySamples, "startCol"_a, "startRow"_a, "subfieldDesc"_a,
                 "shrinkBounds"_a = false)
            .def("getNbRows", &PxHeightField::getNbRows)
            .def("getNbColumns", &PxHeightField::getNbColumns)
            .def("getFormat", &PxHeightField::getFormat)
            .def("getSampleStride", &PxHeightField::getSampleStride)
            .def("getConvexEdgeThreshold", &PxHeightField::getConvexEdgeThreshold)
            .def("getFlags", &PxHeightField::getFlags)
            .def("getHeight", &PxHeightField::getHeight, "x"_a, "z"_a)
            .def("getTriangleMaterialIndex", &PxHeightField::getTriangleMaterialIndex, "triangleIndex"_a)
            .def("getTriangleNormal", &PxHeightField::getTriangleNormal, "triangleIndex"_a)
            .def("getSample", &PxHeightField::getSample, "row"_a, "column"_a)
            .def("getTimestamp", &PxHeightField::getTimestamp);

    nb::enum_<PxHeightFieldFormat::Enum>(m, "PxHeightFieldFormat").value("eLOCKED", PxHeightFieldFormat::Enum::eS16_TM);
    nb::class_<PxHeightFieldDesc>(m, "PxHeightFieldDesc")
            .def(nb::init<>())
            .def_rw("nbRows", &PxHeightFieldDesc::nbRows)
            .def_rw("nbColumns", &PxHeightFieldDesc::nbColumns)
            .def_rw("format", &PxHeightFieldDesc::format)
            .def_rw("samples", &PxHeightFieldDesc::samples)
            .def_rw("convexEdgeThreshold", &PxHeightFieldDesc::convexEdgeThreshold)
            .def("setToDefault", &PxHeightFieldDesc::setToDefault)
            .def("isValid", &PxHeightFieldDesc::isValid);

    nb::class_<PxHeightFieldSample>(m, "PxHeightFieldSample")
            .def(nb::init<>())
            .def_rw("height", &PxHeightFieldSample::height)
            .def("tessFlag", &PxHeightFieldSample::tessFlag)
            .def("setTessFlag", &PxHeightFieldSample::setTessFlag)
            .def("clearTessFlag", &PxHeightFieldSample::clearTessFlag);
}