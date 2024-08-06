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

void bindMath(nb::module_& m) {
    nb::class_<PxVec3d>(m, "PxVec3d")
            .def(nb::init<>())
            .def(nb::init<double>(), "a"_a)
            .def(nb::init<double, double, double>(), "nx"_a, "ny"_a, "nz"_a)
            .def_rw("x", &PxVec3d::x)
            .def_rw("y", &PxVec3d::y)
            .def_rw("z", &PxVec3d::z)
            .def("isZero", &PxVec3d::isZero)
            .def("isFinite", &PxVec3d::isFinite)
            .def("isNormalized", &PxVec3d::isNormalized)
            .def("magnitudeSquared", &PxVec3d::magnitudeSquared)
            .def("magnitude", &PxVec3d::magnitude)
            .def("dot", &PxVec3d::dot, "v"_a)
            .def("cross", &PxVec3d::cross, "v"_a)
            .def("getNormalized", &PxVec3d::getNormalized)
            .def("normalize", &PxVec3d::normalize)
            .def("normalizeSafe", &PxVec3d::normalizeSafe)
            .def("normalizeFast", &PxVec3d::normalizeFast)
            .def("multiply", &PxVec3d::multiply, "a"_a)
            .def("minimum", &PxVec3d::minimum, "v"_a)
            .def("minElement", &PxVec3d::minElement)
            .def("maximum", &PxVec3d::maximum, "v"_a)
            .def("maxElement", &PxVec3d::maxElement)
            .def("abs", &PxVec3d::abs)
            .def("__iadd__", &PxVec3d::operator+=)
            .def("__add__", &PxVec3d::operator+)
            .def("__isub__", &PxVec3d::operator-=)
            .def("__sub__",
                 [](PxVec3d& s, const PxVec3d& factor) {
                     return s - factor;
                 })
            .def("__imul__", &PxVec3d::operator*=)
            .def("__mul__", &PxVec3d::operator*)
            .def("__itruediv__", &PxVec3d::operator/=)
            .def("__truediv__", &PxVec3d::operator/)
            .def("__neg__",
                 [](PxVec3d& s) {
                     return -s;
                 })
            .def("__ne__", &PxVec3d::operator!=)
            .def("__eq__", &PxVec3d::operator==)
            .def("__setitem__",
                 [](PxVec3d& self, unsigned index, double val) {
                     self[index] = val;
                 })
            .def("__getitem__", [](PxVec3d& self, unsigned index) {
                return self[index];
            });

    nb::class_<PxVec3>(m, "PxVec3")
            .def(nb::init<>())
            .def(nb::init<float>(), "a"_a)
            .def(nb::init<float, float, float>(), "nx"_a, "ny"_a, "nz"_a)
            .def_rw("x", &PxVec3::x)
            .def_rw("y", &PxVec3::y)
            .def_rw("z", &PxVec3::z)
            .def("isZero", &PxVec3::isZero)
            .def("isFinite", &PxVec3::isFinite)
            .def("isNormalized", &PxVec3::isNormalized)
            .def("magnitudeSquared", &PxVec3::magnitudeSquared)
            .def("magnitude", &PxVec3::magnitude)
            .def("dot", &PxVec3::dot, "v"_a)
            .def("cross", &PxVec3::cross, "v"_a)
            .def("getNormalized", &PxVec3::getNormalized)
            .def("normalize", &PxVec3::normalize)
            .def("normalizeSafe", &PxVec3::normalizeSafe)
            .def("normalizeFast", &PxVec3::normalizeFast)
            .def("multiply", &PxVec3::multiply, "a"_a)
            .def("minimum", &PxVec3::minimum, "v"_a)
            .def("minElement", &PxVec3::minElement)
            .def("maximum", &PxVec3::maximum, "v"_a)
            .def("maxElement", &PxVec3::maxElement)
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

    nb::class_<PxVec4>(m, "PxVec4")
            .def(nb::init<>())
            .def(nb::init<float>(), "a"_a)
            .def(nb::init<float, float, float, float>(), "nx"_a, "ny"_a, "nz"_a, "nw"_a)
            .def_rw("x", &PxVec4::x)
            .def_rw("y", &PxVec4::y)
            .def_rw("z", &PxVec4::z)
            .def_rw("w", &PxVec4::w)
            .def("isZero", &PxVec4::isZero)
            .def("isFinite", &PxVec4::isFinite)
            .def("isNormalized", &PxVec4::isNormalized)
            .def("magnitudeSquared", &PxVec4::magnitudeSquared)
            .def("magnitude", &PxVec4::magnitude)
            .def("dot", &PxVec4::dot, "v"_a)
            .def("getNormalized", &PxVec4::getNormalized)
            .def("normalize", &PxVec4::normalize)
            .def("multiply", &PxVec4::multiply, "a"_a)
            .def("minimum", &PxVec4::minimum, "v"_a)
            .def("maximum", &PxVec4::maximum, "v"_a)
            .def("__iadd__", &PxVec4::operator+=)
            .def("__add__", &PxVec4::operator+)
            .def("__isub__", &PxVec4::operator-=)
            .def("__sub__",
                 [](PxVec4& s, const PxVec4& factor) {
                     return s - factor;
                 })
            .def("__imul__", &PxVec4::operator*=)
            .def("__mul__", &PxVec4::operator*)
            .def("__itruediv__", &PxVec4::operator/=)
            .def("__truediv__", &PxVec4::operator/)
            .def("__neg__",
                 [](PxVec4& s) {
                     return -s;
                 })
            .def("__ne__", &PxVec4::operator!=)
            .def("__eq__", &PxVec4::operator==)
            .def("__setitem__",
                 [](PxVec4& self, unsigned index, float val) {
                     self[index] = val;
                 })
            .def("__getitem__", [](PxVec4& self, unsigned index) {
                return self[index];
            });

    nb::class_<PxQuat>(m, "PxQuat")
            .def(nb::init<>())
            .def(nb::init<float>(), "a"_a)
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
            .def("toRadiansAndUnitAxis", &PxQuat::toRadiansAndUnitAxis, "angle"_a, "axis"_a)
            .def("getAngle", nb::overload_cast<>(&PxQuat::getAngle, nb::const_))
            .def("getAngle", nb::overload_cast<const PxQuat&>(&PxQuat::getAngle, nb::const_))
            .def("magnitudeSquared", &PxQuat::magnitudeSquared)
            .def("dot", &PxQuat::dot, "v"_a)
            .def("getNormalized", &PxQuat::getNormalized)
            .def("magnitude", &PxQuat::magnitude)
            .def("normalize", &PxQuat::normalize)
            .def("getConjugate", &PxQuat::getConjugate)
            .def("getImaginaryPart", &PxQuat::getImaginaryPart)
            .def("getBasisVector0", &PxQuat::getBasisVector0)
            .def("getBasisVector1", &PxQuat::getBasisVector1)
            .def("getBasisVector2", &PxQuat::getBasisVector2)
            .def("rotate", &PxQuat::rotate, "v"_a)
            .def("rotateInv", &PxQuat::rotateInv, "v"_a)
            .def("__iadd__", &PxQuat::operator+=)
            .def("__add__", &PxQuat::operator+)
            .def("__isub__", &PxQuat::operator-=)
            .def("__sub__",
                 [](PxQuat& s, const PxQuat& factor) {
                     return s - factor;
                 })
            .def("__imul__",
                 [](PxQuat& s, const PxQuat& factor) {
                     s *= factor;
                 })
            .def("__imul__",
                 [](PxQuat& s, const float& factor) {
                     s *= factor;
                 })
            .def("__mul__",
                 [](PxQuat& s, const PxQuat& factor) {
                     return s * factor;
                 })
            .def("__mul__",
                 [](PxQuat& s, const float& factor) {
                     return s * factor;
                 })
            .def("__neg__",
                 [](PxQuat& s) {
                     return -s;
                 })
            .def("__eq__", &PxQuat::operator==);

    nb::class_<PxTransform>(m, "PxTransform")
            .def(nb::init())
            .def(nb::init<PxVec3>(), "position"_a)
            .def(nb::init<PxQuat>(), "orientation"_a)
            .def(nb::init<float, float, float, PxQuat>(), "x"_a, "y"_a, "z"_a, "aQ"_a)
            .def(nb::init<PxVec3, PxQuat>(), "p0"_a, "q0"_a)
            .def(nb::init<PxMat44>())
            .def_rw("translation", &PxTransform::p)
            .def_rw("rotation", &PxTransform::q)
            .def("getInverse", &PxTransform::getInverse)
            .def("getNormalized", &PxTransform::getNormalized)
            .def("transform", nb::overload_cast<const PxVec3&>(&PxTransform::transform, nb::const_), "input"_a)
            .def("transform", nb::overload_cast<const PxTransform&>(&PxTransform::transform, nb::const_), "input"_a)
            .def("transformInv", nb::overload_cast<const PxVec3&>(&PxTransform::transformInv, nb::const_), "input"_a)
            .def("transformInv", nb::overload_cast<const PxTransform&>(&PxTransform::transformInv, nb::const_),
                 "input"_a)
            .def("rotate", &PxTransform::rotate, "input"_a)
            .def("rotateInv", &PxTransform::rotateInv, "input"_a)
            .def("isValid", &PxTransform::isValid)
            .def("isSane", &PxTransform::isSane)
            .def("isFinite", &PxTransform::isFinite)
            .def("__eq__", &PxTransform::operator==)
            .def("__imul__", &PxTransform::operator*=)
            .def("__mul__", &PxTransform::operator*);

    nb::class_<PxMat33>(m, "PxMat33")
            .def(nb::init())
            .def(nb::init<PxVec3, PxVec3, PxVec3>(), "col0"_a, "col1"_a, "col2"_a)
            .def(nb::init<float>(), "v"_a)
            .def("__init__",
                 [](std::array<float, 9>& array) {
                     return PxMat33(array.data());
                 })
            .def(nb::init<PxQuat>(), "q"_a)
            .def_static("createDiagonal", &PxMat33::createDiagonal, "d"_a)
            .def_static("outer", &PxMat33::outer, "a"_a, "b"_a)
            .def("getTranspose", &PxMat33::getTranspose)
            .def("getInverse", &PxMat33::getInverse)
            .def("getDeterminant", &PxMat33::getDeterminant)
            .def("transform", &PxMat33::transform, "other"_a)
            .def("transformTranspose", &PxMat33::transformTranspose, "other"_a)
            .def("__iadd__", &PxMat33::operator+=)
            .def("__add__", &PxMat33::operator+)
            .def("__isub__", &PxMat33::operator-=)
            .def("__sub__",
                 [](PxMat33& s, const PxMat33& factor) {
                     return s - factor;
                 })
            .def("__imul__",
                 [](PxMat33& s, const PxMat33& factor) {
                     s *= factor;
                 })
            .def("__imul__",
                 [](PxMat33& s, const float& factor) {
                     s *= factor;
                 })
            .def("__mul__",
                 [](PxMat33& s, const PxMat33& factor) {
                     return s * factor;
                 })
            .def("__mul__",
                 [](PxMat33& s, const float& factor) {
                     return s * factor;
                 })
            .def("__neg__",
                 [](PxMat33& s) {
                     return -s;
                 })
            .def("__getitem__",
                 [](const PxMat33& m, std::tuple<size_t, size_t> index) {
                     return m(std::get<0>(index), std::get<1>(index));
                 })
            .def("__setitem__", [](PxMat33& m, std::tuple<size_t, size_t> index, float value) {
                m(std::get<0>(index), std::get<1>(index)) = value;
            });

    nb::class_<PxMat44>(m, "PxMat44")
            .def(nb::init())
            .def(nb::init<PxVec4, PxVec4, PxVec4, PxVec4>(), "col0"_a, "col1"_a, "col2"_a, "col3"_a)
            .def(nb::init<float>(), "v"_a)
            .def("__init__",
                 [](std::array<float, 16>& array) {
                     return PxMat44(array.data());
                 })
            .def(nb::init<PxQuat>(), "q"_a)
            .def(nb::init<PxVec4>(), "diagonal"_a)
            .def(nb::init<PxMat33, PxVec3>(), "axes"_a, "position"_a)
            .def("getTranspose", &PxMat44::getTranspose)
            .def("transform", nb::overload_cast<const PxVec4&>(&PxMat44::transform, nb::const_), "other"_a)
            .def("transform", nb::overload_cast<const PxVec3&>(&PxMat44::transform, nb::const_), "other"_a)
            .def("rotate", nb::overload_cast<const PxVec4&>(&PxMat44::rotate, nb::const_), "other"_a)
            .def("rotate", nb::overload_cast<const PxVec3&>(&PxMat44::rotate, nb::const_), "other"_a)
            .def("getBasis", &PxMat44::getBasis, "num"_a)
            .def("getPosition", &PxMat44::getPosition)
            .def("setPosition", &PxMat44::setPosition, "position"_a)
            .def("scale", &PxMat44::scale, "p"_a)
            .def("inverseRT", &PxMat44::inverseRT)
            .def("isFinite", &PxMat44::isFinite)
            .def("__iadd__", &PxMat44::operator+=)
            .def("__add__", &PxMat44::operator+)
            .def("__isub__", &PxMat44::operator-=)
            .def("__sub__",
                 [](PxMat44& s, const PxMat44& factor) {
                     return s - factor;
                 })
            .def("__imul__",
                 [](PxMat44& s, const PxMat44& factor) {
                     s *= factor;
                 })
            .def("__imul__",
                 [](PxMat44& s, const float& factor) {
                     s *= factor;
                 })
            .def("__mul__",
                 [](PxMat44& s, const PxMat44& factor) {
                     return s * factor;
                 })
            .def("__mul__",
                 [](PxMat44& s, const float& factor) {
                     return s * factor;
                 })
            .def("__neg__",
                 [](PxMat44& s) {
                     return -s;
                 })
            .def("__getitem__",
                 [](const PxMat44& m, std::tuple<size_t, size_t> index) {
                     return m(std::get<0>(index), std::get<1>(index));
                 })
            .def("__setitem__", [](PxMat44& m, std::tuple<size_t, size_t> index, float value) {
                m(std::get<0>(index), std::get<1>(index)) = value;
            });

    nb::class_<PxBounds3>(m, "PxBounds3")
            .def(nb::init())
            .def(nb::init<PxVec3, PxVec3>(), "minimum"_a, "maximum"_a)
            .def_static("empty", &PxBounds3::empty)
            .def_static("boundsOfPoints", &PxBounds3::boundsOfPoints)
            .def_static("centerExtents", &PxBounds3::centerExtents)
            .def_static("basisExtent", &PxBounds3::basisExtent)
            .def_static("poseExtent", &PxBounds3::poseExtent)
            .def_static("transformSafe", nb::overload_cast<const PxMat33&, const PxBounds3&>(&PxBounds3::transformSafe))
            .def_static("transformSafe",
                        nb::overload_cast<const PxTransform&, const PxBounds3&>(&PxBounds3::transformSafe))
            .def_static("transformFast", nb::overload_cast<const PxMat33&, const PxBounds3&>(&PxBounds3::transformFast))
            .def_static("transformFast",
                        nb::overload_cast<const PxTransform&, const PxBounds3&>(&PxBounds3::transformFast))
            .def("setEmpty", &PxBounds3::setEmpty)
            .def("setMaximal", &PxBounds3::setMaximal)
            .def("include", nb::overload_cast<const PxVec3&>(&PxBounds3::include))
            .def("include", nb::overload_cast<const PxBounds3&>(&PxBounds3::include))
            .def("isEmpty", &PxBounds3::isEmpty)
            .def("intersects", &PxBounds3::intersects)
            .def("intersects1D", &PxBounds3::intersects1D)
            .def("contains", &PxBounds3::contains)
            .def("isInside", &PxBounds3::isInside)
            .def("getCenter", nb::overload_cast<>(&PxBounds3::getCenter, nb::const_))
            .def("getCenter", nb::overload_cast<uint32_t>(&PxBounds3::getCenter, nb::const_))
            .def("getExtents", nb::overload_cast<uint32_t>(&PxBounds3::getExtents, nb::const_))
            .def("getDimensions", &PxBounds3::getDimensions)
            .def("getExtents", nb::overload_cast<>(&PxBounds3::getExtents, nb::const_))
            .def("scaleSafe", &PxBounds3::scaleSafe)
            .def("scaleFast", &PxBounds3::scaleFast)
            .def("fattenSafe", &PxBounds3::fattenSafe)
            .def("fattenFast", &PxBounds3::fattenFast)
            .def("isFinite", &PxBounds3::isFinite)
            .def("isValid", &PxBounds3::isValid)
            .def("closestPoint", &PxBounds3::closestPoint)
            .def_rw("minimum", &PxBounds3::minimum)
            .def_rw("maximum", &PxBounds3::maximum);

    nb::enum_<PxZERO>(m, "PxZERO").value("PxZero", PxZERO::PxZero);
    nb::enum_<PxEMPTY>(m, "PxEMPTY").value("PxEmpty", PxEMPTY::PxEmpty);
    nb::enum_<PxIDENTITY>(m, "PxIDENTITY").value("PxIdentity", PxIDENTITY::PxIdentity);
}