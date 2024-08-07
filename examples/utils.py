#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

import pyPhysX as physx


class PhysxSceneConfig:
    gravity = physx.PxVec3(0, 0, -9.81)  # default gravity
    bounceThreshold = 2.0  # relative velocity below this will not bounce
    enablePCM = True  # Use persistent contact manifold solver for contact
    enableTGS = True  # use TGS solver
    enableCCD = False  # use continuous collision detection
    enableEnhancedDeterminism = False  # improve determinism
    enableFrictionEveryIteration = True  # better friction calculation, recommended for robotics
    cpuWorkers = 0  # CPU workers, 0 for using main thread
