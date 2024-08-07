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


def main():
    def error_callback(code: physx.PxErrorCode, message: str, file: str, line: int):
        print(message)

    foundation = physx.PxCreateFoundation(physx.ErrorCallback(error_callback))
    engine = physx.PxCreatePhysics(foundation, physx.PxTolerancesScale())
    physx.PxInitExtensions(engine)

    scene_config = PhysxSceneConfig()
    scene_desc = physx.PxSceneDesc(engine.getTolerancesScale())
    scene_desc.gravity = scene_config.gravity
    scene_desc.setFilterShaderCPU()
    scene_desc.solverType = physx.PxSolverType.eTGS if scene_config.enableTGS else physx.PxSolverType.ePGS
    scene_desc.bounceThresholdVelocity = scene_config.bounceThreshold

    scene_flags = physx.PxSceneFlags()
    if scene_config.enableEnhancedDeterminism:
        scene_flags |= physx.PxSceneFlag.eENABLE_ENHANCED_DETERMINISM
    if scene_config.enablePCM:
        scene_flags |= physx.PxSceneFlag.eENABLE_PCM
    if scene_config.enableCCD:
        scene_flags |= physx.PxSceneFlag.eENABLE_CCD
    if scene_config.enableFrictionEveryIteration:
        scene_flags |= physx.PxSceneFlag.eENABLE_FRICTION_EVERY_ITERATION
    scene_desc.flags = scene_flags
    scene_desc.cpuDispatcher = physx.PxDefaultCpuDispatcherCreate(scene_config.cpuWorkers)

    scene = engine.createScene(scene_desc)


if __name__ == '__main__':
    main()