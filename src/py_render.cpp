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

void bindRender(nb::module_& m) {
    nb::class_<PxRenderBuffer>(m, "PxRenderBuffer")
            .def("getNbPoints", &PxRenderBuffer::getNbPoints)
            .def("addPoint", &PxRenderBuffer::addPoint, "point"_a)
            .def("getNbLines", &PxRenderBuffer::getNbLines)
            .def("addLine", &PxRenderBuffer::addLine, "line"_a)
            .def("getNbTriangles", &PxRenderBuffer::getNbTriangles)
            .def("addTriangle", &PxRenderBuffer::addTriangle, "triangle"_a)
            .def("append", &PxRenderBuffer::append, "other"_a)
            .def("clear", &PxRenderBuffer::clear)
            .def("shift", &PxRenderBuffer::shift, "delta"_a)
            .def("empty", &PxRenderBuffer::empty);

    nb::class_<PxDebugPoint>(m, "PxDebugPoint")
            .def(nb::init<PxVec3, PxU32>())
            .def_rw("pos", &PxDebugPoint::pos)
            .def_rw("color", &PxDebugPoint::color);

    nb::class_<PxDebugLine>(m, "PxDebugLine")
            .def(nb::init<PxVec3, PxVec3, PxU32>())
            .def_rw("pos0", &PxDebugLine::pos0)
            .def_rw("color0", &PxDebugLine::color0)
            .def_rw("pos1", &PxDebugLine::pos1)
            .def_rw("color1", &PxDebugLine::color1);

    nb::class_<PxDebugTriangle>(m, "PxDebugTriangle")
            .def(nb::init<PxVec3, PxVec3, PxVec3, PxU32>())
            .def_rw("pos0", &PxDebugTriangle::pos0)
            .def_rw("color0", &PxDebugTriangle::color0)
            .def_rw("pos1", &PxDebugTriangle::pos1)
            .def_rw("color1", &PxDebugTriangle::color1)
            .def_rw("pos2", &PxDebugTriangle::pos2)
            .def_rw("color2", &PxDebugTriangle::color2);
}