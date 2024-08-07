//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/tuple.h>

#include "py_utils.h"

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

void bindUtils(nb::module_& m) {
    nb::class_<PxCounterFrequencyToTensOfNanos>(m, "PxCounterFrequencyToTensOfNanos")
            .def(nb::init<PxU64, PxU64>(), "inNum"_a, "inDenom"_a)
            .def_rw("mDenominator", &PxCounterFrequencyToTensOfNanos::mDenominator)
            .def_rw("mNumerator", &PxCounterFrequencyToTensOfNanos::mNumerator)
            .def("toTensOfNanos", &PxCounterFrequencyToTensOfNanos::toTensOfNanos);

    nb::class_<PxTime>(m, "PxTime")
            .def_static("getCounterFrequency", &PxTime::getCounterFrequency)
            .def_static("getCurrentCounterValue", &PxTime::getCurrentCounterValue);
}