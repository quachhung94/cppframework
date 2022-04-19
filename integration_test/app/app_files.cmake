# set(PLATFORM_LIB_ROOT ${CMAKE_CURRENT_LIST_DIR})

set(app_dir ${CMAKE_CURRENT_LIST_DIR})
set(app_inc_dir ${CMAKE_CURRENT_LIST_DIR}/include)


if(NATIVE_BUILD)
        set(APP_SOURCES
                ${app_dir}/src/main.cpp
                ${app_dir}/src/RemoteBasic.cpp
                ${app_dir}/src/OpmodeIf.cpp
                ${app_dir}/src/CanIf.cpp
                ${app_dir}/src/BrokerIf.cpp
                ${app_dir}/src/CsmIf.cpp
                ${app_dir}/src/NvmIf.cpp
                ${app_dir}/src/monitor/MonitorIf.cpp
                ${app_dir}/src/monitor/Monitor.cpp
                ${app_dir}/src/ocpp/OcppIf.cpp
                # ${app_dir}/src/SetVariableMsg.cpp
                ${app_dir}/src/ocpp/message/state/OCPPBaseState.cpp
                ${app_dir}/src/ocpp/message/state/IdleState.cpp
                ${app_dir}/src/ocpp/message/state/ProcessingState.cpp
                ${app_dir}/../stub/IOpModeManager.cpp
                ${app_dir}/../stub/OpModeManagerImpl.cpp
                ${app_dir}/../stub/ocpp_client.c
                ${app_dir}/../stub/broker.c
                ${app_dir}/../stub/cancom.c
                )
else()
        set(APP_SOURCES
                ${app_dir}/src/main.cpp
                ${app_dir}/src/RemoteBasic.cpp
                ${app_dir}/src/OpmodeIf.cpp
                ${app_dir}/src/CanIf.cpp
                ${app_dir}/src/BrokerIf.cpp
                ${app_dir}/src/CsmIf.cpp
                ${app_dir}/src/NvmIf.cpp
                ${app_dir}/src/monitor/MonitorIf.cpp
                ${app_dir}/src/monitor/Monitor.cpp
                ${app_dir}/src/ocpp/OcppIf.cpp
                # ${app_dir}/src/SetVariableMsg.cpp
                ${app_dir}/src/ocpp/message/state/OCPPBaseState.cpp
                ${app_dir}/src/ocpp/message/state/IdleState.cpp
                ${app_dir}/src/ocpp/message/state/ProcessingState.cpp
                )
endif(NATIVE_BUILD)



