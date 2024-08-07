//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>

#include "py_utils.h"

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

void bindParticle(nb::module_& m) {
    nb::enum_<PxParticlePhaseFlag::Enum>(m, "PxParticlePhaseFlag")
            .value("eParticlePhaseGroupMask", PxParticlePhaseFlag::Enum::eParticlePhaseGroupMask)
            .value("eParticlePhaseFlagsMask", PxParticlePhaseFlag::Enum::eParticlePhaseFlagsMask)
            .value("eParticlePhaseSelfCollide", PxParticlePhaseFlag::Enum::eParticlePhaseSelfCollide)
            .value("eParticlePhaseSelfCollideFilter", PxParticlePhaseFlag::Enum::eParticlePhaseSelfCollideFilter)
            .value("eParticlePhaseFluid", PxParticlePhaseFlag::Enum::eParticlePhaseFluid);
    bindFlags<PxParticlePhaseFlag::Enum, PxU32>(m, "PxParticlePhaseFlags");

    nb::enum_<PxParticleFlag::Enum>(m, "PxParticleFlag")
            .value("eDISABLE_SELF_COLLISION", PxParticleFlag::Enum::eDISABLE_SELF_COLLISION)
            .value("eDISABLE_RIGID_COLLISION", PxParticleFlag::Enum::eDISABLE_RIGID_COLLISION)
            .value("eFULL_DIFFUSE_ADVECTION", PxParticleFlag::Enum::eFULL_DIFFUSE_ADVECTION)
            .value("eENABLE_SPECULATIVE_CCD", PxParticleFlag::Enum::eENABLE_SPECULATIVE_CCD);
    bindFlags<PxParticleFlag::Enum, PxU32>(m, "PxParticleFlags");

    nb::enum_<PxParticleLockFlag::Enum>(m, "PxParticleLockFlag")
            .value("eLOCK_X", PxParticleLockFlag::Enum::eLOCK_X)
            .value("eLOCK_Y", PxParticleLockFlag::Enum::eLOCK_Y)
            .value("eLOCK_Z", PxParticleLockFlag::Enum::eLOCK_Z);
    bindFlags<PxParticleLockFlag::Enum, PxU8>(m, "PxParticleLockFlags");

    nb::enum_<PxParticleBufferFlag::Enum>(m, "PxParticleBufferFlag")
            .value("eNONE", PxParticleBufferFlag::Enum::eNONE)
            .value("eUPDATE_POSITION", PxParticleBufferFlag::Enum::eUPDATE_POSITION)
            .value("eUPDATE_VELOCITY", PxParticleBufferFlag::Enum::eUPDATE_VELOCITY)
            .value("eUPDATE_PHASE", PxParticleBufferFlag::Enum::eUPDATE_PHASE)
            .value("eUPDATE_RESTPOSITION", PxParticleBufferFlag::Enum::eUPDATE_RESTPOSITION)
            .value("eUPDATE_CLOTH", PxParticleBufferFlag::Enum::eUPDATE_CLOTH)
            .value("eUPDATE_RIGID", PxParticleBufferFlag::Enum::eUPDATE_RIGID)
            .value("eUPDATE_DIFFUSE_PARAM", PxParticleBufferFlag::Enum::eUPDATE_DIFFUSE_PARAM)
            .value("eUPDATE_ATTACHMENTS", PxParticleBufferFlag::Enum::eUPDATE_ATTACHMENTS)
            .value("eALL", PxParticleBufferFlag::Enum::eALL);
    bindFlags<PxParticleBufferFlag::Enum, PxU32>(m, "PxParticleBufferFlags");

    nb::class_<PxPBDParticleSystem, PxActor>(m, "PxPBDParticleSystem")
            .def("setSolverIterationCounts", &PxPBDParticleSystem::setSolverIterationCounts)
            .def("getSolverIterationCounts", &PxPBDParticleSystem::getSolverIterationCounts)
            .def("getSimulationFilterData", &PxPBDParticleSystem::getSimulationFilterData)
            .def("setSimulationFilterData", &PxPBDParticleSystem::setSimulationFilterData)
            .def("setParticleFlag", &PxPBDParticleSystem::setParticleFlag)
            .def("setParticleFlags", &PxPBDParticleSystem::setParticleFlags)
            .def("getParticleFlags", &PxPBDParticleSystem::getParticleFlags)
            .def("setMaxDepenetrationVelocity", &PxPBDParticleSystem::setMaxDepenetrationVelocity)
            .def("getMaxDepenetrationVelocity", &PxPBDParticleSystem::getMaxDepenetrationVelocity)
            .def("setMaxVelocity", &PxPBDParticleSystem::setMaxVelocity)
            .def("getMaxVelocity", &PxPBDParticleSystem::getMaxVelocity)
#ifdef SUPPORT_CUDA
            .def("getCudaContextManager", &PxPBDParticleSystem::getCudaContextManager)
#endif
            .def("setRestOffset", &PxPBDParticleSystem::setRestOffset)
            .def("getRestOffset", &PxPBDParticleSystem::getRestOffset)
            .def("setContactOffset", &PxPBDParticleSystem::setContactOffset)
            .def("getContactOffset", &PxPBDParticleSystem::getContactOffset)
            .def("setParticleContactOffset", &PxPBDParticleSystem::setParticleContactOffset)
            .def("getParticleContactOffset", &PxPBDParticleSystem::getParticleContactOffset)
            .def("setSolidRestOffset", &PxPBDParticleSystem::setSolidRestOffset)
            .def("getSolidRestOffset", &PxPBDParticleSystem::getSolidRestOffset)
            .def("addRigidAttachment", &PxPBDParticleSystem::addRigidAttachment)
            .def("removeRigidAttachment", &PxPBDParticleSystem::removeRigidAttachment)
            .def("enableCCD", &PxPBDParticleSystem::enableCCD)
            .def("setParticleLockFlag", &PxPBDParticleSystem::setParticleLockFlag)
            .def("setParticleLockFlags", &PxPBDParticleSystem::setParticleLockFlags)
            .def("getParticleLockFlags", &PxPBDParticleSystem::getParticleLockFlags)
            .def("createPhase", &PxPBDParticleSystem::createPhase)
            .def("getNbParticleMaterials", &PxPBDParticleSystem::getNbParticleMaterials)
            .def("addParticleBuffer", &PxPBDParticleSystem::addParticleBuffer)
            .def("removeParticleBuffer", &PxPBDParticleSystem::removeParticleBuffer)
            .def("getGpuParticleSystemIndex", &PxPBDParticleSystem::getGpuParticleSystemIndex)
            .def("setWind", &PxPBDParticleSystem::setWind)
            .def("getWind", &PxPBDParticleSystem::getWind)
            .def("setFluidBoundaryDensityScale", &PxPBDParticleSystem::setFluidBoundaryDensityScale)
            .def("getFluidBoundaryDensityScale", &PxPBDParticleSystem::getFluidBoundaryDensityScale)
            .def("setFluidRestOffset", &PxPBDParticleSystem::setFluidRestOffset)
            .def("getFluidRestOffset", &PxPBDParticleSystem::getFluidRestOffset)
            .def("setGridSizeX", &PxPBDParticleSystem::setGridSizeX)
            .def("getGridSizeX", &PxPBDParticleSystem::getGridSizeX)
            .def("setGridSizeY", &PxPBDParticleSystem::setGridSizeY)
            .def("getGridSizeY", &PxPBDParticleSystem::getGridSizeY)
            .def("setGridSizeZ", &PxPBDParticleSystem::setGridSizeZ)
            .def("getGridSizeZ", &PxPBDParticleSystem::getGridSizeZ);

    nb::class_<PxParticleBuffer>(m, "PxParticleBuffer")
            .def("setNbActiveParticles", &PxParticleBuffer::setNbActiveParticles)
            .def("getNbActiveParticles", &PxParticleBuffer::getNbActiveParticles)
            .def("getMaxParticles", &PxParticleBuffer::getMaxParticles)
            .def("getNbParticleVolumes", &PxParticleBuffer::getNbParticleVolumes)
            .def("setNbParticleVolumes", &PxParticleBuffer::setNbParticleVolumes)
            .def("getMaxParticleVolumes", &PxParticleBuffer::getMaxParticleVolumes)
            .def("getFlatListStartIndex", &PxParticleBuffer::getFlatListStartIndex)
            .def("raiseFlags", &PxParticleBuffer::raiseFlags)
            .def("release", &PxParticleBuffer::release)
            .def("getUniqueId", &PxParticleBuffer::getUniqueId);
}