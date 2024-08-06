//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <PxFEMClothMaterial.h>

#include <nanobind/nanobind.h>
#include <nanobind/stl/array.h>
#include <nanobind/stl/tuple.h>

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
            .def("setDynamicFriction", &PxMaterial::setDynamicFriction, "coef"_a)
            .def("getDynamicFriction", &PxMaterial::getDynamicFriction)
            .def("setStaticFriction", &PxMaterial::setStaticFriction, "coef"_a)
            .def("getStaticFriction", &PxMaterial::getStaticFriction)
            .def("setRestitution", &PxMaterial::setRestitution, "rest"_a)
            .def("getRestitution", &PxMaterial::getRestitution)
            .def("setDamping", &PxMaterial::setDamping, "damping"_a)
            .def("getDamping", &PxMaterial::getDamping)
            .def("setFrictionCombineMode", &PxMaterial::setFrictionCombineMode, "combMode"_a)
            .def("getFrictionCombineMode", &PxMaterial::getFrictionCombineMode)
            .def("setRestitutionCombineMode", &PxMaterial::setRestitutionCombineMode, "combMode"_a)
            .def("getRestitutionCombineMode", &PxMaterial::getRestitutionCombineMode)
            .def("setDampingCombineMode", &PxMaterial::setDampingCombineMode, "combMode"_a)
            .def("getDampingCombineMode", &PxMaterial::getDampingCombineMode);

    nb::class_<PxFEMMaterial, PxBaseMaterial>(m, "PxFEMMaterial")
            .def("setYoungsModulus", &PxFEMMaterial::setYoungsModulus)
            .def("getYoungsModulus", &PxFEMMaterial::getYoungsModulus)
            .def("setPoissons", &PxFEMMaterial::setPoissons)
            .def("getPoissons", &PxFEMMaterial::getPoissons)
            .def("setDynamicFriction", &PxFEMMaterial::setDynamicFriction)
            .def("getDynamicFriction", &PxFEMMaterial::getDynamicFriction);

    nb::class_<PxFEMSoftBodyMaterial, PxFEMMaterial>(m, "PxFEMSoftBodyMaterial")
            .def("setDamping", &PxFEMSoftBodyMaterial::setDamping)
            .def("getDamping", &PxFEMSoftBodyMaterial::getDamping)
            .def("setDampingScale", &PxFEMSoftBodyMaterial::setDampingScale)
            .def("getDampingScale", &PxFEMSoftBodyMaterial::getDampingScale)
            .def("setMaterialModel", &PxFEMSoftBodyMaterial::setMaterialModel)
            .def("getMaterialModel", &PxFEMSoftBodyMaterial::getMaterialModel);

    nb::class_<PxFEMClothMaterial, PxFEMMaterial>(m, "PxFEMClothMaterial")
            .def("setThickness", &PxFEMClothMaterial::setThickness)
            .def("getThickness", &PxFEMClothMaterial::getThickness);

    nb::class_<PxPBDMaterial, PxBaseMaterial>(m, "PxPBDMaterial")
            .def("setFriction", &PxPBDMaterial::setFriction)
            .def("getFriction", &PxPBDMaterial::getFriction)
            .def("setDamping", &PxPBDMaterial::setDamping)
            .def("getDamping", &PxPBDMaterial::getDamping)
            .def("setAdhesion", &PxPBDMaterial::setAdhesion)
            .def("getAdhesion", &PxPBDMaterial::getAdhesion)
            .def("setGravityScale", &PxPBDMaterial::setGravityScale)
            .def("getGravityScale", &PxPBDMaterial::getGravityScale)
            .def("setAdhesionRadiusScale", &PxPBDMaterial::setAdhesionRadiusScale)
            .def("getAdhesionRadiusScale", &PxPBDMaterial::getAdhesionRadiusScale)
            .def("setViscosity", &PxPBDMaterial::setViscosity)
            .def("getViscosity", &PxPBDMaterial::getViscosity)
            .def("setVorticityConfinement", &PxPBDMaterial::setVorticityConfinement)
            .def("getVorticityConfinement", &PxPBDMaterial::getVorticityConfinement)
            .def("setSurfaceTension", &PxPBDMaterial::setSurfaceTension)
            .def("getSurfaceTension", &PxPBDMaterial::getSurfaceTension)
            .def("setCohesion", &PxPBDMaterial::setCohesion)
            .def("getCohesion", &PxPBDMaterial::getCohesion)
            .def("setLift", &PxPBDMaterial::setLift)
            .def("getLift", &PxPBDMaterial::getLift)
            .def("setDrag", &PxPBDMaterial::setDrag)
            .def("getDrag", &PxPBDMaterial::getDrag)
            .def("setCFLCoefficient", &PxPBDMaterial::setCFLCoefficient)
            .def("getCFLCoefficient", &PxPBDMaterial::getCFLCoefficient)
            .def("setParticleFrictionScale", &PxPBDMaterial::setParticleFrictionScale)
            .def("getParticleFrictionScale", &PxPBDMaterial::getParticleFrictionScale)
            .def("setParticleAdhesionScale", &PxPBDMaterial::setParticleAdhesionScale)
            .def("getParticleAdhesionScale", &PxPBDMaterial::getParticleAdhesionScale);
}