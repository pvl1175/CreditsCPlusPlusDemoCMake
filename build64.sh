rm -r -f build64
rm -r -f CS-API
rm -r -f thrift
rm -r -f api

git clone https://github.com/CREDITSCOM/CS-API
mkdir api
thrift -r -gen cpp:no_skeleton,pure_enums,moveable_types -out .\api .\CS-API\api.thrift

git clone https://github.com/apache/thrift.git
cd thrift
git checkout 0.12.1

cd ..
mkdir build64
cd build64

cmake ..
cmake  --build . --config Debug
cmake  --build . --config Release




