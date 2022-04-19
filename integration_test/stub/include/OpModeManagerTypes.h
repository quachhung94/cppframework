#if !defined(_OP_MODE_MANAGER_TYPES_H_)
#define _OP_MODE_MANAGER_TYPES_H_

namespace OpModeManager {

#define E_OK (int32_t)(0)
#define E_NG (int32_t)(-1)
#define E_INVALID_PARAM (int32_t)(-2)
#define E_TIMEOUT (int32_t)(-3)

    enum OperationModeType {
        INVALID_MODE = 0,
        POST_MODE,
        INACTIVATED_MODE,
        IDLE_MODE,
        CHARGING_MODE,
        EMERGENCY_MODE,
        MAINTENANCE_MODE,
        OP_MODE_MAX
    };

    enum PostResults {
        POST_RESULT_NG = 0,
        POST_RESULT_OK,
        POST_RESULT_MAX
    };

    enum ActivatedStatus {
        ACTIVATE_STATUS_STARTED = 0,
        ACTIVATE_STATUS_INACTIVATED,
        ACTIVATE_STATUS_ACTIVATED_ONLINE,
        ACTIVATE_STATUS_ACTIVATED_OFFLINE,
        ACTIVATE_STATUS_MAX,
    };

    enum EvConnectStatus {
        EV_STATUS_DISCONNECTED = 0,
        EV_STATUS_CONNECTED,
        EV_STATUS_MAX,
    };

    enum DiagRequests {
        DIAG_REQ_ENTRY = 0,
        DIAG_REQ_EXIT,
        DIAG_REQ_MAX
    };

    enum DfuRequests {
        DFU_REQ_ENTRY = 0,
        DFU_REQ_EXIT,
        DFU_REQ_MAX,
    };

    enum EmgStatus {
        EMG_STATUS_OFF = 0,
        EMG_STATUS_ON,
        EMG_STATUS_MAX,
    };

    enum RebootRequests {
        REBOOT_REQ_ON_IDLE = 0,
        REBOOT_REQ_IMMEDIATE,
        REBOOT_REQ_MAX,
    };

} // namespace OpModeManager

#endif // defined(_OP_MODE_MANAGER_TYPES_H_)
