/*
Platform - A C++ framework
*/

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#include "spdlog/common.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

// #include "platform/config_constants.h"
#include "RemoteTest.h"
#include "platform/core/SystemStatistics.h"
#include <vector>

#define NBR_OF_ARGS         2
#define CONFIG_OFFSET       1
#define NBR_OF_CONFIG_VALUE 2
#define CONFIG_VALUE_LEN    3

const std::string kLogFile = "remote_test.log";
const int kMaxSize         = 1048576;
const int kMaxFiles        = 3;
const std::string kLogName = "remote-test";

using namespace rb;
const char* config_values[NBR_OF_CONFIG_VALUE] = {
    "30K",
    "60K",
};
const char* config_paths[NBR_OF_CONFIG_VALUE]
    = {"/etc/remote-basic/remote_basic_conf_30k.json", "/etc/remote-basic/remote_basic_conf_60k.json"};

int main(int argc, char* argv[])
{
    std::vector<spdlog::sink_ptr> sinks;
    /* File sink */
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_st>(kLogFile, kMaxSize, kMaxFiles);
    file_sink->set_level(spdlog::level::debug);
    file_sink->set_pattern("[%D %H:%M:%S.%e] [%L] %v");

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);
    console_sink->set_pattern("[%D %H:%M:%S.%e] [%^%L%$] [%s:%#] %v");

    sinks.push_back(file_sink);
    sinks.push_back(console_sink);

    auto logger = std::make_shared<spdlog::logger>(kLogName, begin(sinks), end(sinks));
    logger->flush_on(spdlog::level::info);

    spdlog::register_logger(logger);
    spdlog::set_default_logger(logger);

    SPDLOG_INFO("Hello, {}", kLogName);
    platform::core::SystemStatistics::instance().dump();

    // Check input arguments
    if (argc == NBR_OF_ARGS) {
        // Get config type
        char* conf_value      = argv[CONFIG_OFFSET];
        // const char* conf_path = nullptr;
        // for (uint8_t i = 0; i < NBR_OF_CONFIG_VALUE; i++) {
        //     if (!strncmp(conf_value, config_values[i], CONFIG_VALUE_LEN)) {
        //         conf_path = config_paths[i];
        //         break;
        //     }
        // }
        // for (uint8_t i = 0; i < 5; i++) {
        const char* conf_path = "/home/hungqt/Downloads/Programs/WorkSpace/remote_basic_app/app/conf/remote_basic_conf_30k.json";
        if (conf_path != nullptr) {
            // auto gTemplateApp = new RemoteBasicApp(conf_path);
            /* Create iapplication instance */
            // AppMngConnector application("remote_basic_app", DC60SVSTT_SID_RMT_MORNITOR);
            auto rm = std::make_shared<rb::RemoteTest>();
            SPDLOG_INFO("Success create {}", argv[0]);

            rm->getConfig(conf_path);

            rm->prepare();

            rm->start();
        }
        else {
            SPDLOG_INFO("Invalid input argument {}", conf_value);
        }
        // }
    }
    else {
        SPDLOG_ERROR("Invalid number of arguments: got {}, expected {}", argc, NBR_OF_ARGS);
    }

    SPDLOG_ERROR("{}", "App stopped");

    return 0;
}
