
project(urtcenginedemo)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE "release")
set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -ggdb -o3 -fpermissive -fPIC")
set(ENGINEDEMO_LDFLAGS "-Wl,-rpath -LZ")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(THIRDPARTY ${PROJECT_SOURCE_DIR}/third_party)
set(RAPIDJSON ${THIRDPARTY}/rapidjson/include)
set(URTC_MEDIA_PATH ${PROJECT_SOURCE_DIR}/urtclib/interface)
set(URTC_MEDIA_LIB ${PROJECT_SOURCE_DIR}/urtclib/lib)


aux_source_directory(
  ${PROJECT_SOURCE_DIR}/
  SRCS
)

include_directories(
  ${PROJECT_SOURCE_DIR}
)

include_directories(
  ${URTC_MEDIA_PATH}
  ${RAPIDJSON}
)

link_directories(
  ${URTC_MEDIA_LIB}
)

set (ALL_LDFLAGS
  ${ENGINEDEMO_LDFLAGS}
)

link_libraries(
    "liburtcmediaengine.so"
)

add_library(urtclib  SHARED ${SRCS}  ) 
target_link_libraries( urtclib dl  stdc++ -lpthread -lm)
