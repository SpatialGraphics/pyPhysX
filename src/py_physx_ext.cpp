//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <nanobind/nanobind.h>
#include <PxMaterial.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

extern void bindMath(nb::module_& m);
extern void bindMaterial(nb::module_& m);
extern void bindActor(nb::module_& m);
extern void bindShape(nb::module_& m);

NB_MODULE(py_physx_ext, m) {
    m.doc() = "python binding for PhysX";

    bindMath(m);
    bindMaterial(m);
    bindActor(m);
    bindShape(m);
}
