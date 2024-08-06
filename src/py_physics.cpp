//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <PxFEMClothMaterial.h>

#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

void bindPhysics(nb::module_& m) {
    nb::class_<PxTolerancesScale>(m, "PxTolerancesScale")
            .def(nb::init<float, float>(), "defaultLength"_a = 1.f, "defaultSpeed"_a = 10.f)
            .def("isValid", &PxTolerancesScale::isValid)
            .def_rw("length", &PxTolerancesScale::length)
            .def_rw("speed", &PxTolerancesScale::speed);

    nb::class_<PxPhysics>(m, "PxPhysics")
            .def("getFoundation", &PxPhysics::getFoundation)
            .def("createAggregate", &PxPhysics::createAggregate, nb::rv_policy::reference)
            .def("getTolerancesScale", &PxPhysics::getTolerancesScale, nb::rv_policy::reference)
            .def("createTriangleMesh", &PxPhysics::createTriangleMesh, nb::rv_policy::reference)
            .def("getNbTriangleMeshes", &PxPhysics::getNbTriangleMeshes)
            .def("createTetrahedronMesh", &PxPhysics::createTetrahedronMesh, nb::rv_policy::reference)
            .def("createSoftBodyMesh", &PxPhysics::createSoftBodyMesh, nb::rv_policy::reference)
            .def("getNbTetrahedronMeshes", &PxPhysics::getNbTetrahedronMeshes)
            .def("createHeightField", &PxPhysics::createHeightField, nb::rv_policy::reference)
            .def("getNbHeightFields", &PxPhysics::getNbHeightFields)
            .def("createConvexMesh", &PxPhysics::createConvexMesh, nb::rv_policy::reference)
            .def("getNbConvexMeshes", &PxPhysics::getNbConvexMeshes)
            .def("getNbBVHs", &PxPhysics::getNbBVHs)
            .def("createScene", &PxPhysics::createScene, nb::rv_policy::reference)
            .def("getNbScenes", &PxPhysics::getNbScenes)
            .def("createRigidStatic", &PxPhysics::createRigidStatic, nb::rv_policy::reference)
            .def("createRigidDynamic", &PxPhysics::createRigidDynamic, nb::rv_policy::reference)
            .def("createShape",
                 nb::overload_cast<const PxGeometry&, const PxMaterial&, bool, PxShapeFlags>(&PxPhysics::createShape),
                 nb::rv_policy::reference)
            .def("createShape",
                 nb::overload_cast<const PxGeometry&, const PxFEMSoftBodyMaterial&, bool, PxShapeFlags>(
                         &PxPhysics::createShape),
                 nb::rv_policy::reference)
            .def(
                    "createShape",
                    [](PxPhysics* physics, const PxGeometry& geometry, std::vector<PxMaterial*> materials,
                       bool isExclusive, const PxShapeFlags& shapeFlags) {
                        return physics->createShape(geometry, materials.data(), materials.size(), shapeFlags);
                    },
                    nb::rv_policy::reference)
            .def(
                    "createShape",
                    [](PxPhysics* physics, const PxGeometry& geometry, std::vector<PxFEMSoftBodyMaterial*> materials,
                       bool isExclusive, const PxShapeFlags& shapeFlags) {
                        return physics->createShape(geometry, materials.data(), materials.size(), shapeFlags);
                    },
                    nb::rv_policy::reference)
            .def(
                    "createShape",
                    [](PxPhysics* physics, const PxGeometry& geometry, std::vector<PxFEMClothMaterial*> materials,
                       bool isExclusive, const PxShapeFlags& shapeFlags) {
                        return physics->createShape(geometry, materials.data(), materials.size(), shapeFlags);
                    },
                    nb::rv_policy::reference)
            .def("getNbShapes", &PxPhysics::getNbShapes)
            .def("createConstraint", &PxPhysics::createConstraint, nb::rv_policy::reference)
            .def("createArticulationReducedCoordinate", &PxPhysics::createArticulationReducedCoordinate,
                 nb::rv_policy::reference)
            //            .def("createFEMCloth", &PxPhysics::createFEMCloth, nb::rv_policy::reference)
            //            .def("createSoftBody", &PxPhysics::createSoftBody, nb::rv_policy::reference)
            //            .def("createHairSystem", &PxPhysics::createHairSystem, nb::rv_policy::reference)
            //            .def("createPBDParticleSystem", &PxPhysics::createPBDParticleSystem, nb::rv_policy::reference)
            //            .def("createParticleBuffer", &PxPhysics::createParticleBuffer, nb::rv_policy::reference)
            //            .def("createParticleAndDiffuseBuffer", &PxPhysics::createParticleAndDiffuseBuffer,
            //            nb::rv_policy::reference) .def("createParticleClothBuffer",
            //            &PxPhysics::createParticleClothBuffer, nb::rv_policy::reference)
            //            .def("createParticleRigidBuffer", &PxPhysics::createParticleRigidBuffer,
            //            nb::rv_policy::reference)
            .def("createMaterial", &PxPhysics::createMaterial, nb::rv_policy::reference)
            .def("getNbMaterials", &PxPhysics::getNbMaterials)
            .def("createFEMSoftBodyMaterial", &PxPhysics::createFEMSoftBodyMaterial, nb::rv_policy::reference)
            .def("getNbFEMSoftBodyMaterials", &PxPhysics::getNbFEMSoftBodyMaterials)
            .def("createFEMClothMaterial", &PxPhysics::createFEMClothMaterial, nb::rv_policy::reference)
            .def("getNbFEMClothMaterials", &PxPhysics::getNbFEMClothMaterials)
            .def("createPBDMaterial", &PxPhysics::createPBDMaterial, nb::rv_policy::reference)
            .def("getNbPBDMaterials", &PxPhysics::getNbPBDMaterials);
}