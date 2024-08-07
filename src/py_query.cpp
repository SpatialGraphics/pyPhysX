//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <PxPhysicsAPI.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/function.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

void bindQuery(nb::module_& m) {
    nb::class_<PxQueryHit>(m, "PxQueryHit").def(nb::init<>()).def_rw("faceIndex", &PxQueryHit::faceIndex);

    nb::class_<PxLocationHit, PxQueryHit>(m, "PxLocationHit")
            .def(nb::init<>())
            .def_rw("position", &PxLocationHit::position)
            .def_rw("normal", &PxLocationHit::normal)
            .def_rw("distance", &PxLocationHit::distance)
            .def("hadInitialOverlap", &PxLocationHit::hadInitialOverlap);

    nb::class_<PxGeomRaycastHit, PxQueryHit>(m, "PxGeomRaycastHit")
            .def(nb::init<>())
            .def_rw("u", &PxGeomRaycastHit::u)
            .def_rw("v", &PxGeomRaycastHit::v);
    nb::class_<PxRaycastHit, PxGeomRaycastHit>(m, "PxRaycastHit").def(nb::init<>());

    nb::class_<PxGeomOverlapHit, PxQueryHit>(m, "PxGeomOverlapHit").def(nb::init<>());
    nb::class_<PxOverlapHit, PxGeomOverlapHit>(m, "PxOverlapHit").def(nb::init<>());

    nb::class_<PxGeomSweepHit, PxQueryHit>(m, "PxGeomSweepHit").def(nb::init<>());
    nb::class_<PxSweepHit, PxGeomSweepHit>(m, "PxSweepHit").def(nb::init<>());

    nb::class_<PxQueryFilterData>(m, "PxQueryFilterData").def(nb::init<>());
    nb::class_<PxQueryCache>(m, "PxQueryCache")
            .def(nb::init<>())
            .def_rw("faceIndex", &PxQueryCache::faceIndex)
            .def_rw("actor", &PxQueryCache::actor)
            .def_rw("shape", &PxQueryCache::shape);

    nb::class_<PxSceneQueryExt>(m, "PxSceneQueryExt")
            .def(nb::init<>())
            .def_static("overlapAny", &PxSceneQueryExt::overlapAny)
            .def_static("overlapMultiple", &PxSceneQueryExt::overlapMultiple)
            .def_static("raycastAny", &PxSceneQueryExt::raycastAny)
            .def_static("raycastMultiple",  &PxSceneQueryExt::raycastMultiple)
            .def_static("raycastSingle", &PxSceneQueryExt::raycastSingle)
            .def_static("sweepAny", &PxSceneQueryExt::sweepAny)
            .def_static("sweepMultiple", &PxSceneQueryExt::sweepMultiple)
            .def_static("sweepSingle", &PxSceneQueryExt::sweepSingle);
}