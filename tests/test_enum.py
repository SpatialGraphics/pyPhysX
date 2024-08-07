#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

import pytest
import pyPhysX as physx


def test_enum():
    a = physx.PxRigidDynamicLockFlags(physx.PxRigidDynamicLockFlag.eLOCK_ANGULAR_X)
    b = physx.PxRigidDynamicLockFlags(physx.PxRigidDynamicLockFlag.eLOCK_LINEAR_Y)
    assert (a | b).value() == 10
    assert (a & b).value() == 0
