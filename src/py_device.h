//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>

struct Device {
    enum class Type { CPU, GPU, OTHER } type;
    std::string name{};
    int cudaId{-1};
    std::array<uint32_t, 4> pci;

    [[nodiscard]] inline bool isCpu() const { return type == Type::CPU; }
    [[nodiscard]] inline bool isGpu() const { return type == Type::GPU; }
    [[nodiscard]] inline bool isCuda() const { return cudaId >= 0; }

    [[nodiscard]] inline std::optional<std::string> getPciString() const {
        if (isCpu()) {
            return {};
        }

        std::string pciStr(12, '\0');
        sprintf(pciStr.data(), "%04x:%02x:%02x.%1x", pci[0], pci[1], pci[2], pci[3]);
        return pciStr;
    }

    [[nodiscard]] std::string getAlias() const;
};

std::shared_ptr<Device> findDevice(const std::string& alias);
