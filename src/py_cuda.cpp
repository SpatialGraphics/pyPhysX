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
            .def("usingDedicatedGPU", &PxCudaContextManager::usingDedicatedGPU)
            .def("release", &PxCudaContextManager::release);
}