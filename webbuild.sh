rm -fr buildHtml
cmake -DCMAKE_TOOLCHAIN_FILE=/home/halfdan/Projects/Potato/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -DMINIFB_BUILD_EXAMPLES=OFF -S . -B buildHtml
cmake --build buildHtml 
cd buildHtml
emcc @CMakeFiles/RaycastingMiniFB.dir/objects1.rsp dependencies/minifb/libminifb.a -sASYNCIFY -o index.html
