//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <PxFEMClothMaterial.h>

#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

void bindMaterial(nb::module_& m) {
    nb::enum_<PxCombineMode::Enum>(m, "PxCombineMode")
            .value("eAVERAGE", PxCombineMode::Enum::eAVERAGE)
            .value("eMIN", PxCombineMode::Enum::eMIN)
            .value("eMULTIPLY", PxCombineMode::Enum::eMULTIPLY)
            .value("eMAX", PxCombineMode::Enum::eMAX);

    nb::enum_<PxFEMSoftBodyMaterialModel::Enum>(m, "PxFEMSoftBodyMaterialModel")
            .value("eCO_ROTATIONAL", PxFEMSoftBodyMaterialModel::Enum::eCO_ROTATIONAL)
            .value("eNEO_HOOKEAN", PxFEMSoftBodyMaterialModel::Enum::eNEO_HOOKEAN);

    nb::class_<PxBaseMaterial>(m, "PxBaseMaterial").def("isKindOf", &PxBaseMaterial::isKindOf);

    nb::class_<PxMaterial, PxBaseMaterial>(m, "PxMaterial")
            .def_prop_rw("dynamicFriction", &PxMaterial::getDynamicFriction, &PxMaterial::setDynamicFriction)
            .def_prop_rw("staticFriction", &PxMaterial::getStaticFriction, &PxMaterial::setStaticFriction)
            .def_prop_rw("restitution", &PxMaterial::getRestitution, &PxMaterial::setRestitution)
            .def_prop_rw("damping", &PxMaterial::getDamping, &PxMaterial::setDamping)
            .def_prop_rw("frictionCombineMode", &PxMaterial::getFrictionCombineMode,
                         &PxMaterial::setFrictionCombineMode)
            .def_prop_rw("restitutionCombineMode", &PxMaterial::getRestitutionCombineMode,
                         &PxMaterial::setRestitutionCombineMode)
            .def_prop_rw("dampingCombineMode", &PxMaterial::getDampingCombineMode, &PxMaterial::setDampingCombineMode);

    nb::class_<PxFEMMaterial, PxBaseMaterial>(m, "PxFEMMaterial")
            .def_prop_rw("youngsModulus", &PxFEMMaterial::getYoungsModulus, &PxFEMMaterial::setYoungsModulus)
            .def_prop_rw("poissons", &PxFEMMaterial::getPoissons, &PxFEMMaterial::setPoissons)
            .def_prop_rw("dynamicFriction", &PxFEMMaterial::getDynamicFriction, &PxFEMMaterial::setDynamicFriction);

    nb::class_<PxFEMSoftBodyMaterial, PxFEMMaterial>(m, "PxFEMSoftBodyMaterial")
            .def_prop_rw("damping", &PxFEMSoftBodyMaterial::getDamping, &PxFEMSoftBodyMaterial::setDamping)
            .def_prop_rw("dampingScale", &PxFEMSoftBodyMaterial::getDampingScale,
                         &PxFEMSoftBodyMaterial::setDampingScale)
            .def_prop_rw("materialModel", &PxFEMSoftBodyMaterial::getMaterialModel,
                         &PxFEMSoftBodyMaterial::setMaterialModel);

    nb::class_<PxFEMClothMaterial, PxFEMMaterial>(m, "PxFEMClothMaterial")
            .def_prop_rw("thickness", &PxFEMClothMaterial::getThickness, &PxFEMClothMaterial::setThickness);

    nb::class_<PxPBDMaterial, PxBaseMaterial>(m, "PxPBDMaterial")
            .def_prop_rw("friction", &PxPBDMaterial::getFriction, &PxPBDMaterial::setFriction)
            .def_prop_rw("setDamping", &PxPBDMaterial::getDamping, &PxPBDMaterial::setDamping)
            .def_prop_rw("adhesion", &PxPBDMaterial::getAdhesion, &PxPBDMaterial::setAdhesion)
            .def_prop_rw("gravityScale", &PxPBDMaterial::getGravityScale, &PxPBDMaterial::setGravityScale)
            .def_prop_rw("adhesionRadiusScale", &PxPBDMaterial::getAdhesionRadiusScale,
                         &PxPBDMaterial::setAdhesionRadiusScale)
            .def_prop_rw("viscosity", &PxPBDMaterial::getViscosity, &PxPBDMaterial::setViscosity)
            .def_prop_rw("vorticityConfinement", &PxPBDMaterial::getVorticityConfinement,
                         &PxPBDMaterial::setVorticityConfinement)
            .def_prop_rw("surfaceTension", &PxPBDMaterial::getSurfaceTension, &PxPBDMaterial::setSurfaceTension)
            .def_prop_rw("cohesion", &PxPBDMaterial::getCohesion, &PxPBDMaterial::setCohesion)
            .def_prop_rw("lift", &PxPBDMaterial::getLift, &PxPBDMaterial::setLift)
            .def_prop_rw("drag", &PxPBDMaterial::getDrag, &PxPBDMaterial::setDrag)
            .def_prop_rw("cflCoefficient", &PxPBDMaterial::getCFLCoefficient, &PxPBDMaterial::setCFLCoefficient)
            .def_prop_rw("particleFrictionScale", &PxPBDMaterial::getParticleFrictionScale,
                         &PxPBDMaterial::setParticleFrictionScale)
            .def_prop_rw("particleAdhesionScale", &PxPBDMaterial::getParticleAdhesionScale,
                         &PxPBDMaterial::setParticleAdhesionScale);
}