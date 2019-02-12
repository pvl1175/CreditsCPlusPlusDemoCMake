rmdir /S /Q build64
rmdir /S /Q CS-API
rmdir /S /Q thrift
del /Q API.cpp
del /Q api_constants.cpp
del /Q API_server.skeleton.cpp
del /Q api_types.cpp
del /Q variant_constants.cpp
del /Q variant_types.cpp
del /Q API.h
del /Q api_constants.h
del /Q api_types.h
del /Q variant_constants.h
del /Q variant_types.h

git clone https://github.com/CREDITSCOM/CS-API
thrift-0.11.0 -r -gen cpp:no_skeleton,pure_enums,moveable_types -out . .\CS-API\api.thrift

git clone https://github.com/apache/thrift.git

mkdir build64
cd build64
cmake .. -A x64
cmake --build .