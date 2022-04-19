/**
 * @file AppItemData.h
 * @author Steven Le (sonlq@vingroup.net)
 * @brief
 * @version 0.1
 * @date 2021-11-13
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <cstring>
#include <string>
#include <vector>

namespace rb {
class AppItemData {
public:
    enum AppSignalType {
        kSysMessageAppStart = 0,
        kSysMsgServerConnected,
        kSysMsgServerDisconnected,
        kSysMsgWokingModeSignal,
        kSysMsgOpModeChanged,
        kSysMsgCsrPrepare,
        kSysMsgCertVerify,
        kSysMessageMax
    };
    AppItemData() = default;
    explicit AppItemData(AppSignalType signal) : m_signal(signal) {}

    AppSignalType signal() const { return m_signal; }

private:
    AppSignalType m_signal;
};
} // namespace rb