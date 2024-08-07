//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <PxSDFBuilder.h>
#include <geomutils/include/GuCooking.h>
#include <nanobind/nanobind.h>

#include "py_utils.h"

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

void bindCooking(nb::module_& m) {
    nb::class_<PxStridedData> pxStridedData(m, "PxStridedData");
    nb::class_<PxBoundedData, PxStridedData>(m, "PxBoundedData")
            .def(nb::init<>())
            .def_rw("count", &PxBoundedData::count);

    nb::enum_<PxMeshPreprocessingFlag::Enum>(m, "PxMeshPreprocessingFlag")
            .value("eWELD_VERTICES", PxMeshPreprocessingFlag::Enum::eWELD_VERTICES)
            .value("eDISABLE_CLEAN_MESH", PxMeshPreprocessingFlag::Enum::eDISABLE_CLEAN_MESH)
            .value("eDISABLE_ACTIVE_EDGES_PRECOMPUTE", PxMeshPreprocessingFlag::Enum::eDISABLE_ACTIVE_EDGES_PRECOMPUTE)
            .value("eFORCE_32BIT_INDICES", PxMeshPreprocessingFlag::Enum::eFORCE_32BIT_INDICES)
            .value("eENABLE_VERT_MAPPING", PxMeshPreprocessingFlag::Enum::eENABLE_VERT_MAPPING)
            .value("eENABLE_INERTIA", PxMeshPreprocessingFlag::Enum::eENABLE_INERTIA);
    bindFlags<PxMeshPreprocessingFlag::Enum, PxU32>(m, "PxMeshPreprocessingFlags");
    nb::class_<PxCookingParams>(m, "PxCookingParams")
            .def(nb::init<PxTolerancesScale>())
            .def_rw("areaTestEpsilon", &PxCookingParams::areaTestEpsilon)
            .def_rw("planeTolerance", &PxCookingParams::planeTolerance)
            .def_rw("convexMeshCookingType", &PxCookingParams::convexMeshCookingType)
            .def_rw("suppressTriangleMeshRemapTable", &PxCookingParams::suppressTriangleMeshRemapTable)
            .def_rw("buildTriangleAdjacencies", &PxCookingParams::buildTriangleAdjacencies)
            .def_rw("buildGPUData", &PxCookingParams::buildGPUData)
            .def_rw("scale", &PxCookingParams::scale)
            .def_rw("meshPreprocessParams", &PxCookingParams::meshPreprocessParams)
            .def_rw("meshWeldTolerance", &PxCookingParams::meshWeldTolerance)
            .def_rw("meshAreaMinLimit", &PxCookingParams::meshAreaMinLimit)
            .def_rw("meshEdgeLengthMaxLimit", &PxCookingParams::meshEdgeLengthMaxLimit)
            .def_rw("midphaseDesc", &PxCookingParams::midphaseDesc)
            .def_rw("gaussMapLimit", &PxCookingParams::gaussMapLimit)
            .def_rw("maxWeightRatioInTet", &PxCookingParams::maxWeightRatioInTet);

    nb::enum_<PxConvexMeshCookingType::Enum>(m, "PxConvexMeshCookingType")
            .value("eQUICKHULL", PxConvexMeshCookingType::Enum::eQUICKHULL);
    nb::enum_<PxConvexMeshCookingResult::Enum>(m, "PxConvexMeshCookingResult")
            .value("eSUCCESS", PxConvexMeshCookingResult::Enum::eSUCCESS)
            .value("eZERO_AREA_TEST_FAILED", PxConvexMeshCookingResult::Enum::eZERO_AREA_TEST_FAILED)
            .value("ePOLYGONS_LIMIT_REACHED", PxConvexMeshCookingResult::Enum::ePOLYGONS_LIMIT_REACHED)
            .value("eFAILURE", PxConvexMeshCookingResult::Enum::eFAILURE)
            .value("eNON_GPU_COMPATIBLE", PxConvexMeshCookingResult::Enum::eNON_GPU_COMPATIBLE);
    nb::enum_<PxConvexFlag::Enum>(m, "PxConvexFlag")
            .value("e16_BIT_INDICES", PxConvexFlag::Enum::e16_BIT_INDICES)
            .value("eCOMPUTE_CONVEX", PxConvexFlag::Enum::eCOMPUTE_CONVEX)
            .value("eCHECK_ZERO_AREA_TRIANGLES", PxConvexFlag::Enum::eCHECK_ZERO_AREA_TRIANGLES)
            .value("eQUANTIZE_INPUT", PxConvexFlag::Enum::eQUANTIZE_INPUT)
            .value("eDISABLE_MESH_VALIDATION", PxConvexFlag::Enum::eDISABLE_MESH_VALIDATION)
            .value("ePLANE_SHIFTING", PxConvexFlag::Enum::ePLANE_SHIFTING)
            .value("eFAST_INERTIA_COMPUTATION", PxConvexFlag::Enum::eFAST_INERTIA_COMPUTATION)
            .value("eSHIFT_VERTICES", PxConvexFlag::Enum::eSHIFT_VERTICES);
    bindFlags<PxConvexFlag::Enum, PxU16>(m, "PxConvexFlags");

    nb::class_<PxConvexMeshDesc>(m, "PxConvexMeshDesc")
            .def(nb::init<>())
            .def("isValid", &PxConvexMeshDesc::isValid)
            .def_rw("points", &PxConvexMeshDesc::points)
            .def_rw("polygons", &PxConvexMeshDesc::polygons)
            .def_rw("indices", &PxConvexMeshDesc::indices)
            .def_rw("flags", &PxConvexMeshDesc::flags)
            .def_rw("vertexLimit", &PxConvexMeshDesc::vertexLimit)
            .def_rw("polygonLimit", &PxConvexMeshDesc::polygonLimit)
            .def_rw("quantizedCount", &PxConvexMeshDesc::quantizedCount)
            .def_rw("sdfDesc", &PxConvexMeshDesc::sdfDesc);

    nb::enum_<PxTriangleMeshCookingResult::Enum>(m, "PxTriangleMeshCookingResult")
            .value("eSUCCESS", PxTriangleMeshCookingResult::Enum::eSUCCESS)
            .value("eLARGE_TRIANGLE", PxTriangleMeshCookingResult::Enum::eLARGE_TRIANGLE)
            .value("eEMPTY_MESH", PxTriangleMeshCookingResult::Enum::eEMPTY_MESH)
            .value("eFAILURE", PxTriangleMeshCookingResult::Enum::eFAILURE);
    nb::enum_<PxMeshFlag::Enum>(m, "PxMeshFlag")
            .value("eFLIPNORMALS", PxMeshFlag::Enum::eFLIPNORMALS)
            .value("e16_BIT_INDICES", PxMeshFlag::Enum::e16_BIT_INDICES);
    bindFlags<PxMeshFlag::Enum, PxU16>(m, "PxMeshFlags");
    nb::class_<PxSimpleTriangleMesh>(m, "PxSimpleTriangleMesh")
            .def(nb::init<>())
            .def("isValid", &PxSimpleTriangleMesh::isValid)
            .def("setToDefault", &PxSimpleTriangleMesh::setToDefault)
            .def_rw("points", &PxSimpleTriangleMesh::points)
            .def_rw("triangles", &PxSimpleTriangleMesh::triangles)
            .def_rw("flags", &PxSimpleTriangleMesh::flags);
    nb::class_<PxTriangleMeshDesc, PxSimpleTriangleMesh>(m, "PxTriangleMeshDesc")
            .def(nb::init<>())
            .def("isValid", &PxTriangleMeshDesc::isValid)
            .def_rw("sdfDesc", &PxTriangleMeshDesc::sdfDesc);

    nb::enum_<PxSdfBitsPerSubgridPixel::Enum>(m, "PxSdfBitsPerSubgridPixel")
            .value("e8_BIT_PER_PIXEL", PxSdfBitsPerSubgridPixel::Enum::e8_BIT_PER_PIXEL)
            .value("e16_BIT_PER_PIXEL", PxSdfBitsPerSubgridPixel::Enum::e16_BIT_PER_PIXEL)
            .value("e32_BIT_PER_PIXEL", PxSdfBitsPerSubgridPixel::Enum::e32_BIT_PER_PIXEL);
    nb::class_<PxDim3>(m, "PxDim3")
            .def(nb::init<>())
            .def_rw("x", &PxDim3::x)
            .def_rw("y", &PxDim3::y)
            .def_rw("z", &PxDim3::z);
    nb::class_<PxSDFDesc>(m, "PxSDFDesc")
            .def(nb::init<>())
            .def("isValid", &PxSDFDesc::isValid)
            .def_rw("sdf", &PxSDFDesc::sdf)
            .def_rw("dims", &PxSDFDesc::dims)
            .def_rw("meshLower", &PxSDFDesc::meshLower)
            .def_rw("spacing", &PxSDFDesc::spacing)
            .def_rw("subgridSize", &PxSDFDesc::subgridSize)
            .def_rw("bitsPerSubgridPixel", &PxSDFDesc::bitsPerSubgridPixel)
            .def_rw("sdfSubgrids3DTexBlockDim", &PxSDFDesc::sdfSubgrids3DTexBlockDim)
            .def_rw("sdfSubgrids", &PxSDFDesc::sdfSubgrids)
            .def_rw("sdfStartSlots", &PxSDFDesc::sdfStartSlots)
            .def_rw("subgridsMinSdfValue", &PxSDFDesc::subgridsMinSdfValue)
            .def_rw("subgridsMaxSdfValue", &PxSDFDesc::subgridsMaxSdfValue)
            .def_rw("sdfBounds", &PxSDFDesc::sdfBounds)
            .def_rw("narrowBandThicknessRelativeToSdfBoundsDiagonal",
                    &PxSDFDesc::narrowBandThicknessRelativeToSdfBoundsDiagonal)
            .def_rw("numThreadsForSdfConstruction", &PxSDFDesc::numThreadsForSdfConstruction)
            .def_rw("baseMesh", &PxSDFDesc::baseMesh)
            .def_rw("sdfBuilder", &PxSDFDesc::sdfBuilder);
    nb::class_<PxSDFBuilder>(m, "PxSDFBuilder").def("release", &PxSDFBuilder::release);

    nb::class_<PxTetrahedronMeshDesc>(m, "PxTetrahedronMeshDesc")
            .def(nb::init<>())
            .def("isValid", &PxTetrahedronMeshDesc::isValid)
            .def_rw("points", &PxTetrahedronMeshDesc::points)
            .def_rw("tetrahedrons", &PxTetrahedronMeshDesc::tetrahedrons)
            .def_rw("flags", &PxTetrahedronMeshDesc::flags)
            .def_rw("tetsPerElement", &PxTetrahedronMeshDesc::tetsPerElement);

    nb::class_<PxSoftBodySimulationDataDesc>(m, "PxSoftBodySimulationDataDesc")
            .def(nb::init<>())
            .def("isValid", &PxSoftBodySimulationDataDesc::isValid)
            .def_rw("vertexToTet", &PxSoftBodySimulationDataDesc::vertexToTet);

    nb::enum_<PxMeshMidPhase::Enum>(m, "PxMeshMidPhase")
            .value("eBVH33", PxMeshMidPhase::Enum::eBVH33)
            .value("eBVH34", PxMeshMidPhase::Enum::eBVH34);
    nb::class_<PxMidphaseDesc>(m, "PxMidphaseDesc")
            .def(nb::init<>())
            .def("isValid", &PxMidphaseDesc::isValid)
            .def("getType", &PxMidphaseDesc::getType);

    nb::enum_<PxBVHBuildStrategy::Enum>(m, "PxBVHBuildStrategy")
            .value("eFAST", PxBVHBuildStrategy::Enum::eFAST)
            .value("eDEFAULT", PxBVHBuildStrategy::Enum::eDEFAULT)
            .value("eSAH", PxBVHBuildStrategy::Enum::eSAH);
    nb::class_<PxBVHDesc>(m, "PxBVHDesc")
            .def(nb::init<>())
            .def("isValid", &PxBVHDesc::isValid)
            .def("setToDefault", &PxBVHDesc::setToDefault)
            .def_rw("bounds", &PxBVHDesc::bounds)
            .def_rw("enlargement", &PxBVHDesc::enlargement)
            .def_rw("numPrimsPerLeaf", &PxBVHDesc::numPrimsPerLeaf)
            .def_rw("buildStrategy", &PxBVHDesc::buildStrategy);

    nb::class_<PxTetrahedronMeshData>(m, "PxTetrahedronMeshData").def(nb::init<>());
    nb::class_<PxSoftBodySimulationData>(m, "PxSoftBodySimulationData").def(nb::init<>());
    nb::class_<PxSoftBodyCollisionData>(m, "PxSoftBodyCollisionData").def(nb::init<>());
    nb::class_<PxCollisionTetrahedronMeshData>(m, "PxCollisionTetrahedronMeshData")
            .def("release", &PxCollisionTetrahedronMeshData::release);
    nb::class_<PxSimulationTetrahedronMeshData>(m, "PxSimulationTetrahedronMeshData")
            .def("release", &PxSimulationTetrahedronMeshData::release);
    nb::class_<PxCollisionMeshMappingData>(m, "PxCollisionMeshMappingData")
            .def("release", &PxCollisionMeshMappingData::release);

    m.def("cookTriangleMesh", immediateCooking::cookTriangleMesh)
            .def("cookHeightField", immediateCooking::cookHeightField)
            .def("cookConvexMesh", immediateCooking::cookConvexMesh)
            .def("cookBVH", immediateCooking::cookBVH)
            .def("assembleSoftBodyMesh", immediateCooking::assembleSoftBodyMesh);

    m.def("PxCookHeightField", &PxCookHeightField, "desc"_a, "stream"_a)
            .def("PxCreateHeightField", nb::overload_cast<const physx::PxHeightFieldDesc&>(&PxCreateHeightField),
                 "desc"_a)
            .def("PxCookConvexMesh", &PxCookConvexMesh, "params"_a, "desc"_a, "stream"_a,
                 "condition"_a.none() = nb::none())
            .def("PxCreateConvexMesh",
                 nb::overload_cast<const physx::PxCookingParams&, const physx::PxConvexMeshDesc&>(&PxCreateConvexMesh),
                 "params"_a, "desc"_a)
            .def("PxValidateConvexMesh", &PxValidateConvexMesh, "params"_a, "desc"_a)
            //            .def("PxComputeHullPolygons", &PxComputeHullPolygons)
            .def("PxValidateTriangleMesh", &PxValidateTriangleMesh, "params"_a, "desc"_a)
            .def("PxCookTriangleMesh", &PxCookTriangleMesh, "params"_a, "desc"_a, "stream"_a,
                 "condition"_a.none() = nb::none())
            .def("PxCreateTriangleMesh",
                 nb::overload_cast<const physx::PxCookingParams&, const physx::PxTriangleMeshDesc&>(
                         &PxCreateTriangleMesh),
                 "params"_a, "desc"_a)
            .def("PxCookTetrahedronMesh", &PxCookTetrahedronMesh, "params"_a, "meshDesc"_a, "stream"_a)
            .def("PxCreateTetrahedronMesh",
                 nb::overload_cast<const physx::PxCookingParams&, const physx::PxTetrahedronMeshDesc&>(
                         &PxCreateTetrahedronMesh),
                 "params"_a, "meshDesc"_a)
            .def("PxCookSoftBodyMesh", &PxCookSoftBodyMesh, "params"_a, "simulationMeshDesc"_a, "collisionMeshDesc"_a,
                 "softbodyDataDesc"_a, "stream"_a)
            .def("PxCreateSoftBodyMesh",
                 nb::overload_cast<const physx::PxCookingParams&, const physx::PxTetrahedronMeshDesc&,
                                   const physx::PxTetrahedronMeshDesc&, const physx::PxSoftBodySimulationDataDesc&>(
                         &PxCreateSoftBodyMesh),
                 "params"_a, "simulationMeshDesc"_a, "collisionMeshDesc"_a, "softbodyDataDesc"_a)
            .def("PxComputeModelsMapping", &PxComputeModelsMapping, "params"_a, "simulationMesh"_a, "collisionMesh"_a,
                 "collisionData"_a, "vertexToTet"_a.none() = nb::none())
            .def("PxComputeCollisionData", &PxComputeCollisionData, "params"_a, "collisionMeshDesc"_a)
            .def("PxComputeSimulationData", &PxComputeSimulationData, "params"_a, "simulationMeshDesc"_a)
            .def("PxAssembleSoftBodyMesh", &PxAssembleSoftBodyMesh, "simulationMesh"_a, "simulationData"_a,
                 "collisionMesh"_a, "collisionData"_a, "mappingData"_a, "insertionCallback"_a)
            .def("PxAssembleSoftBodyMesh_Sim", &PxAssembleSoftBodyMesh_Sim, "simulationMesh"_a, "collisionMesh"_a,
                 "mappingData"_a, "insertionCallback"_a);

    class InsertionCallback : public PxInsertionCallback {
    public:
        PxBase* buildObjectFromData(PxConcreteType::Enum type, void* data) override { return nullptr; }
    };
    nb::class_<PxInsertionCallback> pxInsertionCallback(m, "PxInsertionCallback");
    nb::class_<InsertionCallback, PxInsertionCallback> insertionCallback(m, "InsertionCallback");
}