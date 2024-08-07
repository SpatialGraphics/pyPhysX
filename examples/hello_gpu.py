#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

import pyPhysX as physx
from utils import PhysxSceneConfig


def main():
    def error_callback(code: physx.PxErrorCode, message: str, file: str, line: int):
        print(message)

    foundation = physx.PxCreateFoundation(physx.ErrorCallback(error_callback))
    engine = physx.PxCreatePhysics(foundation, physx.PxTolerancesScale())
    physx.PxInitExtensions(engine)

    scene_config = PhysxSceneConfig()
    scene_desc = physx.PxSceneDesc(engine.getTolerancesScale())
    scene_desc.gravity = scene_config.gravity
    scene_desc.setFilterShaderGPU()
    scene_desc.solverType = physx.PxSolverType.eTGS if scene_config.enableTGS else physx.PxSolverType.ePGS
    scene_desc.bounceThresholdVelocity = scene_config.bounceThreshold
    scene_desc.gpuDynamicsConfig = physx.PxGpuDynamicsMemoryConfig()

    scene_flags = physx.PxSceneFlags()
    if scene_config.enableEnhancedDeterminism:
        scene_flags |= physx.PxSceneFlag.eENABLE_ENHANCED_DETERMINISM
    if scene_config.enablePCM:
        scene_flags |= physx.PxSceneFlag.eENABLE_PCM
    if scene_config.enableCCD:
        scene_flags |= physx.PxSceneFlag.eENABLE_CCD
    if scene_config.enableFrictionEveryIteration:
        scene_flags |= physx.PxSceneFlag.eENABLE_FRICTION_EVERY_ITERATION
    scene_flags |= physx.PxSceneFlag.eENABLE_GPU_DYNAMICS
    scene_flags |= physx.PxSceneFlag.eENABLE_DIRECT_GPU_API
    if not scene_config.enablePCM:
        scene_flags |= physx.PxSceneFlag.eENABLE_PCM
    scene_desc.flags = scene_flags
    scene_desc.cpuDispatcher = physx.PxDefaultCpuDispatcherCreate(scene_config.cpuWorkers)
    # scene_desc.cudaContextManager = mEngine->getCudaContextManager(device->cudaId)
    # scene = engine.createScene(scene_desc)

    gpu = physx.findDevice("cuda")
    cuda_context_manager = physx.PxCreateCudaContextManager(foundation, gpu)


if __name__ == '__main__':
    main()
