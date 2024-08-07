//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#pragma once

#include <cuda.h>

struct CudaLib {
    static CudaLib& Get();
    CudaLib();
    void* libcuda{};

    decltype(::cuCtxGetCurrent)* cuCtxGetCurrent{};
};