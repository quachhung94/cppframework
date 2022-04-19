# cmake_minimum_required(VERSION 3.10)

# project(remote_test_app)
# set(CMAKE_CXX_STANDARD 17)

# list(APPEND LINKLIBS spdlog)
# list(APPEND LINKLIBS platform)
# list(APPEND LINKLIBS HTTPSERVER)
# list(APPEND LINKLIBS IFRuntime)

# include(app_files.cmake)
# # include(compiler.cmake)

# # if(NOT CMAKE_BUILD_TYPE)
# #     set(CMAKE_BUILD_TYPE Release)
# # endif()
# set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")
# set(CMAKE_CXX_FLAGS_RELEASE "-O3 -s -Wall -Wextra")
# include_directories(SYSTEM "${CMAKE_CURRENT_LIST_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/../../Logging/spdlog/include" 
# "${CMAKE_CURRENT_LIST_DIR}/../jsoncpp/include" "${CMAKE_CURRENT_LIST_DIR}/stub/include" "${CMAKE_CURRENT_LIST_DIR}/stub/include/appfw")
# add_executable(${PROJECT_NAME} ${APP_SOURCES})

# if(NATIVE_BUILD)
#     add_library(jsoncpp SHARED IMPORTED) # or STATIC instead of SHARED
#     set_target_properties(jsoncpp PROPERTIES
#     IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/lib/libjsoncpp.so.1.9.5"
#     INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/../jsoncpp/include"
#     )
#     target_link_libraries(${PROJECT_NAME} platform pthread ${LINKLIBS} jsoncpp)
    # target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/app/include
    #                                                     ${CMAKE_CURRENT_LIST_DIR}/../jsoncpp/include
    #                                                     ${CMAKE_CURRENT_LIST_DIR}/stub/include
    #                                                     ${CMAKE_CURRENT_LIST_DIR}/stub/include/appfw
    #                                                     ${CMAKE_CURRENT_LIST_DIR}/../Logging/spdlog/include)
# endif(NATIVE_BUILD)

# if(NATIVE_BUILD)
# else()
# if (CMAKE_BUILD_TYPE STREQUAL Release)
#     # message(STATUS "CMAKE_BUILD_TYPE App Release")
#     # add_custom_command(TARGET remote_basic_app POST_BUILD
#     #         COMMAND ${CMAKE_STRIP} remote_basic_app)
# endif ()
# endif()
# # set_compile_options(${PROJECT_NAME})

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()


# Link libraries
# list(APPEND LINKLIBS ${OPENSSL_LIBRARIES})
list(APPEND LINKLIBS spdlog)
list(APPEND LINKLIBS platform)
list(APPEND LINKLIBS HTTPSERVER)
list(APPEND LINKLIBS IFRuntime)
# list(APPEND LINKLIBS jsoncpp)
include(app_files.cmake)
# OpenSSL libraries
# message(STATUS "OpenSSL version: ${OPENSSL_VERSION} ${OPENSSL_INCLUDE_DIR} ${OPENSSL_LIBRARIES}")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -s -Wall -Wextra -Wno-deprecated-declarations")
if(NATIVE_BUILD)
    add_library(jsoncpp SHARED IMPORTED) # or STATIC instead of SHARED
    set_target_properties(jsoncpp PROPERTIES
    IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/lib/libjsoncpp.so.1.9.5"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/../jsoncpp/include"
    )
endif(NATIVE_BUILD)
    
# System directories
include_directories(SYSTEM "${CMAKE_CURRENT_LIST_DIR}/app/include" "${CMAKE_CURRENT_SOURCE_DIR}/../../Logging/spdlog/include" 
"${CMAKE_CURRENT_LIST_DIR}/stub/include" "${CMAKE_CURRENT_LIST_DIR}/stub/include/appfw")

# client
file(GLOB EXAMPLE_HEADER_FILES "*.h")
# file(GLOB EXAMPLE_INLINE_FILES "*.inl")
file(GLOB EXAMPLE_SOURCE_FILES "*.cpp")

add_executable(remote_test ${APP_SOURCES})
target_link_libraries(remote_test ${LINKLIBS} jsoncpp)