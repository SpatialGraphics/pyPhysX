//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>

#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

void bindMath(nb::module_& m) {
    nb::class_<PxVec3>(m, "PxVec3")
            .def(nb::init<>())
            .def(nb::init<float>())
            .def(nb::init<float, float, float>())
            .def_rw("x", &PxVec3::x)
            .def_rw("y", &PxVec3::y)
            .def_rw("z", &PxVec3::z)
            .def("isZero", &PxVec3::isZero)
            .def("isFinite", &PxVec3::isFinite)
            .def("isNormalized", &PxVec3::isNormalized)
            .def("magnitudeSquared", &PxVec3::magnitudeSquared)
            .def("magnitude", &PxVec3::magnitude)
            .def("dot", &PxVec3::dot)
            .def("cross", &PxVec3::cross)
            .def("getNormalized", &PxVec3::getNormalized)
            .def("normalize", &PxVec3::normalize)
            .def("normalizeSafe", &PxVec3::normalizeSafe)
            .def("normalizeFast", &PxVec3::normalizeFast)
            .def("multiply", &PxVec3::multiply)
            .def("minimum", &PxVec3::minimum)
            .def("minElement", &PxVec3::minElement)
            .def("maximum", &PxVec3::maximum)
            .def("maxElement", &PxVec3::maxElement)
            .def("abs", &PxVec3::abs)
            .def("abs", &PxVec3::abs)
            .def("__iadd__", &PxVec3::operator+=)
            .def("__add__", &PxVec3::operator+)
            .def("__isub__", &PxVec3::operator-=)
            .def("__sub__",
                 [](PxVec3& s, const PxVec3& factor) {
                     return s - factor;
                 })
            .def("__imul__", &PxVec3::operator*=)
            .def("__mul__", &PxVec3::operator*)
            .def("__itruediv__", &PxVec3::operator/=)
            .def("__truediv__", &PxVec3::operator/)
            .def("__neg__",
                 [](PxVec3& s) {
                     return -s;
                 })
            .def("__ne__", &PxVec3::operator!=)
            .def("__eq__", &PxVec3::operator==)
            .def("__setitem__",
                 [](PxVec3& self, unsigned index, float val) {
                     self[index] = val;
                 })
            .def("__getitem__", [](PxVec3& self, unsigned index) {
                return self[index];
            });

    nb::class_<PxQuat>(m, "PxQuat")
            .def(nb::init<>())
            .def(nb::init<float>())
            .def(nb::init<float, float, float, float>(), "nx"_a, "ny"_a, "nz"_a, "nw"_a)
            .def(nb::init<float, PxVec3>(), "angleRadians"_a, "unitAxis"_a)
            .def(nb::init<PxMat33>(), "m"_a)
            .def_rw("x", &PxQuat::x)
            .def_rw("y", &PxQuat::y)
            .def_rw("z", &PxQuat::z)
            .def_rw("w", &PxQuat::w)
            .def("isIdentity", &PxQuat::isIdentity)
            .def("isFinite", &PxQuat::isFinite)
            .def("isUnit", &PxQuat::isUnit)
            .def("isSane", &PxQuat::isSane)
            .def("toRadiansAndUnitAxis", &PxQuat::toRadiansAndUnitAxis)
            .def("getAngle", nb::overload_cast<>(&PxQuat::getAngle, nb::const_))
            .def("getAngle", nb::overload_cast<const PxQuat&>(&PxQuat::getAngle, nb::const_))
            .def("magnitudeSquared", &PxQuat::magnitudeSquared)
            .def("dot", &PxQuat::dot)
            .def("getNormalized", &PxQuat::getNormalized)
            .def("magnitude", &PxQuat::magnitude)
            .def("normalize", &PxQuat::normalize)
            .def("getConjugate", &PxQuat::getConjugate)
            .def("getImaginaryPart", &PxQuat::getImaginaryPart)
            .def("getBasisVector0", &PxQuat::getBasisVector0)
            .def("getBasisVector1", &PxQuat::getBasisVector1)
            .def("getBasisVector2", &PxQuat::getBasisVector2)
            .def("rotate", &PxQuat::rotate)
            .def("rotateInv", &PxQuat::rotateInv);

    nb::class_<PxTransform>(m, "PxTransform")
            .def_rw("translation", &PxTransform::p)
            .def_rw("rotation", &PxTransform::q);
    nb::class_<PxExtendedVec3>(m, "PxExtendedVec3")
            .def_rw("x", &PxExtendedVec3::x)
            .def_rw("y", &PxExtendedVec3::y)
            .def_rw("z", &PxExtendedVec3::z);

    nb::enum_<PxIDENTITY>(m, "PxIDENTITY").value("PxIdentity", PxIDENTITY::PxIdentity);
}