
#include "cancomm_types.h"

cancomm_err_t cancomm_init(cancomm_connect_cb_t connect_cb, void* connect_ctx)
{
    (void)connect_cb;
    (void)connect_ctx;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_free(void) { return CANCOMM_ERR_NONE; }
cancomm_err_t cancomm_register_event(cancomm_event_t event, cancomm_event_cb_t event_cb, void* event_ctx)
{
    (void)event;
    (void)event_cb;
    (void)event_ctx;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_unregister_event(cancomm_event_t event)
{
    (void)event;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_set_rectifier_output(uint8_t rec_id, uint32_t req_volt, uint32_t req_curr)
{
    (void)rec_id;
    (void)req_volt;
    (void)req_curr;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_notify_rectifier_output(uint8_t rec_id)
{
    (void)rec_id;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_set_fast_charge_state(cancomm_fast_charge_t fast_charge)
{
    (void)fast_charge;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_set_charger_state(uint8_t gun_id, uint8_t state)
{
    (void)gun_id;
    (void)state;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_set_comm_req(cancomm_nodes_t node, bool is_enable)
{
    (void)node;
    (void)is_enable;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_get_fan_info(cancomm_fan_info_t* fan_info)
{
    (void)fan_info;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_get_temp_info(cancomm_temp_info_t* temp_info)
{
    (void)temp_info;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_get_fan_manufacture_infor(cancomm_board_manufacture_info_t* fan_version)
{
    (void)fan_version;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_get_hv_manufacture_infor(cancomm_board_manufacture_info_t* hv_version)
{
    (void)hv_version;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_get_cp_manufacture_infor(cancomm_board_manufacture_info_t* cp_version, uint8_t idx)
{
    (void)cp_version;
    (void)idx;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_get_ext_manufacture_infor(cancomm_board_manufacture_info_t* ext_version)
{
    (void)ext_version;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_get_fan_error_code(FanErrorCode_t* fan_error)
{
    (void)fan_error;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_get_hv_error_code(HVErrorCode_t* hv_error)
{
    (void)hv_error;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_get_hv_output_error_code(HVOutputErrorCode_t* hv_output_error, uint8_t idx)
{
    (void)hv_output_error;
    (void)idx;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_get_rect_error_code(RectErrorCode_t* rect_error, uint8_t idx)
{
    (void)rect_error;
    (void)idx;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_get_hv_selftest_info(cancomm_hv_selftest_state_t* hv_self_test)
{
    (void)hv_self_test;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_set_hv_system_state(uint8_t system_state, uint8_t v2g0_state, uint8_t v2g1_state)
{
    (void)system_state;
    (void)v2g0_state;
    (void)v2g1_state;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_set_charger_mode_30k60k(uint32_t charger_mode)
{
    (void)charger_mode;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_set_group_mode(uint8_t group_id, uint8_t rec_id)
{
    (void)group_id;
    (void)rec_id;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_set_system_reboot(void) { return CANCOMM_ERR_NONE; }
cancomm_err_t cancomm_set_ac_state(bool is_on)
{
    (void)is_on;
    return CANCOMM_ERR_NONE;
}
cancomm_err_t cancomm_set_ev_max_volt(uint8_t gun_id, uint16_t volt)
{
    (void)gun_id;
    (void)volt;
    return CANCOMM_ERR_NONE;
}