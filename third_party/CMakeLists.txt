set(physx5_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/physx/physx)
add_library(physx5 INTERFACE)

if (UNIX)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_link_directories(physx5 INTERFACE $<BUILD_INTERFACE:${physx5_SOURCE_DIR}/bin/linux.clang/checked>)
    else ()
        target_link_directories(physx5 INTERFACE $<BUILD_INTERFACE:${physx5_SOURCE_DIR}/bin/linux.clang/release>)
    endif ()
    target_link_libraries(physx5 INTERFACE
            -Wl,--start-group
            libPhysXCharacterKinematic_static_64.a libPhysXCommon_static_64.a
            libPhysXCooking_static_64.a libPhysXExtensions_static_64.a
            libPhysXFoundation_static_64.a libPhysXPvdSDK_static_64.a
            libPhysX_static_64.a libPhysXVehicle_static_64.a
            -Wl,--end-group)
    target_include_directories(physx5 SYSTEM INTERFACE $<BUILD_INTERFACE:${physx5_SOURCE_DIR}/include>)
endif ()

if (WIN32)
    target_include_directories(physx5 SYSTEM INTERFACE $<BUILD_INTERFACE:${physx5_SOURCE_DIR}/include>)
    target_link_directories(physx5 INTERFACE $<BUILD_INTERFACE:${physx5_SOURCE_DIR}/bin/win.x86_64.vc143.mt/release>)
    target_link_libraries(physx5 INTERFACE
            PhysXVehicle2_static_64.lib PhysXExtensions_static_64.lib
            PhysXVehicle_static_64.lib PhysX_static_64.lib PhysXPvdSDK_static_64.lib
            PhysXCooking_static_64.lib PhysXCommon_static_64.lib
            PhysXCharacterKinematic_static_64.lib PhysXFoundation_static_64.lib)
endif ()

target_compile_definitions(physx5 INTERFACE PX_PHYSX_STATIC_LIB)
target_compile_definitions(physx5 INTERFACE PHYSX_VERSION="${PHYSX_VERSION}")