//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>

#include <nanobind/nanobind.h>
#include <nanobind/stl/array.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

void bindMaterial(nb::module_& m) {
    nb::class_<PxMaterial>(m, "PxMaterial")
            .def("setDynamicFriction", &PxMaterial::setDynamicFriction, "coef"_a)
            .def("getDynamicFriction", &PxMaterial::getDynamicFriction)
            .def("setStaticFriction", &PxMaterial::setStaticFriction, "coef"_a)
            .def("getStaticFriction", &PxMaterial::getStaticFriction)
            .def("setRestitution", &PxMaterial::setRestitution, "rest"_a)
            .def("getRestitution", &PxMaterial::getRestitution)
            .def("setDamping", &PxMaterial::setDamping, "damping"_a)
            .def("getDamping", &PxMaterial::getDamping)
            .def("setFrictionCombineMode", &PxMaterial::setFrictionCombineMode, "combMode"_a)
            .def("getFrictionCombineMode", &PxMaterial::getFrictionCombineMode)
            .def("setRestitutionCombineMode", &PxMaterial::setRestitutionCombineMode, "combMode"_a)
            .def("getRestitutionCombineMode", &PxMaterial::getRestitutionCombineMode)
            .def("setDampingCombineMode", &PxMaterial::setDampingCombineMode, "combMode"_a)
            .def("getDampingCombineMode", &PxMaterial::getDampingCombineMode);

    nb::enum_<PxCombineMode::Enum>(m, "PxCombineMode")
            .value("eAVERAGE", PxCombineMode::Enum::eAVERAGE)
            .value("eMIN", PxCombineMode::Enum::eMIN)
            .value("eMULTIPLY", PxCombineMode::Enum::eMULTIPLY)
            .value("eMAX", PxCombineMode::Enum::eMAX);
}