/**
 * @file OcppItemData.h
 * @author Steven Le (sonlq@vingroup.net)
 * @brief
 * @version 0.1
 * @date 2021-11-16
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <cstring>
#include <string>
#include <vector>
namespace rb::ocpp {
class OcppItemData {
public:
    enum OcppEventType { kOcppEventToServer = 0, kOcppEventFromServer, kOcppEventMax };
    OcppItemData() = default;
    explicit OcppItemData(uint32_t type, OcppEventType dir, std::string payload)
        : m_type(type), m_dir(dir), m_payload(payload), isCallError(false)
    {
    }

    uint32_t type() { return m_type; }
    OcppEventType dir() { return m_dir; }
    const std::string payload() const { return m_payload; }
    bool callError() { return isCallError; }
    void setCallError(bool isError) { isCallError = isError; }

private:
    uint32_t m_type;
    OcppEventType m_dir;
    std::string m_payload;
    bool isCallError;
};
} // namespace rb::ocpp