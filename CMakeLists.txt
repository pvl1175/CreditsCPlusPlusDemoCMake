cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    set(BOOST_ROOT d:/boost)
else()
    set(BOOST_ROOT ~/boost)
endif()

if (MSVC)
    add_definitions(-DNOMINMAX)
endif()

add_definitions(-DUSE_STD_THREAD)
if (MSVC)
  option(BUILD_COMPILER "" OFF)
endif(MSVC)
option(WITH_BOOST_STATIC "" ON)
option(BUILD_TESTING "" OFF)
option(BUILD_TUTORIALS "" OFF)
option(BUILD_EXAMPLES "" OFF)
option(BUILD_PYTHON "" OFF)
option(WITH_SHARED_LIB "" OFF)
option(WITH_STATIC_LIB "" ON)
option(WITH_C_GLIB "" OFF)
option(WITH_JAVA "" OFF)
option(WITH_PYTHON "" OFF)
option(WITH_QT4 "" OFF)
option(WITH_QT5 "" OFF)
option(WITH_ZLIB "" OFF)
option(WITH_STDTHREADS "" ON)
option(WITH_LIBEVENT "" OFF)
option(WITH_OPENSSL "" OFF)
add_subdirectory(thrift)

find_package(Boost 1.68 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories("./thrift/lib/cpp/src")

add_executable(main
	api_constants.h
	api_types.h
	API.h
	base58.h
	variant_constants.h
	variant_types.h
	api_constants.cpp
	api_types.cpp
	API.cpp
	base58.cpp
	variant_constants.cpp
	variant_types.cpp
	main.cpp
)

target_link_libraries(main ${Boost_LIBRARIES})
target_link_libraries(main thrift_static)
