/**
 * @file nvmIf.cpp
 * @author Steven Le (sonlq@vingroup.net)
 * @brief
 * @version 0.1
 * @date 2021-12-10
 *
 * @copyright Copyright (c) 2021
 *
 */

// #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#include "spdlog/spdlog.h"

#include "NvmIf.h"

#define DATA_CONFIG_TXT_FILE_PATH      "/udata/config.txt"
#define DATA_CONFIG__TMP_TXT_FILE_PATH "/udata/config_tmp.txt"
#define SERVER_INFO_TXT_FILE_PATH      "/udata/config.txt"
#define SERVER_INFO__TMP_TXT_FILE_PATH "/udata/config_tmp.txt"
#define NTP_CONF_FILE_PATH             "/udata/config.txt"
#define NTP__TMP_CONF_FILE_PATH        "/udata/config_tmp.txt"
#define RECONNECT_CONF_FILE_PATH       "/etc/ocpp/domain/server_info.txt"
#define RECONNECT__TMP_CONF_FILE_PATH  "/etc/ocpp/domain/server_info_tmp.txt"

namespace rb::nvm {
bool NvmIf::checkNumber(const std::string& str)
{
    return !str.empty() && (str.find_first_not_of("[0123456789]") == std::string::npos);
}

std::vector<std::string> NvmIf::splitString(const std::string& str, char delim)
{
    auto i = 0;
    std::vector<std::string> list;
    auto pos = str.find(delim);
    while (pos != std::string::npos) {
        list.push_back(str.substr(i, pos - i));
        i   = ++pos;
        pos = str.find(delim, pos);
    }
    list.push_back(str.substr(i, str.length()));
    return list;
}

bool NvmIf::validateIP(std::string ip)
{
    // split the string into tokens
    std::vector<std::string> slist = splitString(ip, '.');
    if (slist.size() != 4)
        return false;
    for (std::string str : slist) {
        // check that string is number, positive, and range
        if (!checkNumber(str) || stoi(str) < 0 || stoi(str) > 255)
            return false;
    }
    return true;
}

bool NvmIf::updateServerIP(std::string ip)
{
    SPDLOG_INFO("{}", "updateServerIP");
    bool retVal{false};
    if (validateIP(ip) != true) {
        SPDLOG_INFO("{}", "Invalid setting IP format");
        return retVal;
    }

    std::string src_file_path(DATA_CONFIG_TXT_FILE_PATH);
    std::string dst_file_path(DATA_CONFIG__TMP_TXT_FILE_PATH);
    std::ifstream src_file(src_file_path);
    std::ofstream dst_file(dst_file_path);
    std::string line;

    if (src_file && dst_file) {
        while (std::getline(src_file, line)) {
            line.erase(remove(line.begin(), line.end(), ' '), line.end());

            std::vector<std::string> slist = splitString(line, '=');
            if (slist.size() == 2) {
                if (slist[0].compare(std::string("csms")) == 0) {
                    if (validateIP(slist[1]) == true) {
                        SPDLOG_INFO("Current Server IP: {}", slist[1].c_str());
                        SPDLOG_INFO("Update Server IP: {}", ip.c_str());
                        /* Modified line */
                        line = std::regex_replace(line, std::regex(slist[1].c_str()), ip.c_str());
                    }
                }
            }
            line = std::regex_replace(line, std::regex("="), " = ");
            dst_file << line << "\n";
        }
        retVal = true;
    }
    else {
        SPDLOG_INFO("{}", "Cannot open File");
    }
    if (src_file.is_open())
        src_file.close();

    if (dst_file.is_open())
        dst_file.close();

    if (retVal == true) {
        int value = 0;
        value     = remove(DATA_CONFIG_TXT_FILE_PATH);

        if (!value) {
            SPDLOG_INFO("{}", "File rm successfully");
        }
        else {
            SPDLOG_ERROR("{}", "File mv failed");
        }
        value = rename(DATA_CONFIG__TMP_TXT_FILE_PATH, DATA_CONFIG_TXT_FILE_PATH);
        // Print the result
        if (!value) {
            SPDLOG_INFO("{}", "File rn successfully");
        }
        else {
            SPDLOG_ERROR("{}", "File rn failed");
        }
    }

    return retVal;
}

bool NvmIf::updateServerDomain(std::string domain)
{
    SPDLOG_INFO("{}", "updateServerDomain");
    bool retVal{false};
    std::string config_host;
    std::string config_port;
    std::vector<std::string> slist = splitString(domain, ':');
    for (std::string str : slist) {
        SPDLOG_INFO("{}", str);
    }
    if (slist.size() == 1) {
        config_host = slist[0];
    }
    else if (slist.size() == 2) {
        config_host = slist[0];
        config_port = slist[1];
    }

    std::string src_file_path(SERVER_INFO_TXT_FILE_PATH);
    std::string dst_file_path(SERVER_INFO__TMP_TXT_FILE_PATH);
    std::ifstream src_file(src_file_path);
    std::ofstream dst_file(dst_file_path);
    std::string line;

    if (src_file && dst_file) {
        while (std::getline(src_file, line)) {
            line.erase(remove(line.begin(), line.end(), ' '), line.end());

            std::vector<std::string> slist = splitString(line, '=');
            if (slist.size() == 2) {
                if (slist[0].compare(std::string("csms")) == 0) {
                    SPDLOG_INFO("Current domain: {}", slist[1].c_str());
                    SPDLOG_INFO("New domain: {}", config_host.c_str());
                    /* Modified line */
                    line = std::regex_replace(line, std::regex(slist[1].c_str()), config_host.c_str());
                }
                else if ((slist[0].compare(std::string("server_port")) == 0) && (!config_port.empty())) {
                    SPDLOG_INFO("Current port: {}", slist[1].c_str());
                    SPDLOG_INFO("New port: {}", config_port.c_str());
                    /* Modified line */
                    line = std::regex_replace(line, std::regex(slist[1].c_str()), config_port.c_str());
                }
            }
            dst_file << line << "\n";
        }
        retVal = true;
    }
    else {
        SPDLOG_INFO("{}", "Cannot open File");
    }
    if (src_file.is_open())
        src_file.close();

    if (dst_file.is_open())
        dst_file.close();

    if (retVal == true) {
        int value = 0;
        value     = remove(SERVER_INFO_TXT_FILE_PATH);

        if (!value) {
            SPDLOG_INFO("{}", "File rm successfully");
        }
        else {
            SPDLOG_ERROR("{}", "File mv failed");
        }
        value = rename(SERVER_INFO__TMP_TXT_FILE_PATH, SERVER_INFO_TXT_FILE_PATH);
        // Print the result
        if (!value) {
            SPDLOG_INFO("{}", "File rn successfully");
        }
        else {
            SPDLOG_ERROR("{}", "File rn failed");
        }
    }

    return retVal;
}

bool NvmIf::updateDNSServer(std::string dns, uint8_t index)
{
    SPDLOG_INFO("{}", "updateDNSServer");
    bool retVal{false};

    if (dns.empty()) {
        SPDLOG_INFO("{}", "Invalid param");
        return retVal;
    }

    std::string origin_str = dns;

    std::string src_file_path(DATA_CONFIG_TXT_FILE_PATH);
    std::string dst_file_path(DATA_CONFIG__TMP_TXT_FILE_PATH);
    std::ifstream src_file(src_file_path);
    std::ofstream dst_file(dst_file_path);
    std::string line;

    if (src_file && dst_file) {
        while (std::getline(src_file, line)) {
            line.erase(remove(line.begin(), line.end(), ' '), line.end());

            std::vector<std::string> slist = splitString(line, '=');
            if (validateIP(origin_str) == false) {
                SPDLOG_INFO("{}", "Invalid IP format");
                continue;
            }
            if (index == 0) {
                if (slist[0].compare(std::string("dns1")) == 0) {
                    SPDLOG_INFO("Current dns1: {}", slist[1].c_str());
                    SPDLOG_INFO("New dns1: {}", dns.c_str());
                    /* Modified line */
                    line = std::regex_replace(line, std::regex(slist[1].c_str()), dns.c_str());
                }
            }
            else if (index == 1) {
                if (slist[0].compare(std::string("dns2")) == 0) {
                    SPDLOG_INFO("Current dns2: {}", slist[1].c_str());
                    SPDLOG_INFO("New dns2: {}", dns.c_str());
                    /* Modified line */
                    line = std::regex_replace(line, std::regex(slist[1].c_str()), dns.c_str());
                }
            }
            line = std::regex_replace(line, std::regex("="), " = ");
            dst_file << line << "\n";
        }
        retVal = true;
    }
    else {
        SPDLOG_INFO("{}", "Cannot open File");
    }
    if (src_file.is_open())
        src_file.close();

    if (dst_file.is_open())
        dst_file.close();

    if (retVal == true) {
        int value = 0;
        value     = remove(DATA_CONFIG_TXT_FILE_PATH);

        if (!value) {
            SPDLOG_INFO("{}", "File rm successfully");
        }
        else {
            SPDLOG_ERROR("{}", "File mv failed");
        }
        value = rename(DATA_CONFIG__TMP_TXT_FILE_PATH, DATA_CONFIG_TXT_FILE_PATH);
        // Print the result
        if (!value) {
            SPDLOG_INFO("{}", "File rn successfully");
        }
        else {
            SPDLOG_ERROR("{}", "File rn failed");
        }
    }

    return retVal;
}

bool NvmIf::updateNTPServer(std::string ntp, uint8_t index)
{
    SPDLOG_INFO("{}", "updateNTPServer");
    bool retVal{false};
    if (ntp.empty()) {
        SPDLOG_INFO("{}", "Invalid param");
        return retVal;
    }

    std::string origin_str = ntp;

    std::string src_file_path(NTP_CONF_FILE_PATH);
    std::string dst_file_path(NTP__TMP_CONF_FILE_PATH);
    std::ifstream src_file(src_file_path);
    std::ofstream dst_file(dst_file_path);
    std::string line;

    if (src_file && dst_file) {
        while (std::getline(src_file, line)) {
            line.erase(remove(line.begin(), line.end(), ' '), line.end());

            std::vector<std::string> slist = splitString(line, '=');
            if (index == 0) {
                if (slist[0].compare(std::string("time1")) == 0) {
                    SPDLOG_INFO("Current time1: {}", slist[1].c_str());
                    SPDLOG_INFO("New time1: {}", ntp.c_str());
                    /* Modified line */
                    line = std::regex_replace(line, std::regex(slist[1].c_str()), ntp.c_str());
                }
            }
            else if (index == 1) {
                if (slist[0].compare(std::string("time2")) == 0) {
                    SPDLOG_INFO("Current time2: {}", slist[1].c_str());
                    SPDLOG_INFO("New time2: {}", ntp.c_str());
                    /* Modified line */
                    line = std::regex_replace(line, std::regex(slist[1].c_str()), ntp.c_str());
                }
            }
            line = std::regex_replace(line, std::regex("="), " = ");
            dst_file << line << "\n";
        }
        retVal = true;
    }
    else {
        SPDLOG_INFO("{}", "Cannot open File");
    }
    if (src_file.is_open())
        src_file.close();

    if (dst_file.is_open())
        dst_file.close();

    if (retVal == true) {
        int value = 0;
        value     = remove(NTP_CONF_FILE_PATH);

        if (!value) {
            SPDLOG_INFO("{}", "File rm successfully");
        }
        else {
            SPDLOG_ERROR("{}", "File mv failed");
        }
        value = rename(NTP__TMP_CONF_FILE_PATH, NTP_CONF_FILE_PATH);
        // Print the result
        if (!value) {
            SPDLOG_INFO("{}", "File rn successfully");
        }
        else {
            SPDLOG_ERROR("{}", "File rn failed");
        }
    }

    return retVal;
}

bool NvmIf::updateReconnectParam(std::string set_string, uint8_t index)
{
    SPDLOG_INFO("{}", "updateReconnectParam");
    bool retVal{false};
    if (set_string.empty()) {
        SPDLOG_INFO("{}", "Invalid param");
        return retVal;
    }

    std::string origin_str = set_string;

    std::string src_file_path(RECONNECT_CONF_FILE_PATH);
    std::string dst_file_path(RECONNECT__TMP_CONF_FILE_PATH);
    std::ifstream src_file(src_file_path);
    std::ofstream dst_file(dst_file_path);
    std::string line;

    if (src_file && dst_file) {
        while (std::getline(src_file, line)) {
            line.erase(remove(line.begin(), line.end(), ' '), line.end());

            std::vector<std::string> slist = splitString(line, '=');
            if (index == 0) {
                if (slist[0].compare(std::string("retryBackOffWaitMinimum")) == 0) {
                    SPDLOG_INFO("Current retryBackOffWaitMinimum: {}", slist[1].c_str());
                    SPDLOG_INFO("New retryBackOffWaitMinimum: {}", set_string.c_str());
                    std::lock_guard<std::mutex> lock(m_groupSetReconnectParam_mtx);
                    m_groupSetReconnectParam.push(
                        std::make_shared<GroupSetReconnectParam>(atoi(set_string.c_str()), RETRY_BACKOFF_WAIT_MINIMUM));
                    /* Modified line */
                    line = std::regex_replace(line, std::regex(slist[1].c_str()), set_string.c_str());
                }
            }
            else if (index == 1) {
                if (slist[0].compare(std::string("retryBackOffRepeatTimes")) == 0) {
                    SPDLOG_INFO("Current retryBackOffRepeatTimes: {}", slist[1].c_str());
                    SPDLOG_INFO("New retryBackOffRepeatTimes: {}", set_string.c_str());
                    std::lock_guard<std::mutex> lock(m_groupSetReconnectParam_mtx);
                    m_groupSetReconnectParam.push(
                        std::make_shared<GroupSetReconnectParam>(atoi(set_string.c_str()), RETRY_BACKOFF_REPEAT_TIMES));
                    /* Modified line */
                    line = std::regex_replace(line, std::regex(slist[1].c_str()), set_string.c_str());
                }
            }
            else if (index == 2) {
                if (slist[0].compare(std::string("retryBackOffRandomRange")) == 0) {
                    SPDLOG_INFO("Current retryBackOffRandomRange: {}", slist[1].c_str());
                    SPDLOG_INFO("New retryBackOffRandomRange: {}", set_string.c_str());
                    std::lock_guard<std::mutex> lock(m_groupSetReconnectParam_mtx);
                    m_groupSetReconnectParam.push(
                        std::make_shared<GroupSetReconnectParam>(atoi(set_string.c_str()), RETRY_BACKOFF_RANDOM_RANGE));
                    /* Modified line */
                    line = std::regex_replace(line, std::regex(slist[1].c_str()), set_string.c_str());
                }
            }
            line = std::regex_replace(line, std::regex("="), " = ");
            dst_file << line << "\n";
        }
        retVal = true;
    }
    else {
        SPDLOG_INFO("{}", "Cannot open File");
    }
    if (src_file.is_open())
        src_file.close();

    if (dst_file.is_open())
        dst_file.close();

    if (retVal == true) {
        int value = 0;
        value     = remove(RECONNECT_CONF_FILE_PATH);

        if (!value) {
            SPDLOG_INFO("{}", "File rm successfully");
        }
        else {
            SPDLOG_ERROR("{}", "File mv failed");
        }
        value = rename(RECONNECT__TMP_CONF_FILE_PATH, RECONNECT_CONF_FILE_PATH);
        // Print the result
        if (!value) {
            SPDLOG_INFO("{}", "File rn successfully");
        }
        else {
            SPDLOG_ERROR("{}", "File rn failed");
        }
    }

    return retVal;
}

bool NvmIf::groupParamSetting(GroupSetReconnectParam& param)
{
    bool result = false;
    /** Check group queue to sync setting */
    auto reconnect_param = GroupSetReconnectParam(0, 0);
    while (m_groupSetReconnectParam.empty() != true) {
        std::lock_guard<std::mutex> lock(m_groupSetReconnectParam_mtx);
        auto set_param = m_groupSetReconnectParam.front();
        SPDLOG_INFO("option {} with retryBackOffRandomRange: {}", set_param->mOptions,
                    set_param->mParam.retryBackOffRandomRange);
        SPDLOG_INFO("option {} with retryBackOffRepeatTimes: {}", set_param->mOptions,
                    set_param->mParam.retryBackOffRepeatTimes);
        SPDLOG_INFO("option {} with retryBackOffWaitMinimum: {}", set_param->mOptions,
                    set_param->mParam.retryBackOffWaitMinimum);

        reconnect_param.mOptions |= set_param->mOptions;
        if (set_param->mOptions == RETRY_BACKOFF_WAIT_MINIMUM) {
            reconnect_param.mParam.retryBackOffWaitMinimum = set_param->mParam.retryBackOffWaitMinimum;
        }
        else if (set_param->mOptions == RETRY_BACKOFF_REPEAT_TIMES) {
            reconnect_param.mParam.retryBackOffRepeatTimes = set_param->mParam.retryBackOffRepeatTimes;
        }
        else if (set_param->mOptions == RETRY_BACKOFF_RANDOM_RANGE) {
            reconnect_param.mParam.retryBackOffRandomRange = set_param->mParam.retryBackOffRandomRange;
        }
        m_groupSetReconnectParam.pop();
    }
    SPDLOG_INFO("All setting:\n- option: {}\n- retryBackOffRandomRange: {}\n- retryBackOffRepeatTimes: {}\n- "
                "retryBackOffWaitMinimum: {}",
                reconnect_param.mOptions, reconnect_param.mParam.retryBackOffRandomRange,
                reconnect_param.mParam.retryBackOffRepeatTimes, reconnect_param.mParam.retryBackOffWaitMinimum);

    if (reconnect_param.mOptions
        == (RETRY_BACKOFF_WAIT_MINIMUM | RETRY_BACKOFF_REPEAT_TIMES | RETRY_BACKOFF_RANDOM_RANGE)) {
        result = true;
        param = reconnect_param;
    }
    return result;
}
} // namespace rb::nvm