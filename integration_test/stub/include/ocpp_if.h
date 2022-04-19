/****************************************************
 *  ocpp_if.h
 *  Created on: 19-Jun-2020 9:41:55 AM
 *  Implementation of the Interface ocpp
 *  Original author: sonlq
 ****************************************************/

#if !defined(_OCPP_IF_H_)
#define _OCPP_IF_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "ocpp_types.h"
// #include "ocpp_types_internal.h"

typedef void (*ocpp_connect_cb_t)(bool is_connected, void* context);
typedef void (*ocpp_callback_handler_t)(ocpp_event_t event, uint8_t* buffer, size_t len, void* user_data);

ocpp_status_t ocpp_init(ocpp_connect_cb_t connect_cb, void* connect_ctx);
ocpp_status_t ocpp_register_event(ocpp_event_t event, ocpp_func_ptr_t func_ptr, void* context);
ocpp_status_t ocpp_intro_message_to_service(int32_t *events, size_t eventNo);
ocpp_status_t ocpp_alert_message_to_service(uint32_t len, uint8_t* p_data);
ocpp_status_t ocpp_info_message_to_service(message_type_id cmd, bool bsync, uint32_t len, uint8_t* p_data);
ocpp_status_t ocpp_config_message_to_service(config_type_id cmd, uint8_t* p_data, size_t len);
ocpp_status_t ocpp_set_reconnect_pararm(reconnect_param param, uint32_t options);
void ocpp_deinit(void);

#ifdef __cplusplus
}
#endif

#endif /*!defined(_OCPP_IF_H_)*/
