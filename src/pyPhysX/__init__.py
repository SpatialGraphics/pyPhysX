from .py_physx_ext import *


def enable_gpu():
    import os
    import ctypes

    # Set the path to your DLL
    dll_path = os.path.join(os.path.dirname(__file__), 'libPhysXGpu_64.so')

    ctypes.CDLL("libcuda.so", ctypes.RTLD_GLOBAL)
    ctypes.CDLL(dll_path, ctypes.RTLD_LOCAL)
