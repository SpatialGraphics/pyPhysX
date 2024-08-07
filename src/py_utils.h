//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#pragma once

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>

#include <string>

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

template <typename enumtype, typename storagetype = uint32_t>
void bindFlags(nb::module_& m, const char* name) {
    nb::class_<PxFlags<enumtype, storagetype>>(m, name)
            .def(nb::init<>())
            .def(nb::init<enumtype>())
            .def(nb::init<storagetype>())
            .def("__ne__",
                 [](PxFlags<enumtype, storagetype>& lv, PxFlags<enumtype, storagetype>& rv) {
                     return lv != rv;
                 })
            .def("__ne__",
                 [](PxFlags<enumtype, storagetype>& lv, enumtype& rv) {
                     return lv != rv;
                 })
            .def("__eq__",
                 [](PxFlags<enumtype, storagetype>& lv, PxFlags<enumtype, storagetype>& rv) {
                     return lv == rv;
                 })
            .def("__eq__",
                 [](PxFlags<enumtype, storagetype>& lv, enumtype& rv) {
                     return lv == rv;
                 })
            .def("__or__",
                 [](PxFlags<enumtype, storagetype>& lv, PxFlags<enumtype, storagetype>& rv) {
                     return lv | rv;
                 })
            .def("__or__",
                 [](PxFlags<enumtype, storagetype>& lv, enumtype& rv) {
                     return lv | rv;
                 })
            .def("__ior__",
                 [](PxFlags<enumtype, storagetype>& lv, PxFlags<enumtype, storagetype>& rv) {
                     lv |= rv;
                 })
            .def("__ior__",
                 [](PxFlags<enumtype, storagetype>& lv, enumtype& rv) {
                     lv |= rv;
                 })
            .def("__and__",
                 [](PxFlags<enumtype, storagetype>& lv, PxFlags<enumtype, storagetype>& rv) {
                     return lv & rv;
                 })
            .def("__and__",
                 [](PxFlags<enumtype, storagetype>& lv, enumtype& rv) {
                     return lv & rv;
                 })
            .def("__iand__",
                 [](PxFlags<enumtype, storagetype>& lv, PxFlags<enumtype, storagetype>& rv) {
                     lv &= rv;
                 })
            .def("__iand__",
                 [](PxFlags<enumtype, storagetype>& lv, enumtype& rv) {
                     lv &= rv;
                 })
            .def("__xor__",
                 [](PxFlags<enumtype, storagetype>& lv, PxFlags<enumtype, storagetype>& rv) {
                     return lv ^ rv;
                 })
            .def("__xor__",
                 [](PxFlags<enumtype, storagetype>& lv, enumtype& rv) {
                     return lv ^ rv;
                 })
            .def("__ixor__",
                 [](PxFlags<enumtype, storagetype>& lv, PxFlags<enumtype, storagetype>& rv) {
                     lv ^= rv;
                 })
            .def("__ixor__",
                 [](PxFlags<enumtype, storagetype>& lv, enumtype& rv) {
                     lv ^= rv;
                 })
            .def("__invert__",
                 [](PxFlags<enumtype, storagetype>& lv) {
                     return ~lv;
                 })
            .def("value",
                 [](PxFlags<enumtype, storagetype>& lv) {
                     return lv.operator uint32_t();
                 })
            .def("clear", &PxFlags<enumtype, storagetype>::clear)
            .def("isSet", &PxFlags<enumtype, storagetype>::isSet)
            .def("setAll", &PxFlags<enumtype, storagetype>::setAll);
}