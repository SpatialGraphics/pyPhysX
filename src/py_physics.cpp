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
            .def("createAggregate", &PxPhysics::createAggregate, "maxActor"_a, "maxShape"_a, "filterHint"_a,
                 nb::rv_policy::reference)
            .def("getTolerancesScale", &PxPhysics::getTolerancesScale, nb::rv_policy::reference)
            .def("createTriangleMesh", &PxPhysics::createTriangleMesh, "stream"_a, nb::rv_policy::reference)
            .def("getNbTriangleMeshes", &PxPhysics::getNbTriangleMeshes)
            .def("createTetrahedronMesh", &PxPhysics::createTetrahedronMesh, "stream"_a, nb::rv_policy::reference)
            .def("createSoftBodyMesh", &PxPhysics::createSoftBodyMesh, "stream"_a, nb::rv_policy::reference)
            .def("getNbTetrahedronMeshes", &PxPhysics::getNbTetrahedronMeshes)
            .def("createHeightField", &PxPhysics::createHeightField, "stream"_a, nb::rv_policy::reference)
            .def("getNbHeightFields", &PxPhysics::getNbHeightFields)
            .def("createConvexMesh", &PxPhysics::createConvexMesh, "stream"_a, nb::rv_policy::reference)
            .def("getNbConvexMeshes", &PxPhysics::getNbConvexMeshes)
            .def("getNbBVHs", &PxPhysics::getNbBVHs)
            .def("createScene", &PxPhysics::createScene, "sceneDesc"_a, nb::rv_policy::reference)
            .def("getNbScenes", &PxPhysics::getNbScenes)
            .def("createRigidStatic", &PxPhysics::createRigidStatic, "pose"_a, nb::rv_policy::reference)
            .def("createRigidDynamic", &PxPhysics::createRigidDynamic, "pose"_a, nb::rv_policy::reference)
            .def("createShape",
                 nb::overload_cast<const PxGeometry&, const PxMaterial&, bool, PxShapeFlags>(&PxPhysics::createShape),
                 "geometry"_a, "material"_a, "isExclusive"_a = false,
                 "shapeFlags"_a =
                         PxShapeFlag::eVISUALIZATION | PxShapeFlag::eSCENE_QUERY_SHAPE | PxShapeFlag::eSIMULATION_SHAPE,
                 nb::rv_policy::reference)
            .def("createShape",
                 nb::overload_cast<const PxGeometry&, const PxFEMSoftBodyMaterial&, bool, PxShapeFlags>(
                         &PxPhysics::createShape),
                 "geometry"_a, "material"_a, "isExclusive"_a = false,
                 "shapeFlags"_a =
                         PxShapeFlag::eVISUALIZATION | PxShapeFlag::eSCENE_QUERY_SHAPE | PxShapeFlag::eSIMULATION_SHAPE,
                 nb::rv_policy::reference)
            .def(
                    "createShape",
                    [](PxPhysics* physics, const PxGeometry& geometry, std::vector<PxMaterial*> materials,
                       bool isExclusive, const PxShapeFlags& shapeFlags) {
                        return physics->createShape(geometry, materials.data(), materials.size(), shapeFlags);
                    },
                    "geometry"_a, "materials"_a, "isExclusive"_a = false,
                    "shapeFlags"_a = PxShapeFlag::eVISUALIZATION | PxShapeFlag::eSCENE_QUERY_SHAPE |
                                     PxShapeFlag::eSIMULATION_SHAPE,
                    nb::rv_policy::reference)
            .def(
                    "createShape",
                    [](PxPhysics* physics, const PxGeometry& geometry, std::vector<PxFEMSoftBodyMaterial*> materials,
                       bool isExclusive, const PxShapeFlags& shapeFlags) {
                        return physics->createShape(geometry, materials.data(), materials.size(), shapeFlags);
                    },
                    "geometry"_a, "materials"_a, "isExclusive"_a = false,
                    "shapeFlags"_a = PxShapeFlag::eVISUALIZATION | PxShapeFlag::eSCENE_QUERY_SHAPE |
                                     PxShapeFlag::eSIMULATION_SHAPE,
                    nb::rv_policy::reference)
            .def(
                    "createShape",
                    [](PxPhysics* physics, const PxGeometry& geometry, std::vector<PxFEMClothMaterial*> materials,
                       bool isExclusive, const PxShapeFlags& shapeFlags) {
                        return physics->createShape(geometry, materials.data(), materials.size(), shapeFlags);
                    },
                    "geometry"_a, "materials"_a, "isExclusive"_a = false,
                    "shapeFlags"_a = PxShapeFlag::eVISUALIZATION | PxShapeFlag::eSCENE_QUERY_SHAPE |
                                     PxShapeFlag::eSIMULATION_SHAPE,
                    nb::rv_policy::reference)
            .def("getNbShapes", &PxPhysics::getNbShapes)
            //            .def("createConstraint", &PxPhysics::createConstraint, nb::rv_policy::reference)
            .def("createArticulationReducedCoordinate", &PxPhysics::createArticulationReducedCoordinate,
                 nb::rv_policy::reference)
#ifdef SUPPORT_CUDA
            //            .def("createFEMCloth", &PxPhysics::createFEMCloth, nb::rv_policy::reference)
            .def("createSoftBody", &PxPhysics::createSoftBody, "cudaContextManager"_a, nb::rv_policy::reference)
            //            .def("createHairSystem", &PxPhysics::createHairSystem, nb::rv_policy::reference)
            .def("createPBDParticleSystem", &PxPhysics::createPBDParticleSystem, "cudaContextManager"_a,
                 "maxNeighborhood"_a = 96, "neighborhoodScale"_a = 1.01f, nb::rv_policy::reference)
            .def("createParticleBuffer", &PxPhysics::createParticleBuffer, "maxParticles"_a, "maxVolumes"_a,
                 "cudaContextManager"_a, nb::rv_policy::reference)
            .def("createParticleAndDiffuseBuffer", &PxPhysics::createParticleAndDiffuseBuffer, "maxParticles"_a,
                 "maxVolumes"_a, "maxDiffuseParticles"_a, "cudaContextManager"_a, nb::rv_policy::reference)
            .def("createParticleClothBuffer", &PxPhysics::createParticleClothBuffer, "maxParticles"_a,
                 "maxNumVolumes"_a, "maxNumCloths"_a, "maxNumTriangles"_a, "maxNumSprings"_a, "cudaContextManager"_a,
                 nb::rv_policy::reference)
            .def("createParticleRigidBuffer", &PxPhysics::createParticleRigidBuffer, "maxParticles"_a,
                 "maxNumVolumes"_a, "maxNumRigids"_a, "cudaContextManager"_a, nb::rv_policy::reference)
#endif
            .def("createMaterial", &PxPhysics::createMaterial, "staticFriction"_a, "dynamicFriction"_a, "restitution"_a,
                 nb::rv_policy::reference)
            .def("getNbMaterials", &PxPhysics::getNbMaterials)
            .def("createFEMSoftBodyMaterial", &PxPhysics::createFEMSoftBodyMaterial, "youngs"_a, "poissons"_a,
                 "dynamicFriction"_a, nb::rv_policy::reference)
            .def("getNbFEMSoftBodyMaterials", &PxPhysics::getNbFEMSoftBodyMaterials)
            .def("createFEMClothMaterial", &PxPhysics::createFEMClothMaterial, "youngs"_a, "poissons"_a,
                 "dynamicFriction"_a, "thickness"_a = 0.001f, nb::rv_policy::reference)
            .def("getNbFEMClothMaterials", &PxPhysics::getNbFEMClothMaterials)
            .def("createPBDMaterial", &PxPhysics::createPBDMaterial, "friction"_a, "damping"_a, "adhesion"_a,
                 "viscosity"_a, "vorticityConfinement"_a, "surfaceTension"_a, "cohesion"_a, "lift"_a, "drag"_a,
                 "cflCoefficient"_a = 1.f, "gravityScale"_a = 1.f, nb::rv_policy::reference)
            .def("getNbPBDMaterials", &PxPhysics::getNbPBDMaterials);
}