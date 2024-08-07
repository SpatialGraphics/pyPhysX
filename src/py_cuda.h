//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#pragma once

#include <cuda.h>

#define checkCudaErrors(call)                                                                \
    do {                                                                                     \
        cudaError_t err = call;                                                              \
        if (err != cudaSuccess) {                                                            \
            throw std::runtime_error("CUDA error: " + std::string(cudaGetErrorString(err))); \
        }                                                                                    \
    } while (0)

#define checkCudaDriverErrors(call)                  \
    do {                                             \
        CUresult err = call;                         \
        if (err != CUDA_SUCCESS) {                   \
            throw std::runtime_error("CUDA failed"); \
        }                                            \
    } while (0)

struct CudaLib {
    static CudaLib& Get();
    CudaLib();
    void* libcuda{};

    decltype(::cuCtxGetCurrent)* cuCtxGetCurrent{};
};