//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/tuple.h>

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
            .def("setSolverIterationCounts", &PxPBDParticleSystem::setSolverIterationCounts, "minPositionIters"_a,
                 "minVelocityIters"_a = 1)
            .def("getSolverIterationCounts",
                 [](PxPBDParticleSystem* body) {
                     std::tuple<PxU32, PxU32> result;
                     body->getSolverIterationCounts(std::get<0>(result), std::get<1>(result));
                     return result;
                 })
            .def_prop_rw("simulationFilterData", &PxPBDParticleSystem::getSimulationFilterData,
                         &PxPBDParticleSystem::setSimulationFilterData)
            .def("setParticleFlag", &PxPBDParticleSystem::setParticleFlag, "flag"_a, "val"_a)
            .def_prop_rw("particleFlags", &PxPBDParticleSystem::getParticleFlags,
                         &PxPBDParticleSystem::setParticleFlags)
            .def_prop_rw("maxDepenetrationVelocity", &PxPBDParticleSystem::getMaxDepenetrationVelocity,
                         &PxPBDParticleSystem::setMaxDepenetrationVelocity)
            .def_prop_rw("maxVelocity", &PxPBDParticleSystem::getMaxVelocity, &PxPBDParticleSystem::setMaxVelocity)
#ifdef SUPPORT_CUDA
            .def("getCudaContextManager", &PxPBDParticleSystem::getCudaContextManager)
#endif
            .def_prop_rw("restOffset", &PxPBDParticleSystem::getRestOffset, &PxPBDParticleSystem::setRestOffset)
            .def_prop_rw("contactOffset", &PxPBDParticleSystem::getContactOffset,
                         &PxPBDParticleSystem::setContactOffset)
            .def_prop_rw("particleContactOffset", &PxPBDParticleSystem::getParticleContactOffset,
                         &PxPBDParticleSystem::setParticleContactOffset)
            .def_prop_rw("solidRestOffset", &PxPBDParticleSystem::getSolidRestOffset,
                         &PxPBDParticleSystem::setSolidRestOffset)
            .def("addRigidAttachment", &PxPBDParticleSystem::addRigidAttachment, "actor"_a)
            .def("removeRigidAttachment", &PxPBDParticleSystem::removeRigidAttachment, "actor"_a)
            .def("enableCCD", &PxPBDParticleSystem::enableCCD, "enable"_a)
            .def("setParticleLockFlag", &PxPBDParticleSystem::setParticleLockFlag, "flag"_a, "value"_a)
            .def_prop_rw("particleLockFlags", &PxPBDParticleSystem::getParticleLockFlags,
                         &PxPBDParticleSystem::setParticleLockFlags)
            .def("createPhase", &PxPBDParticleSystem::createPhase, "material"_a, "flags"_a)
            .def("getNbParticleMaterials", &PxPBDParticleSystem::getNbParticleMaterials)
            .def("addParticleBuffer", &PxPBDParticleSystem::addParticleBuffer, "particleBuffer"_a)
            .def("removeParticleBuffer", &PxPBDParticleSystem::removeParticleBuffer, "particleBuffer"_a)
            .def("getGpuParticleSystemIndex", &PxPBDParticleSystem::getGpuParticleSystemIndex)
            .def_prop_rw("wind", &PxPBDParticleSystem::getWind, &PxPBDParticleSystem::setWind)
            .def_prop_rw("fluidBoundaryDensityScale", &PxPBDParticleSystem::getFluidBoundaryDensityScale,
                         &PxPBDParticleSystem::setFluidBoundaryDensityScale)
            .def_prop_rw("fluidRestOffset", &PxPBDParticleSystem::getFluidRestOffset,
                         &PxPBDParticleSystem::setFluidRestOffset)
            .def_prop_rw("gridSizeX", &PxPBDParticleSystem::getGridSizeX, &PxPBDParticleSystem::setGridSizeX)
            .def_prop_rw("gridSizeY", &PxPBDParticleSystem::getGridSizeY, &PxPBDParticleSystem::setGridSizeY)
            .def_prop_rw("gridSizeZ", &PxPBDParticleSystem::getGridSizeZ, &PxPBDParticleSystem::setGridSizeZ);

    nb::class_<PxParticleBuffer>(m, "PxParticleBuffer")
            .def_prop_rw("nbActiveParticles", &PxParticleBuffer::getNbActiveParticles,
                         &PxParticleBuffer::setNbActiveParticles)
            .def_prop_rw("nbParticleVolumes", &PxParticleBuffer::getNbParticleVolumes,
                         &PxParticleBuffer::setNbParticleVolumes)
            .def("getMaxParticles", &PxParticleBuffer::getMaxParticles)
            .def("getMaxParticleVolumes", &PxParticleBuffer::getMaxParticleVolumes)
            .def("getFlatListStartIndex", &PxParticleBuffer::getFlatListStartIndex)
            .def("raiseFlags", &PxParticleBuffer::raiseFlags, "flags"_a)
            .def("release", &PxParticleBuffer::release)
            .def("getUniqueId", &PxParticleBuffer::getUniqueId);

    nb::class_<PxDiffuseParticleParams>(m, "PxDiffuseParticleParams")
            .def("setToDefault", &PxDiffuseParticleParams::setToDefault)
            .def_rw("threshold", &PxDiffuseParticleParams::threshold)
            .def_rw("lifetime", &PxDiffuseParticleParams::lifetime)
            .def_rw("airDrag", &PxDiffuseParticleParams::airDrag)
            .def_rw("bubbleDrag", &PxDiffuseParticleParams::bubbleDrag)
            .def_rw("buoyancy", &PxDiffuseParticleParams::buoyancy)
            .def_rw("kineticEnergyWeight", &PxDiffuseParticleParams::kineticEnergyWeight)
            .def_rw("pressureWeight", &PxDiffuseParticleParams::pressureWeight)
            .def_rw("divergenceWeight", &PxDiffuseParticleParams::divergenceWeight)
            .def_rw("collisionDecay", &PxDiffuseParticleParams::collisionDecay)
            .def_rw("useAccurateVelocity", &PxDiffuseParticleParams::useAccurateVelocity);
    nb::class_<PxParticleAndDiffuseBuffer, PxParticleBuffer>(m, "PxParticleAndDiffuseBuffer")
            .def("setMaxActiveDiffuseParticles", &PxParticleAndDiffuseBuffer::setMaxActiveDiffuseParticles,
                 "maxActiveDiffuseParticles"_a)
            .def("getMaxDiffuseParticles", &PxParticleAndDiffuseBuffer::getMaxDiffuseParticles)
            .def_prop_rw("diffuseParticleParams", &PxParticleAndDiffuseBuffer::getDiffuseParticleParams,
                         &PxParticleAndDiffuseBuffer::setDiffuseParticleParams);

    nb::class_<PxParticleClothBuffer, PxParticleBuffer>(m, "PxParticleClothBuffer")
            .def_prop_rw("nbTriangles", &PxParticleClothBuffer::getNbTriangles, &PxParticleClothBuffer::setNbTriangles)
            .def("getNbSprings", &PxParticleClothBuffer::getNbSprings);
    nb::class_<PxParticleRigidBuffer, PxParticleBuffer>(m, "PxParticleRigidBuffer")
            .def_prop_rw("nbRigids", &PxParticleRigidBuffer::getNbRigids, &PxParticleRigidBuffer::setNbRigids);
}