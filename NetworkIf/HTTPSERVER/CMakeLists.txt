project(HTTPServer_lib VERSION 1.0.0)

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp" "*.h")

add_library(HTTPSERVER STATIC ${src_files})

target_include_directories(HTTPSERVER PUBLIC "./include" "${CMAKE_CURRENT_SOURCE_DIR}/../../Logging/spdlog/include")

target_link_libraries(HTTPSERVER
PUBLIC cppserver cppcommon)
