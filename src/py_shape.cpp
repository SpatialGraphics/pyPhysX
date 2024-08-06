//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

void bindShape(nb::module_& m) {
    nb::enum_<PxGeometryType::Enum>(m, "PxGeometryType")
            .value("eSPHERE", PxGeometryType::Enum::eSPHERE)
            .value("ePLANE", PxGeometryType::Enum::ePLANE)
            .value("eCAPSULE", PxGeometryType::Enum::eCAPSULE)
            .value("eBOX", PxGeometryType::Enum::eBOX)
            .value("eCONVEXMESH", PxGeometryType::Enum::eCONVEXMESH)
            .value("ePARTICLESYSTEM", PxGeometryType::Enum::ePARTICLESYSTEM)
            .value("eTETRAHEDRONMESH", PxGeometryType::Enum::eTETRAHEDRONMESH)
            .value("eTRIANGLEMESH", PxGeometryType::Enum::eTRIANGLEMESH)
            .value("eHEIGHTFIELD", PxGeometryType::Enum::eHEIGHTFIELD)
            .value("eHAIRSYSTEM", PxGeometryType::Enum::eHAIRSYSTEM)
            .value("eCUSTOM", PxGeometryType::Enum::eCUSTOM);

    nb::enum_<PxShapeFlag::Enum>(m, "PxShapeFlag")
            .value("eSIMULATION_SHAPE", PxShapeFlag::Enum::eSIMULATION_SHAPE)
            .value("eSCENE_QUERY_SHAPE", PxShapeFlag::Enum::eSCENE_QUERY_SHAPE)
            .value("eTRIGGER_SHAPE", PxShapeFlag::Enum::eTRIGGER_SHAPE)
            .value("eVISUALIZATION", PxShapeFlag::Enum::eVISUALIZATION);

    nb::class_<PxShape>(m, "PxShape")
            .def("release", &PxShape::release)
            .def("setGeometry", &PxShape::setGeometry)
            .def("getGeometry", &PxShape::getGeometry)
            .def("getActor", &PxShape::getActor)
            .def("setLocalPose", &PxShape::setLocalPose)
            .def("getLocalPose", &PxShape::getLocalPose)
            .def("setSimulationFilterData", &PxShape::setSimulationFilterData)
            .def("getSimulationFilterData", &PxShape::getSimulationFilterData)
            .def("setQueryFilterData", &PxShape::setQueryFilterData)
            .def("getQueryFilterData", &PxShape::getQueryFilterData)
            //            .def("setMaterials", &PxShape::setMaterials)
            //            .def("setSoftBodyMaterials", &PxShape::setSoftBodyMaterials)
            //            .def("setClothMaterials", &PxShape::setClothMaterials)
            .def("getNbMaterials", &PxShape::getNbMaterials)
            .def("setContactOffset", &PxShape::setContactOffset)
            .def("getContactOffset", &PxShape::getContactOffset)
            .def("setRestOffset", &PxShape::setRestOffset)
            .def("getRestOffset", &PxShape::getRestOffset)
            .def("setDensityForFluid", &PxShape::setDensityForFluid)
            .def("getDensityForFluid", &PxShape::getDensityForFluid)
            .def("setTorsionalPatchRadius", &PxShape::setTorsionalPatchRadius)
            .def("getTorsionalPatchRadius", &PxShape::getTorsionalPatchRadius)
            .def("setMinTorsionalPatchRadius", &PxShape::setMinTorsionalPatchRadius)
            .def("getMinTorsionalPatchRadius", &PxShape::getMinTorsionalPatchRadius)
            .def("getGPUIndex", &PxShape::getGPUIndex)
            .def("setFlag", &PxShape::setFlag)
            .def("setFlags", &PxShape::setFlags)
            .def("getFlags", &PxShape::getFlags)
            .def("isExclusive", &PxShape::isExclusive)
            .def("setName", &PxShape::setName)
            .def("getName", &PxShape::getName);

    nb::class_<PxGeometry>(m, "PxGeometry").def("getType", &PxGeometry::getType);

    nb::class_<PxBoxGeometry, PxGeometry>(m, "PxBoxGeometry")
            .def(nb::init<PxReal, PxReal, PxReal>())
            .def(nb::init<PxVec3>())
            .def("isValid", &PxBoxGeometry::isValid)
            .def_rw("halfExtents", &PxBoxGeometry::halfExtents);

    nb::class_<PxSphereGeometry, PxGeometry>(m, "PxSphereGeometry")
            .def(nb::init<PxReal>())
            .def("isValid", &PxSphereGeometry::isValid)
            .def_rw("radius", &PxSphereGeometry::radius);

    nb::class_<PxCapsuleGeometry, PxGeometry>(m, "PxCapsuleGeometry")
            .def(nb::init<PxReal, PxReal>())
            .def("isValid", &PxCapsuleGeometry::isValid)
            .def_rw("radius", &PxCapsuleGeometry::radius)
            .def_rw("halfHeight", &PxCapsuleGeometry::halfHeight);

    nb::class_<PxPlaneGeometry, PxGeometry>(m, "PxPlaneGeometry")
            .def(nb::init<>())
            .def("isValid", &PxPlaneGeometry::isValid);

    nb::class_<PxTriangleMeshGeometry, PxGeometry>(m, "PxTriangleMeshGeometry")
            .def(nb::init<PxTriangleMesh*, const PxMeshScale&, PxMeshGeometryFlags>())
            .def("isValid", &PxTriangleMeshGeometry::isValid);

    nb::class_<PxTetrahedronMeshGeometry, PxGeometry>(m, "PxTetrahedronMeshGeometry")
            .def(nb::init<PxTetrahedronMesh*>())
            .def("isValid", &PxTetrahedronMeshGeometry::isValid);

    nb::class_<PxHairSystemGeometry, PxGeometry>(m, "PxHairSystemGeometry")
            .def(nb::init<>())
            .def("isValid", &PxHairSystemGeometry::isValid);

    nb::class_<PxParticleSystemGeometry, PxGeometry>(m, "PxParticleSystemGeometry")
            .def(nb::init<>())
            .def("isValid", &PxParticleSystemGeometry::isValid);
}