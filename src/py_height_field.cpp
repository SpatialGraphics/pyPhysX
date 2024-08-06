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
    nb::class_<PxHeightFieldGeometry, PxGeometry>(m, "PxHeightFieldGeometry")
            .def("__init__",
                 [](PxHeightField* hf, int flags, PxReal heightScale_, PxReal rowScale_, PxReal columnScale_) {
                     return new PxHeightFieldGeometry(hf, PxMeshGeometryFlags(flags), heightScale_, rowScale_,
                                                      columnScale_);
                 })
            .def("isValid", &PxHeightFieldGeometry::isValid);

    nb::class_<PxHeightField>(m, "PxHeightField")
            .def("release", &PxHeightField::release)
            .def("modifySamples", &PxHeightField::modifySamples)
            .def("getNbRows", &PxHeightField::getNbRows)
            .def("getNbColumns", &PxHeightField::getNbColumns)
            .def("getFormat", &PxHeightField::getFormat)
            .def("getSampleStride", &PxHeightField::getSampleStride)
            .def("getConvexEdgeThreshold", &PxHeightField::getConvexEdgeThreshold)
            .def("getFlags",
                 [](PxHeightField* field) {
                     return field->getFlags().operator uint32_t();
                 })
            .def("getHeight", &PxHeightField::getHeight)
            .def("getTriangleMaterialIndex", &PxHeightField::getTriangleMaterialIndex)
            .def("getTriangleNormal", &PxHeightField::getTriangleNormal)
            .def("getSample", &PxHeightField::getSample)
            .def("getTimestamp", &PxHeightField::getTimestamp);

    nb::enum_<PxHeightFieldFormat::Enum>(m, "PxHeightFieldFormat").value("eLOCKED", PxHeightFieldFormat::Enum::eS16_TM);
    nb::class_<PxHeightFieldDesc>(m, "PxHeightFieldDesc")
            .def_rw("nbRows", &PxHeightFieldDesc::nbRows)
            .def_rw("nbColumns", &PxHeightFieldDesc::nbColumns)
            .def_rw("format", &PxHeightFieldDesc::format)
            .def_rw("samples", &PxHeightFieldDesc::samples)
            .def_rw("convexEdgeThreshold", &PxHeightFieldDesc::convexEdgeThreshold)
            .def("setToDefault", &PxHeightFieldDesc::setToDefault)
            .def("isValid", &PxHeightFieldDesc::isValid);

    nb::class_<PxHeightFieldSample>(m, "PxHeightFieldSample")
            .def_rw("height", &PxHeightFieldSample::height)
            .def("tessFlag", &PxHeightFieldSample::tessFlag)
            .def("setTessFlag", &PxHeightFieldSample::setTessFlag)
            .def("clearTessFlag", &PxHeightFieldSample::clearTessFlag);

    nb::class_<PxStridedData> pxStridedData(m, "PxStridedData");
}