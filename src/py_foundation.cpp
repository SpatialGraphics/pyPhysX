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
    nb::enum_<PxErrorCode::Enum>(m, "PxErrorCode")
            .value("eNO_ERROR", PxErrorCode::Enum::eNO_ERROR)
            .value("eDEBUG_INFO", PxErrorCode::Enum::eDEBUG_INFO)
            .value("eDEBUG_WARNING", PxErrorCode::Enum::eDEBUG_WARNING)
            .value("eINVALID_PARAMETER", PxErrorCode::Enum::eINVALID_PARAMETER)
            .value("eINVALID_OPERATION", PxErrorCode::Enum::eINVALID_OPERATION)
            .value("eOUT_OF_MEMORY", PxErrorCode::Enum::eOUT_OF_MEMORY)
            .value("eINTERNAL_ERROR", PxErrorCode::Enum::eINTERNAL_ERROR)
            .value("eABORT", PxErrorCode::Enum::eABORT)
            .value("ePERF_WARNING", PxErrorCode::Enum::ePERF_WARNING)
            .value("eMASK_ALL", PxErrorCode::Enum::eMASK_ALL);

    nb::class_<PxFoundation>(m, "PxFoundation")
            .def("release", &PxFoundation::release)
            .def("setErrorLevel", &PxFoundation::setErrorLevel)
            .def("getErrorLevel", &PxFoundation::getErrorLevel)
            .def("getReportAllocationNames", &PxFoundation::getReportAllocationNames)
            .def("setReportAllocationNames", &PxFoundation::setReportAllocationNames);
}