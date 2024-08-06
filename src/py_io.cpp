//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

void bindIO(nb::module_& m) {
    nb::class_<PxInputStream>(m, "PxInputStream").def("write", [](PxInputStream* stream, nb::ndarray<uint8_t> buffer) {
        return stream->read(buffer.data(), buffer.nbytes());
    });
    nb::class_<PxInputData, PxInputStream>(m, "PxInputData")
            .def("getLength", &PxInputData::getLength)
            .def("seek", &PxInputData::seek)
            .def("tell", &PxInputData::tell);
    nb::class_<PxDefaultMemoryInputData, PxInputData>(m, "PxDefaultMemoryInputData")
            .def("getLength", &PxDefaultMemoryInputData::getLength)
            .def("seek", &PxDefaultMemoryInputData::seek)
            .def("tell", &PxDefaultMemoryInputData::tell);
    nb::class_<PxDefaultFileInputData, PxInputData>(m, "PxDefaultFileInputData").def(nb::init<const char*>());

    nb::class_<PxOutputStream>(m, "PxOutputStream")
            .def("write", [](PxOutputStream* stream, nb::ndarray<uint8_t> buffer) {
                return stream->write(buffer.data(), buffer.nbytes());
            });
    nb::class_<PxDefaultMemoryOutputStream, PxOutputStream>(m, "PxDefaultMemoryOutputStream")
            .def("getSize", &PxDefaultMemoryOutputStream::getSize);
    nb::class_<PxDefaultFileOutputStream, PxOutputStream>(m, "PxDefaultFileOutputStream").def(nb::init<const char*>());
}