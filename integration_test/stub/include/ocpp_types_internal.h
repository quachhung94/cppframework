/****************************************************
 *  ocpp_types_internal.h
 *  Created on: 19-Jun-2020 10:41:31 AM
 *  Implementation of the Enumeration ocpp_error_t
 *  Original author: sonlq
 ****************************************************/

#if !defined(_OCPP_TYPES_INTERNAL_H_)
#define _OCPP_TYPES_INTERNAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#define OCPP_SOCKET_PORT 5354

typedef enum _OCPP_ERROR_T_ {
    E_OCPP_NO_ERROR = 0,
    E_OCPP_ERROR,
    E_OCPP_INVALID_PARAM,
    E_OCPP_INIT_ERROR,
    E_OCPP_SEND_ERROR,
    E_OCPP_RECV_ERROR,
    E_OCPP_UNKNOWN_ERROR
} ocpp_error_t;

typedef enum _OCPP_MESSAGE_DIRECTION_T_ {
    REQ_FROM_CS_TO_SERVER = 0,
    RES_FROM_SERVER_TO_CS,
    REQ_FROM_SERVER_TO_CS,
    RES_FROM_CS_TO_SERVER
} ocpp_message_dir_t;

typedef enum _OCPP_METHOD_TYPE_ {
    RPC_INFO_MESSAGE_REQ = 0,
    RPC_ALERT_MESSAGE_REQ,
    RPC_INTRO_MESSAGE_REQ,
    RPC_CONFIG_MESSAGE_REQ,
    RPC_OCPP_METHOD_REQ_MAX
} ocpp_method_type;

typedef enum _RESP_OCPP_METHOD_TYPE_ {
    RPC_INFO_MESSAGE_ACK = 0,
    RPC_ALERT_MESSAGE_ACK,
    RPC_INTRO_MESSAGE_ACK,
    RPC_CONFIG_MESSAGE_ACK,
    RPC_OCPP_METHOD_RES_MAX
} ocpp_method_resp_type;
#ifdef __cplusplus
}
#endif

#endif /*!defined(_OCPP_TYPES_INTERNAL_H_)*/
