//  Copyright (c) 2024 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <nanobind/nanobind.h>
#include <PxPhysicsAPI.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace physx;

extern void bindMath(nb::module_& m);
extern void bindMaterial(nb::module_& m);
extern void bindActor(nb::module_& m);
extern void bindShape(nb::module_& m);
extern void bindJoint(nb::module_& m);
extern void bindScene(nb::module_& m);
extern void bindPhysics(nb::module_& m);
extern void bindFoundation(nb::module_& m);

extern void bindIO(nb::module_& m);
extern void bindAggregate(nb::module_& m);
extern void bindTriangleMesh(nb::module_& m);
extern void bindTetrahedronMesh(nb::module_& m);
extern void bindSoftBodyMesh(nb::module_& m);
extern void bindConvexMesh(nb::module_& m);
extern void bindHeightField(nb::module_& m);
extern void bindArticulationReducedCoordinate(nb::module_& m);
extern void bindParticle(nb::module_& m);

extern void bindController(nb::module_& m);
extern void bindConstraint(nb::module_& m);
extern void bindRender(nb::module_& m);
extern void bindFilter(nb::module_& m);
extern void bindQuery(nb::module_& m);
extern void bindUtils(nb::module_& m);
extern void bindCooking(nb::module_& m);

extern void bindDevice(nb::module_& m);
#ifdef SUPPORT_CUDA
extern void bindCuda(nb::module_& m);
#endif

NB_MODULE(py_physx_ext, m) {
    m.doc() = "python binding for PhysX";

    bindMath(m);
    bindMaterial(m);
    bindShape(m);
    bindActor(m);
    bindJoint(m);
    bindScene(m);
    bindPhysics(m);
    bindFoundation(m);

    bindIO(m);
    bindAggregate(m);
    bindTriangleMesh(m);
    bindTetrahedronMesh(m);
    bindSoftBodyMesh(m);
    bindConvexMesh(m);
    bindHeightField(m);
    bindArticulationReducedCoordinate(m);
    bindParticle(m);

    bindController(m);
    bindConstraint(m);
    bindRender(m);
    bindFilter(m);
    bindQuery(m);
    bindUtils(m);
    bindCooking(m);

    bindDevice(m);
#ifdef SUPPORT_CUDA
    bindCuda(m);
#endif
}
