//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <PxFEMClothMaterial.h>

#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

void bindFoundation(nb::module_& m) {
    nb::class_<PxFoundation>(m, "PxFoundation")
            .def("release", &PxFoundation::release)
            .def("setErrorLevel", &PxFoundation::setErrorLevel)
            .def("getErrorLevel", &PxFoundation::getErrorLevel)
            .def("getReportAllocationNames", &PxFoundation::getReportAllocationNames)
            .def("setReportAllocationNames", &PxFoundation::setReportAllocationNames);
}