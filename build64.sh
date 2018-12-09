rm -r -f build64
rm -r -f CS-API
rm -r -f thrift
rm API.cpp
rm api_constants.cpp
rm API_server.skeleton.cpp
rm api_types.cpp
rm variant_constants.cpp
rm variant_types.cpp
rm API.h
rm api_constants.h
rm api_types.h
rm variant_constants.h
rm variant_types.h

git clone https://github.com/CREDITSCOM/CS-API
thrift --gen cpp -out . ./CS-API/api.thrift
thrift --gen cpp -out . ./CS-API/variant.thrift

git clone https://github.com/apache/thrift.git

mkdir build64
cd build64
cmake ..
cmake --build .
