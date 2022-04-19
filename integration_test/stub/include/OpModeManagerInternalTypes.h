#if !defined(_OP_MODE_MANAGER_INTTERNAL_TYPES_H_)
#define _OP_MODE_MANAGER_INTTERNAL_TYPES_H_

#include "OpModeManagerTypes.h"

namespace OpModeManager {
    typedef enum {
        RPC_ID_REGISTER_RECEIVER = 0,
        RPC_ID_UNREGISTER_RECEIVER,
        RPC_ID_SET_MODE,
        RPC_ID_SET_EXT_EVENT,
        RPC_ID_GET_MODE,
        RPC_ID_MODE_CHANGE_NTFY,
        RPC_ID_REBOOT_REQUEST_NTFY,
        RPC_ID_START_DIAG_NTFY,
        RPC_ID_START_LOCAL_DFU_NTFY,
        RPC_ID_START_OTA_DFU_NTFY,
        RPC_ID_INACTIVATED_NTFY,
        RPC_ID_ACCTIVATE_SOURCE_NTFY,
        RPC_ID_FORCE_IDLE_NTFY,
        REQ_ID_MAX
    } OpModeRpcCmdIdType;

    //    typedef enum { RESP_ID_MODE_CHANGE = 0, RESP_ID_MODE_CONF, RESP_ID_MAX } OpModeRespIdType;
    typedef enum { 
        EVENT_TYPE_MODE_CHANGED = 0,
        EVENT_TYPE_MODE_CNF,
        EVENT_TYPE_REBOOT_REQUEST,
        EVENT_TYPE_START_DIAG,
        EVENT_TYPE_START_LOCAL_DFU,
        EVENT_TYPE_START_OTA_DFU,
        EVENT_TYPE_INACTIVATED,
        EVENT_TYPE_ACTIVATE_SOURCE,
        EVENT_TYPE_FORCE_IDLE,
        EVENT_TYPE_MAX
    } OpModeEventType;

    struct OpModeNtfyData {
        OperationModeType currMode;
        OperationModeType prevMode;
    };

    enum ExternalEvents {
        EXT_EVENT_POST_RESULT = 0,
        EXT_EVENT_ACTIVATED_STATUS,
        EXT_EVENT_EV_CONNECT_STATUS,
        EXT_EVENT_DIAG_REQUEST,
        EXT_EVENT_LOCAL_DFU_REQUEST,
        EXT_EVENT_OTA_DFU_REQUEST,
        EXT_EVENT_EMERGENCY_STATUS,
        EXT_EVENT_REBOOT_REQUEST,
        EXT_EVENT_MAX
    };

} // namespace OpModeManager

#endif // defined(_OP_MODE_MANAGER_INTTERNAL_TYPES_H_)
