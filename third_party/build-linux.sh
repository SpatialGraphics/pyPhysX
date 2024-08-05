sed -i 's/name="PX_BUILDSNIPPETS" value="True"/name="PX_BUILDSNIPPETS" value="False"/g' physx/physx/buildtools/presets/public/linux.xml
sed -i 's/name="PX_BUILDPVDRUNTIME" value="True"/name="PX_BUILDPVDRUNTIME" value="False"/g' physx/physx/buildtools/presets/public/linux.xml
sed -i 's/-Werror//g' physx/physx/source/compiler/cmake/linux/CMakeLists.txt
cd physx/physx
./generate_projects.sh linux
cmake --build compiler/linux-release --config Release
cmake --build compiler/linux-checked --config Checked
