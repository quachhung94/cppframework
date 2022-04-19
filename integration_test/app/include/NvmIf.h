/**
 * @file nvmIf.h
 * @author Steven Le (sonlq@vingroup.net)
 * @brief
 * @version 0.1
 * @date 2021-12-10
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <chrono>
#include <deque>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <regex>
#include <string>
#include "ocpp_types.h"

#define RETRY_BACKOFF_WAIT_MINIMUM 0x01
#define RETRY_BACKOFF_REPEAT_TIMES 0x02
#define RETRY_BACKOFF_RANDOM_RANGE 0x04
namespace rb::nvm {

/**
 * @brief Nvm Interface
 *
 */
class NvmIf {

public:
    /**
     * @brief Construct a new Nvm If object
     *
     * @param interface_id
     * @param stack_size
     * @param priority
     * @param app_event_queue
     */

    NvmIf()  = default;
    ~NvmIf() = default;

    struct GroupSetReconnectParam {
        /* data */
        reconnect_param mParam;
        uint32_t mOptions;
        GroupSetReconnectParam(int param, uint32_t opt) : mOptions(opt)
        {
            // memset((void*)mParam, 0, sizeof(reconnect_param));
            if (opt == RETRY_BACKOFF_WAIT_MINIMUM) {
                mParam.retryBackOffWaitMinimum = param;
            }
            else if (opt == RETRY_BACKOFF_REPEAT_TIMES) {
                mParam.retryBackOffRepeatTimes = param;
            }
            else if (opt == RETRY_BACKOFF_RANDOM_RANGE) {
                mParam.retryBackOffRandomRange = param;
            }
        }
    };

    bool updateServerIP(std::string ip);
    bool updateServerDomain(std::string domain);
    bool updateDNSServer(std::string dns, uint8_t index);
    bool updateNTPServer(std::string ntp, uint8_t index);
    bool updateReconnectParam(std::string set_string, uint8_t index);
    bool groupParamSetting(GroupSetReconnectParam& param);

private:
    bool checkNumber(const std::string& str);
    std::vector<std::string> splitString(const std::string& str, char delim);
    bool validateIP(std::string ip);

    std::queue<std::shared_ptr<GroupSetReconnectParam>> m_groupSetReconnectParam;
    std::mutex m_groupSetReconnectParam_mtx;
};
} // namespace rb::nvm
