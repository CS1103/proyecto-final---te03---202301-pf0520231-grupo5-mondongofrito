cmake_minimum_required(VERSION 3.0.0)
project(MondongoFrito VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(C:/tools/opencv/build/include)

add_executable(MondongoFrito main.cpp imageloading.h imageloading.cpp menu.h structure.h)

target_link_libraries(MondongoFrito ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
