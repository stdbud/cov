cmake_minimum_required(VERSION 3.12)

project(budCov VERSION 1.0)

set(CMAKE_CXX_COMPILER g++)

add_library(vulkan SHARED ${PROJECT_SOURCE_DIR}/vkstub/budVkStub.cpp)
target_include_directories(vulkan PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(vulkan PUBLIC -std=c++17
                                     -ggdb)

add_library(OpenCL SHARED ${PROJECT_SOURCE_DIR}/src/budCovContext.cpp
                          ${PROJECT_SOURCE_DIR}/src/budCovDevice.cpp
                          ${PROJECT_SOURCE_DIR}/src/budCovEntries.cpp
                          ${PROJECT_SOURCE_DIR}/src/budCovIcd.cpp
                          ${PROJECT_SOURCE_DIR}/src/budCovPlatform.cpp)
target_include_directories(OpenCL PUBLIC ${PROJECT_SOURCE_DIR}/include
                                         ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(OpenCL PUBLIC vulkan)
target_compile_options(OpenCL PUBLIC -DCOV_MAX_VERSION=120
                                     -std=c++17
                                     -ggdb)

add_executable(budCovTest ${PROJECT_SOURCE_DIR}/test/budCovTest.cpp
                          ${PROJECT_SOURCE_DIR}/test/budCovTestPlatform.cpp)
target_include_directories(budCovTest PUBLIC ${PROJECT_SOURCE_DIR}/include
                                             ${PROJECT_SOURCE_DIR}/test)
target_link_libraries(budCovTest PUBLIC OpenCL
                                        pthread)
target_compile_options(budCovTest PUBLIC -DCL_TARGET_OPENCL_VERSION=120
                                         -DCL_USE_DEPRECATED_OPENCL_1_0_APIS
                                         -DCL_USE_DEPRECATED_OPENCL_1_1_APIS
                                         -std=c++17
                                         -ggdb)
