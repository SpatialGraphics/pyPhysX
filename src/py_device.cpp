//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include "py_device.h"

#ifdef SUPPORT_CUDA
#include <cuda_runtime.h>
#endif
#include <vector>
#include <stdexcept>

#include <nanobind/nanobind.h>
#include <nanobind/stl/array.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/shared_ptr.h>

namespace nb = nanobind;
using namespace nb::literals;

#ifdef SUPPORT_CUDA

static std::array<uint32_t, 4> parsePCIString(const std::string& s) {
    if (s.length() == 12) {
        return {static_cast<uint32_t>(std::stoi(s.substr(0, 4), nullptr, 16)),
                static_cast<uint32_t>(std::stoi(s.substr(5, 2), nullptr, 16)),
                static_cast<uint32_t>(std::stoi(s.substr(8, 2), nullptr, 16)),
                static_cast<uint32_t>(std::stoi(s.substr(11, 1), nullptr, 16))};
    }
    if (s.length() == 7) {
        return {0u, static_cast<uint32_t>(std::stoi(s.substr(0, 2), nullptr, 16)),
                static_cast<uint32_t>(std::stoi(s.substr(3, 2), nullptr, 16)),
                static_cast<uint32_t>(std::stoi(s.substr(6, 1), nullptr, 16))};
    }
    throw std::runtime_error("invalid PCI string");
}

static std::vector<std::shared_ptr<Device>> cudaFindDevices() {
    std::vector<std::shared_ptr<Device>> res;

    int nDevices;
    if (cudaGetDeviceCount(&nDevices) != cudaSuccess) {
        return res;
    }
    for (int i = 0; i < nDevices; i++) {
        cudaDeviceProp prop{};
        if (cudaGetDeviceProperties(&prop, i) != cudaSuccess) {
            continue;
        }
        char pci[20] = {0};
        if (cudaDeviceGetPCIBusId(pci, 20, i) != cudaSuccess) {
            continue;
        }

        res.push_back(std::make_shared<Device>(Device{
                .type = Device::Type::GPU, .name = prop.name, .cudaId = i, .pci = parsePCIString(std::string(pci))}));
    }
    return res;
}
#endif

static std::vector<std::shared_ptr<Device>> findDevices() {
    std::vector<std::shared_ptr<Device>> devices;
    devices.push_back(std::make_shared<Device>(Device{.type = Device::Type::CPU, .name = "cpu", .cudaId = -1}));

#ifdef SUPPORT_CUDA
    auto cudaDevices = cudaFindDevices();
    devices.insert(devices.end(), cudaDevices.begin(), cudaDevices.end());
#endif

    return devices;
}

std::string Device::getAlias() const {
    if (isCpu()) {
        return "cpu";
    }
    if (cudaId >= 0) {
        return "cuda:" + std::to_string(cudaId);
    }
    if (isGpu()) {
        char pciString[20] = {0};
        sprintf(pciString, "%04x:%02x:%02x.%1x", pci[0], pci[1], pci[2], pci[3]);
        return "pci:" + std::string(pciString);
    }
    return "unknown";
}

template <typename CharT, typename Traits = std::char_traits<CharT>, typename Allocator = std::allocator<CharT>>
bool starts_with(const std::basic_string<CharT, Traits, Allocator>& str,
                 const std::basic_string<CharT, Traits, Allocator>& prefix) {
    // Check if the prefix is longer than the string
    if (prefix.size() > str.size()) {
        return false;
    }
    // Compare the beginning of the string with the prefix
    return std::equal(prefix.begin(), prefix.end(), str.begin());
}

static std::vector<std::shared_ptr<Device>> gDevices;

std::shared_ptr<Device> findDevice(const std::string& alias) {
    if (gDevices.empty()) {
        gDevices = findDevices();
    }

    // CPU
    if (alias == "cpu") {
        for (auto d : gDevices) {
            if (d->isCpu()) {
                return d;
            }
        }
        throw std::runtime_error("failed to find device \"" + alias + "\"");
    }

    // CUDA
    if (starts_with(alias, std::string("cuda"))) {
        // any cuda
        if (alias == "cuda") {
            for (auto d : gDevices) {
                if (d->isCuda()) {
                    return d;
                }
            }
        }

        // cuda with id
        if (starts_with(alias, std::string("cuda:"))) {
            int id = std::stoi(alias.substr(5));
            for (auto d : gDevices) {
                if (d->cudaId == id) {
                    return d;
                }
            }
        }

        throw std::runtime_error("failed to find device \"" + alias + "\"");
    }

    // PCI
    if (starts_with(alias, std::string("pci:"))) {
        try {
            std::array<uint32_t, 4> pci = parsePCIString(alias.substr(4));
            for (auto d : gDevices) {
                if (d->isGpu() && d->pci == pci) {
                    return d;
                }
            }
        } catch (std::runtime_error const&) {
        }

        try {
            uint32_t busId = std::stoi(alias.substr(4), nullptr, 16);
            for (auto d : gDevices) {
                if (d->isGpu() && d->pci[1] == busId) {
                    return d;
                }
            }
        } catch (std::runtime_error const&) {
        }

        throw std::runtime_error("failed to find device \"" + alias + "\"");
    }

    throw std::runtime_error("failed to find device \"" + alias + "\"");
}

void bindDevice(nb::module_& m) {
    m.def("findDevice", &findDevice);

    nb::class_<Device> device(m, "Device");
    device.def("isCpu", &Device::isCpu)
            .def("isGpu", &Device::isGpu)
            .def("isCuda", &Device::isCuda)
            .def("getAlias", &Device::getAlias)
            .def_ro("type", &Device::type)
            .def_ro("name", &Device::name)
            .def_ro("cudaId", &Device::cudaId)
            .def_ro("pci", &Device::pci);

    nb::enum_<Device::Type>(device, "Type")
            .value("CPU", Device::Type::CPU)
            .value("GPU", Device::Type::GPU)
            .value("OTHER", Device::Type::OTHER);
}