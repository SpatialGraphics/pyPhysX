#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

import pyPhysX as physx
from utils import PhysxSceneConfig
import pxr


def main():
    a = pxr.UsdPhysics.MaterialAPI.GetDynamicFrictionAttr()
