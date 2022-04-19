/****************************************************
 *  cancomm_if.h
 *  Created on: 03-Jun-2020 9:41:55 AM
 *  Implementation of the Interface cancomm
 *  Original author: duanlv
 ****************************************************/

#ifndef _CANCOMM_IF_H_
#define _CANCOMM_IF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cancomm_types.h"

cancomm_err_t cancomm_init(cancomm_connect_cb_t connect_cb, void* connect_ctx);
cancomm_err_t cancomm_free(void);
cancomm_err_t cancomm_register_event(cancomm_event_t event, cancomm_event_cb_t event_cb, void* event_ctx);
cancomm_err_t cancomm_unregister_event(cancomm_event_t event);

cancomm_err_t cancomm_set_rectifier_output(uint8_t rec_id, uint32_t req_volt, uint32_t req_curr);
cancomm_err_t cancomm_notify_rectifier_output(uint8_t rec_id);
cancomm_err_t cancomm_set_fast_charge_state(cancomm_fast_charge_t fast_charge);
cancomm_err_t cancomm_set_charger_state(uint8_t gun_id, uint8_t state);
cancomm_err_t cancomm_set_comm_req(cancomm_nodes_t node, bool is_enable);

cancomm_err_t cancomm_get_fan_info(cancomm_fan_info_t* fan_info);
cancomm_err_t cancomm_get_temp_info(cancomm_temp_info_t* temp_info);
cancomm_err_t cancomm_get_fan_manufacture_infor(cancomm_board_manufacture_info_t* fan_version);
cancomm_err_t cancomm_get_hv_manufacture_infor(cancomm_board_manufacture_info_t* hv_version);
cancomm_err_t cancomm_get_cp_manufacture_infor(cancomm_board_manufacture_info_t *cp_version, uint8_t idx);
cancomm_err_t cancomm_get_ext_manufacture_infor(cancomm_board_manufacture_info_t *ext_version);

/* get error code */
cancomm_err_t cancomm_get_fan_error_code(FanErrorCode_t* fan_error);
cancomm_err_t cancomm_get_hv_error_code(HVErrorCode_t* hv_error);
cancomm_err_t cancomm_get_hv_output_error_code(HVOutputErrorCode_t* hv_output_error, uint8_t idx);
cancomm_err_t cancomm_get_rect_error_code(RectErrorCode_t* rect_error, uint8_t idx);

/* get selftest info*/
cancomm_err_t cancomm_get_hv_selftest_info(cancomm_hv_selftest_state_t* hv_self_test);
cancomm_err_t cancomm_set_hv_system_state(uint8_t system_state, uint8_t v2g0_state, uint8_t v2g1_state);

/* set charger mode */
cancomm_err_t cancomm_set_charger_mode_30k60k(uint32_t charger_mode);
cancomm_err_t cancomm_set_group_mode(uint8_t group_id, uint8_t rec_id);

cancomm_err_t cancomm_set_system_reboot(void);
cancomm_err_t cancomm_set_ac_state(bool is_on);
cancomm_err_t cancomm_set_ev_max_volt(uint8_t gun_id, uint16_t volt);

#ifdef __cplusplus
}
#endif

#endif // _CANCOMM_IF_H_
