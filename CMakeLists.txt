cmake_minimum_required(VERSION 3.15...3.26)

project(pyPhysX LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

#add_subdirectory(third_party)

# Try to import all Python components potentially needed by nanobind
find_package(Python 3.8
        REQUIRED COMPONENTS Interpreter Development.Module
        OPTIONAL_COMPONENTS Development.SABIModule)

execute_process(
        COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
        OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT)

# Import nanobind through CMake's find_package mechanism
find_package(nanobind CONFIG REQUIRED)

set(BINDING_FILES
        src/py_physx_ext.cpp
)

# We are now ready to compile the actual extension module
nanobind_add_module(
        # Name of the extension
        py_physx_ext

        # Target the stable ABI for Python 3.12+, which reduces
        # the number of binary wheels that must be built. This
        # does nothing on older Python versions
        STABLE_ABI

        # Build libnanobind statically and merge it into the
        # extension (which itself remains a shared library)
        #
        # If your project builds multiple extensions, you can
        # replace this flag by NB_SHARED to conserve space by
        # reusing a shared libnanobind across libraries
        NB_STATIC

        # Source code goes here
        ${BINDING_FILES}
)

nanobind_add_stub(
        py_physx_stub
        MODULE py_physx_ext
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/pyPhysX/__init__.pyi
        PYTHON_PATH $<TARGET_FILE_DIR:py_physx_ext>
        DEPENDS py_physx_ext
)

#target_link_libraries(py_physx_ext PRIVATE
#        filament
#        math
#        utils
#        filamat
#        filabridge
#
#        ktxreader
#        filameshio
#        uberarchive
#        gltfio_core
#)

# Install directive for scikit-build-core
install(TARGETS py_physx_ext LIBRARY DESTINATION pyPhysX)
