# raycasting
A simple minifb project to demonstrate raycasting techique
Based on great raycasting tutorial by Lode Vandevenne: https://lodev.org/cgtutor/raycasting.html

Building:

> cmake --preset mingw-build
> cd build
> mingw32-make.exe

Command for Linux:
cmake --build build ; build/RaycastingMiniFB


Command for WebAss:

cmake -DCMAKE_TOOLCHAIN_FILE=/home/halfdan/Projects/Potato/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -DMINIFB_BUILD_EXAMPLES=OFF -S . -B buildHtml
cmake --build build ; 
emcc @CMakeFiles/RaycastingMiniFB.dir/objects1.rsp dependencies/minifb/libminifb.a -o RaycastingMiniFB.html

Upload to a server (this is for me, so i don't have to remember):
scp -r buildHtml/* {user}@{server}:{server path}/raycasting

