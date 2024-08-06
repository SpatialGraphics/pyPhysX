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

void bindFilter(nb::module_& m) {
    nb::class_<PxFilterData>(m, "PxFilterData")
            .def(nb::init<>())
            .def(nb::init<PxU32, PxU32, PxU32, PxU32>())
            .def_rw("word0", &PxFilterData::word0)
            .def_rw("word1", &PxFilterData::word1)
            .def_rw("word2", &PxFilterData::word2)
            .def_rw("word3", &PxFilterData::word3)
            .def("setToDefault", &PxFilterData::setToDefault);

    class QueryFilterCallback : public PxQueryFilterCallback {
    public:
        QueryFilterCallback(const std::function<PxQueryHitType::Enum(const PxFilterData& filterData,
                                                                     const PxShape* shape,
                                                                     const PxRigidActor* actor,
                                                                     uint32_t& queryFlags)>& c1,
                            const std::function<PxQueryHitType::Enum(const PxFilterData& filterData,
                                                                     const PxQueryHit& hit,
                                                                     const PxShape* shape,
                                                                     const PxRigidActor* actor)>& c2)
            : c1(c1), c2(c2) {}

        PxQueryHitType::Enum preFilter(const PxFilterData& filterData,
                                       const PxShape* shape,
                                       const PxRigidActor* actor,
                                       PxHitFlags& queryFlags) override {
            uint32_t flags;
            auto result = c1(filterData, shape, actor, flags);
            queryFlags = PxHitFlags(flags);
            return result;
        }
        PxQueryHitType::Enum postFilter(const PxFilterData& filterData,
                                        const PxQueryHit& hit,
                                        const PxShape* shape,
                                        const PxRigidActor* actor) override {
            return c2(filterData, hit, shape, actor);
        }

    private:
        std::function<PxQueryHitType::Enum(
                const PxFilterData& filterData, const PxShape* shape, const PxRigidActor* actor, uint32_t& queryFlags)>
                c1;
        std::function<PxQueryHitType::Enum(
                const PxFilterData& filterData, const PxQueryHit& hit, const PxShape* shape, const PxRigidActor* actor)>
                c2;
    };
    nb::class_<PxQueryFilterCallback> pxQueryFilterCallback(m, "PxQueryFilterCallback");
    nb::class_<QueryFilterCallback, PxQueryFilterCallback>(m, "QueryFilterCallback")
            .def(nb::init<
                    const std::function<PxQueryHitType::Enum(const PxFilterData& filterData, const PxShape* shape,
                                                             const PxRigidActor* actor, uint32_t& queryFlags)>&,
                    const std::function<PxQueryHitType::Enum(const PxFilterData& filterData, const PxQueryHit& hit,
                                                             const PxShape* shape, const PxRigidActor* actor)>&>());
}