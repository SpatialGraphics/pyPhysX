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
    nb::class_<PxPhysics>(m, "PxPhysics")
            .def("getFoundation", &PxPhysics::getFoundation)
            .def("createAggregate", &PxPhysics::createAggregate)
            .def("getTolerancesScale", &PxPhysics::getTolerancesScale)
            .def("createTriangleMesh", &PxPhysics::createTriangleMesh)
            .def("getNbTriangleMeshes", &PxPhysics::getNbTriangleMeshes)
            .def("createTetrahedronMesh", &PxPhysics::createTetrahedronMesh)
            .def("createSoftBodyMesh", &PxPhysics::createSoftBodyMesh)
            .def("getNbTetrahedronMeshes", &PxPhysics::getNbTetrahedronMeshes)
            .def("createHeightField", &PxPhysics::createHeightField)
            .def("getNbHeightFields", &PxPhysics::getNbHeightFields)
            .def("createConvexMesh", &PxPhysics::createConvexMesh)
            .def("getNbConvexMeshes", &PxPhysics::getNbConvexMeshes)
            .def("getNbBVHs", &PxPhysics::getNbBVHs)
            .def("createScene", &PxPhysics::createScene)
            .def("getNbScenes", &PxPhysics::getNbScenes)
            .def("createRigidStatic", &PxPhysics::createRigidStatic)
            .def("createRigidDynamic", &PxPhysics::createRigidDynamic)
            .def("createShape",
                 nb::overload_cast<const PxGeometry&, const PxMaterial&, bool, PxShapeFlags>(&PxPhysics::createShape))
            .def("createShape", nb::overload_cast<const PxGeometry&, const PxFEMSoftBodyMaterial&, bool, PxShapeFlags>(
                                        &PxPhysics::createShape))
            .def("createShape",
                 [](PxPhysics* physics, const PxGeometry& geometry, std::vector<PxMaterial*> materials,
                    bool isExclusive, const PxShapeFlags& shapeFlags) {
                     return physics->createShape(geometry, materials.data(), materials.size(), shapeFlags);
                 })
            .def("createShape",
                 [](PxPhysics* physics, const PxGeometry& geometry, std::vector<PxFEMSoftBodyMaterial*> materials,
                    bool isExclusive, const PxShapeFlags& shapeFlags) {
                     return physics->createShape(geometry, materials.data(), materials.size(), shapeFlags);
                 })
            .def("createShape",
                 [](PxPhysics* physics, const PxGeometry& geometry, std::vector<PxFEMClothMaterial*> materials,
                    bool isExclusive, const PxShapeFlags& shapeFlags) {
                     return physics->createShape(geometry, materials.data(), materials.size(), shapeFlags);
                 })
            .def("getNbShapes", &PxPhysics::getNbShapes)
            .def("createConstraint", &PxPhysics::createConstraint)
            .def("createArticulationReducedCoordinate", &PxPhysics::createArticulationReducedCoordinate)
            //            .def("createFEMCloth", &PxPhysics::createFEMCloth)
            //            .def("createSoftBody", &PxPhysics::createSoftBody)
            //            .def("createHairSystem", &PxPhysics::createHairSystem)
            //            .def("createPBDParticleSystem", &PxPhysics::createPBDParticleSystem)
            //            .def("createParticleBuffer", &PxPhysics::createParticleBuffer)
            //            .def("createParticleAndDiffuseBuffer", &PxPhysics::createParticleAndDiffuseBuffer)
            //            .def("createParticleClothBuffer", &PxPhysics::createParticleClothBuffer)
            //            .def("createParticleRigidBuffer", &PxPhysics::createParticleRigidBuffer)
            .def("createMaterial", &PxPhysics::createMaterial)
            .def("getNbMaterials", &PxPhysics::getNbMaterials)
            .def("createFEMSoftBodyMaterial", &PxPhysics::createFEMSoftBodyMaterial)
            .def("getNbFEMSoftBodyMaterials", &PxPhysics::getNbFEMSoftBodyMaterials)
            .def("createFEMClothMaterial", &PxPhysics::createFEMClothMaterial)
            .def("getNbFEMClothMaterials", &PxPhysics::getNbFEMClothMaterials)
            .def("createPBDMaterial", &PxPhysics::createPBDMaterial)
            .def("getNbPBDMaterials", &PxPhysics::getNbPBDMaterials);
}