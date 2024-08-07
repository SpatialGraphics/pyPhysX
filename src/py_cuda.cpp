//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/shared_ptr.h>

#include "py_device.h"
#include "py_cuda.h"
#include <dlfcn.h>
#include <cuda_runtime.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

CudaLib::CudaLib() {
    libcuda = dlopen("libcuda.so", RTLD_LAZY);
    cudaFree(nullptr);  // establish cuda context with runtime API
    this->cuCtxGetCurrent = (decltype(::cuCtxGetCurrent)*)dlsym(libcuda, "cuCtxGetCurrent");
}

CudaLib& CudaLib::Get() {
    static CudaLib lib;
    if (!lib.libcuda) {
        throw std::runtime_error("failed to load libcuda");
    }
    return lib;
}

void bindCuda(nb::module_& m) {
    m.def("PxSetPhysXGpuProfilerCallback", &PxSetPhysXGpuProfilerCallback)
            .def(
                    "PxCreateCudaContextManager",
                    [](physx::PxFoundation& foundation, std::shared_ptr<Device>& device) {
                        PxCudaContextManagerDesc cudaContextManagerDesc;
                        CUcontext context{};

                        checkCudaErrors(cudaSetDevice(device->cudaId));

                        // NOTE: context initialization seems inconsistent across cuda versions
                        // cudaFree(0) is guaranteed to establish context
                        checkCudaErrors(cudaFree(nullptr));

                        checkCudaDriverErrors(CudaLib::Get().cuCtxGetCurrent(&context));
                        if (!context) {
                            throw std::runtime_error("failed to get CUDA context.");
                        }
                        cudaContextManagerDesc.ctx = &context;

                        return PxCreateCudaContextManager(foundation, cudaContextManagerDesc);
                    },
                    "foundation"_a, "device"_a, nb::rv_policy::reference);

    nb::class_<PxCudaContextManager>(m, "PxCudaContextManager")
            .def("acquireContext", &PxCudaContextManager::acquireContext)
            .def("releaseContext", &PxCudaContextManager::releaseContext)
            .def("contextIsValid", &PxCudaContextManager::contextIsValid)
            .def("supportsArchSM10", &PxCudaContextManager::supportsArchSM10)
            .def("supportsArchSM11", &PxCudaContextManager::supportsArchSM11)
            .def("supportsArchSM12", &PxCudaContextManager::supportsArchSM12)
            .def("supportsArchSM13", &PxCudaContextManager::supportsArchSM13)
            .def("supportsArchSM20", &PxCudaContextManager::supportsArchSM20)
            .def("supportsArchSM30", &PxCudaContextManager::supportsArchSM30)
            .def("supportsArchSM35", &PxCudaContextManager::supportsArchSM35)
            .def("supportsArchSM50", &PxCudaContextManager::supportsArchSM50)
            .def("supportsArchSM52", &PxCudaContextManager::supportsArchSM52)
            .def("supportsArchSM60", &PxCudaContextManager::supportsArchSM60)
            .def("isIntegrated", &PxCudaContextManager::isIntegrated)
            .def("canMapHostMemory", &PxCudaContextManager::canMapHostMemory)
            .def("getDriverVersion", &PxCudaContextManager::getDriverVersion)
            .def("getDeviceTotalMemBytes", &PxCudaContextManager::getDeviceTotalMemBytes)
            .def("getMultiprocessorCount", &PxCudaContextManager::getMultiprocessorCount)
            .def("getClockRate", &PxCudaContextManager::getClockRate)
            .def("getSharedMemPerBlock", &PxCudaContextManager::getSharedMemPerBlock)
            .def("getSharedMemPerMultiprocessor", &PxCudaContextManager::getSharedMemPerMultiprocessor)
            .def("getMaxThreadsPerBlock", &PxCudaContextManager::getMaxThreadsPerBlock)
            .def("getDeviceName", &PxCudaContextManager::getDeviceName)
            .def_prop_rw("usingConcurrentStreams", &PxCudaContextManager::getUsingConcurrentStreams,
                         &PxCudaContextManager::setUsingConcurrentStreams)
            .def("getDeviceName", &PxCudaContextManager::getDeviceName)
            .def("getDeviceName", &PxCudaContextManager::getDeviceName)
            .def("getDeviceName", &PxCudaContextManager::getDeviceName)
            .def("usingDedicatedGPU", &PxCudaContextManager::usingDedicatedGPU)
            .def("release", &PxCudaContextManager::release);

    class ProfilerCallback : public PxProfilerCallback {
    public:
        void zoneEnd(void* profilerData, const char* eventName, bool detached, uint64_t contextId) override {}
        void* zoneStart(const char* eventName, bool detached, uint64_t contextId) override { return nullptr; }
    };
    nb::class_<PxProfilerCallback> pxProfilerCallback(m, "PxProfilerCallback");
    nb::class_<ProfilerCallback, PxProfilerCallback> profilerCallback(m, "ProfilerCallback");
}