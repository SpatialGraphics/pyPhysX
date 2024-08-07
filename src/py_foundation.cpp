//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <PxFEMClothMaterial.h>

#include <nanobind/nanobind.h>
#include <nanobind/stl/function.h>

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
            .def_prop_rw("errorLevel", &PxFoundation::getErrorLevel, &PxFoundation::setErrorLevel)
            .def_prop_rw("reportAllocationNames", &PxFoundation::getReportAllocationNames,
                         &PxFoundation::setReportAllocationNames);

    class ErrorCallback : public PxErrorCallback {
    public:
        ~ErrorCallback() override = default;

        explicit ErrorCallback(const std::function<void(PxErrorCode::Enum, const char*, const char*, int)>& c) : c(c) {}

        void reportError(PxErrorCode::Enum code, const char* message, const char* file, int line) override {
            c(code, message, file, line);
        }

    private:
        std::function<void(PxErrorCode::Enum, const char*, const char*, int)> c;
    };
    nb::class_<PxErrorCallback>(m, "PxErrorCallback").def("reportError", &PxErrorCallback::reportError);
    nb::class_<ErrorCallback, PxErrorCallback>(m, "ErrorCallback")
            .def(nb::init<const std::function<void(PxErrorCode::Enum, const char*, const char*, int)>&>());

    static PxDefaultAllocator gDefaultAllocatorCallback;
    static PxDefaultErrorCallback defaultErrorCallback; // todo
    m.def(
            "PxCreateFoundation",
            [](ErrorCallback& callback) {
                return PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, defaultErrorCallback);
            },
            "callback"_a, nb::rv_policy::reference);
}