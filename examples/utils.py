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


def error_callback(code: physx.PxErrorCode, message: str, file: str, line: int):
    print(message)


class PhysicsEngineCPU:
    def __init__(self):
        self.callback = physx.ErrorCallback(error_callback)
        self.foundation = physx.PxCreateFoundation(self.callback)
        self.engine = physx.PxCreatePhysics(self.foundation, physx.PxTolerancesScale())
        physx.PxInitExtensions(self.engine)

        scene_config = PhysxSceneConfig()
        scene_desc = physx.PxSceneDesc(self.engine.getTolerancesScale())
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

        self.scene = self.engine.createScene(scene_desc)

    def __del__(self):
        self.scene.release()
        self.foundation.release()


class PhysicsEngineGPU:
    def __init__(self):
        self.callback = physx.ErrorCallback(error_callback)
        self.foundation = physx.PxCreateFoundation(self.callback)
        self.engine = physx.PxCreatePhysics(self.foundation, physx.PxTolerancesScale(0.1, 0.2))
        physx.PxInitExtensions(self.engine)

        scene_config = PhysxSceneConfig()
        scene_desc = physx.PxSceneDesc(self.engine.getTolerancesScale())
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

        self.gpu = physx.findDevice("cuda")
        self.cuda_context_manager = physx.PxCreateCudaContextManager(self.foundation, self.gpu)
        scene_desc.cudaContextManager = self.cuda_context_manager
        scene_desc.broadPhaseType = physx.PxBroadPhaseType.eGPU
        self.scene = self.engine.createScene(scene_desc)

    def __del__(self):
        self.scene.release()
        self.foundation.release()
