# set(PLATFORM_LIB_ROOT ${CMAKE_CURRENT_LIST_DIR})

set(test_dir ${CMAKE_CURRENT_LIST_DIR})
set(app_dir ${CMAKE_CURRENT_LIST_DIR}/app)
set(app_inc_dir ${CMAKE_CURRENT_LIST_DIR}/app/include)


if(NATIVE_BUILD)
        set(APP_SOURCES
                ${test_dir}/stress_test.cpp
                ${test_dir}/RemoteTest.cpp
                ${app_dir}/src/CsmIf.cpp
                ${app_dir}/src/NvmIf.cpp
                )
endif(NATIVE_BUILD)