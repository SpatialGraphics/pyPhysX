//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

void bindCuda(nb::module_& m) {
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
}