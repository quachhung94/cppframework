/****************************************************
 *  cancomm_types.h
 *  Created on: 03-Jun-2020 10:36:24 AM
 *  Implementation of the Enumeration cancomm_status_t
 *  Original author: duanlv
 ****************************************************/

#ifndef _CANCOMM_TYPES_H_
#define _CANCOMM_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#define CANCOMM_REC_NUM							2
#define CANCOMM_FAN_NUM							8
#define CANCOMM_TEMP_NUM						3
#define CANCOMM_BOARD_INFO_MAX                  128
// Cancomm error enumeration
typedef enum {
	CANCOMM_ERR_NONE = 0,
	CANCOMM_ERR_NOT_INITIALIZED,
	CANCOMM_ERR_ALREADY_INITIALIZED,
	CANCOMM_ERR_NOT_CONNECTED,
	CANCOMM_ERR_MALLOC_FAILED,
	CANCOMM_ERR_INVALID_PARAM,
	CANCOMM_ERR_SEND_REQ_FAILED,
	CANCOMM_ERR_INVALID_RECEIVED_CAN_MSG,
	CANCOMM_ERR_SEND_CAN_MSG_FAILED,
	CANCOMM_ERR_TIMED_OUT,
	CANCOMM_ERR_NO_UPDATE,
	CANCOMM_ERR_UNKNOWN,
	CANCOMM_ERR_MAX
} cancomm_err_t;

// Cancomm event enumeration
typedef enum {
	CANCOMM_EVENT_REC0_OUTPUT = 0,
	CANCOMM_EVENT_REC0_ERROR,
	CANCOMM_EVENT_REC0_WARN,
	CANCOMM_EVENT_REC0_INFO,
	CANCOMM_EVENT_REC1_OUTPUT,
	CANCOMM_EVENT_REC1_ERROR,
	CANCOMM_EVENT_REC1_WARN,
	CANCOMM_EVENT_REC1_INFO,
	CANCOMM_EVENT_FAN_FAILDEM,
	CANCOMM_EVENT_FAN_TEMP_FAILDEM,
	CANCOMM_EVENT_OUTPUT0_FAN_FAILDEM,
	CANCOMM_EVENT_OUTPUT1_FAN_FAILDEM,
	CANCOMM_EVENT_OUTPUT0_COOLING_DONE,
	CANCOMM_EVENT_OUTPUT1_COOLING_DONE,
	CANCOMM_EVENT_OUTPUT0_STATE,
	CANCOMM_EVENT_OUTPUT1_STATE,
	CANCOMM_EVENT_HV_COMMON_ALERT,
	CANCOMM_EVENT_OUTPUT0_ALERT,
	CANCOMM_EVENT_OUTPUT1_ALERT,
	CANCOMM_EVENT_OUTPUT0_VOLTAGE,
	CANCOMM_EVENT_OUTPUT1_VOLTAGE,
	CANCOMM_EVENT_OUTPUT0_ISO_STATUS,
	CANCOMM_EVENT_OUTPUT1_ISO_STATUS,
	CANCOMM_EVENT_OUTPUT0_RELAY_STATUS,
	CANCOMM_EVENT_OUTPUT1_RELAY_STATUS,
	CANCOMM_EVENT_BUS_STATUS,
	CANCOMM_EVENT_FAN_ERROR_CODE,
	CANCOMM_EVENT_HV_ERROR_CODE,
	CANCOMM_EVENT_HV_OUTPUT0_ERROR_CODE,
	CANCOMM_EVENT_HV_OUTPUT1_ERROR_CODE,
	CANCOMM_EVENT_REC0_ERROR_CODE,
	CANCOMM_EVENT_REC1_ERROR_CODE,
	CANCOMM_EVENT_REC0_GROUP_INFO,
	CANCOMM_EVENT_REC1_GROUP_INFO,
	CANCOMM_EVENT_HV_CHARGER_MODE,
	CANCOMM_EVENT_SUPER_HIGH_VOLT_ALERT,
	CANCOMM_EVENT_NODE_COMM_LOST,
	CANCOMM_EVENT_ALL
} cancomm_event_t;

// Callback prototypes
typedef void (*cancomm_connect_cb_t)(bool is_connected, void* context);
typedef void (*cancomm_event_cb_t)  (cancomm_event_t event, void* data, void* context);

#define CANPRD_MAX_CHECK (8U)

typedef enum
{
	FAN_MODULE = 0,
	HV_MODULE,
	EXT_MODULE,
	CP0_MODULE,
	CP1_MODULE,	
	RECT0_MODULE,
	RECT1_MODULE,
	NUMBER_OF_CAN_MODULE,
} cancomm_module_t;

typedef enum
{    
	CAN_LOST_CONNECT = 0U,
	CAN_CONNECTED = 1U,
} cancomm_connection_status_t;


typedef struct {
	uint8_t major;
	uint8_t minor;
	uint8_t subminor;
} cancomm_version_t;

typedef struct {
	uint32_t current;
	uint32_t voltage;
} cancomm_rec_output_t;

typedef struct {
	uint8_t data[CANCOMM_FAN_NUM];
} cancomm_fan_faildem_t;

typedef struct {
	uint8_t duty [CANCOMM_FAN_NUM];
	uint8_t speed[CANCOMM_FAN_NUM];
} cancomm_fan_info_t;

typedef struct {
	uint8_t temp[CANCOMM_TEMP_NUM];
} cancomm_temp_info_t;

typedef struct {
	bool is_error;
} cancomm_fan_system_faildem_t;

typedef struct {
	uint8_t all_fans;
	uint8_t all_temps;
	uint8_t over_temp;
} cancomm_fan_system_faildem_detail_t;

typedef enum {
	HV_STATE_IDLE = 0,
	HV_STATE_PRE_CHARGE,
	HV_STATE_CHARGING,
	HV_STATE_EMERGENCY,
	HV_STATE_MAX,
} cancomm_output_state_t;

typedef enum
{
	HV_SELTEST_OK = 0,
	HV_SELTEST_NG = 1,
	HV_SELTEST_PROCESSING = 2,
} cancomm_hv_selftest_state_t;

typedef struct {
	bool is_alert;
} cancomm_hv_alert_t;

typedef struct {
	uint8_t input_over_voltage;
	uint8_t input_under_voltage;
	bool 	overheat;
	bool 	fast_charge_pre_relay_fail;
	bool 	fast_charge_hv_relay_fail;
	bool 	fast_charge_lv_relay_fail;
} cancomm_hv_alert_detail_t;

typedef struct {
	bool is_alert;
} cancomm_output_alert_t;

typedef struct {
	bool over_voltage;
	bool under_voltage;
	bool abnormal_voltage;
	bool isolator_p_error;
	bool isolator_n_error;
	bool pre_relay_fail;
	bool hv_relay_fail;
	bool lv_relay_fail;
} cancomm_output_alert_detail_t;

typedef enum {
	HV_ISO_INVALID = 0,
	HV_ISO_VALID,	
	HV_ISO_WARNING,
	HV_ISO_FAULT,
	HV_ISO_MAX
} cancomm_iso_status_t;

typedef struct {
	bool main_relay;
	bool precharge_relay;
} cancomm_output_relay_t;

typedef struct {
	bool is_error;
} cancomm_rec_error_t;

typedef struct {
	bool mdl_id_repetition;
	bool input_over_voltage;
	bool input_under_voltage;
	bool input_unbalance;
	bool input_phase_lost;
	bool load_unsharing;
	bool comm_interrupt;
	bool output_over_voltage;
	bool over_temp;
	bool mdl_protect;
	bool mdl_fault;
	bool discharge_abnormal;
	bool pfc_side_abnormal;
	bool inner_comm_interrupt;
	bool output_short;
	bool mdl_pfc_side_off;
} cancomm_rec_error_detail_t;

typedef struct {
	bool fan_fault;
	bool power_limit;
} cancomm_rec_warn_t;

typedef struct {
	bool walk_in_enable;
	bool mdl_off_state;
} cancomm_rec_info_t;

typedef enum {
	FAST_CHARGE_OFF = 0x00,
	FAST_CHARGE_LV  = 0x01,
	FAST_CHARGE_HV  = 0x03,
} cancomm_fast_charge_t;

typedef enum {
	CANCOMM_NODE_FAN  = 0x01,
	CANCOMM_NODE_HV	  = 0x02,
	CANCOMM_NODE_EXT  = 0x04,
	CANCOMM_NODE_PLC0 = 0x08,
	CANCOMM_NODE_PLC1 = 0x10,
	CANCOMM_NODE_ALL  = 0xFF,
	CANCOMM_NODE_REC0,
	CANCOMM_NODE_REC1,
} cancomm_nodes_t;

typedef enum {
	FAN_COOLING = 0,
	FAN_COOLING_DONE,
	FAN_COOLING_MAX
} cancomm_fan_cooling_t;

typedef union {
struct __attribute__((__packed__)) {
	bool input_over_voltage : 1;
	bool input_under_voltage : 1;
	bool output_over_voltage : 1;
	bool overload : 1;
	bool output_short : 1;
	bool input_unbalance : 1;
	bool input_phase_lost : 1;
	bool power_limit : 1;
	bool fan_fault : 1;
	bool discharge_abnormal : 1;
	bool inner_comm_interrupt : 1;
	bool over_temp : 1;
	bool mdl_protect : 1;
	bool mdl_fault : 1;
	bool can_connection:1;
	uint32_t reserved : 17;
	} fields;
	uint32_t value;
} RectErrorCode_t;    

typedef union {
	struct __attribute__((__packed__)) {	
	bool lv_relay_error : 1;
	bool hv_relay_error : 1;
	bool pre_relay_error: 1;
	bool dc_over_voltage : 1;
	bool dc_under_voltage : 1;
	bool dc_abnormal_voltage : 1;
	bool fail_resistance_vplus : 1;
	bool fail_resistance_vminus : 1;
	uint32_t reserverd : 24;
	} fields;
	uint32_t value;
} HVOutputErrorCode_t;


typedef union {
	struct __attribute__((__packed__)) {	
	bool lv_relay_error:1;
	bool hv_relay_error:1;
	bool pre_relay_error:1;
	bool no_memory : 1;
	bool ac_over_voltage : 1;
	bool ac_under_voltage : 1;		
	bool can_connection:1;
	bool ac_relay_error:1;
	uint32_t reserverd : 24;
	} fields;
	uint32_t value;
} HVErrorCode_t;

typedef union {
struct __attribute__((__packed__)) {
	bool fan1_failed : 1;
	bool fan2_failed : 1;
	bool fan3_failed : 1;
	bool fan4_failed : 1;
	bool fan5_failed : 1;
	bool fan6_failed : 1;
	bool fan7_failed : 1;
	bool fan8_failed : 1;
	bool temp_sensor0_failed : 1;
	bool temp_sensor1_failed : 1;
	bool temp_sensor2_failed : 1;
	bool output0_all_temps_failed : 1;
	bool output0_all_fans_failed : 1;
	bool output0_over_temp : 1;
	bool output1_all_temps_failed : 1;
	bool output1_all_fans_failed : 1;
	bool output1_over_temp : 1;
	bool can_connection:1;
	uint32_t reserverd : 14;
	} fields;
	uint32_t value;
} FanErrorCode_t;

typedef struct _cancomm_board_manufacture_info_t_ {
 char app_version[CANCOMM_BOARD_INFO_MAX];
 char boot_version[CANCOMM_BOARD_INFO_MAX];
 char hw_version[CANCOMM_BOARD_INFO_MAX];
 char serial_no[CANCOMM_BOARD_INFO_MAX];
} cancomm_board_manufacture_info_t;

typedef struct _cancomm_rec_group_info_t_ {
	uint32_t rec_group_confirm;
} cancomm_rec_group_info_t;

typedef struct _cancomm_hv_charger_mode_t_ {
	uint32_t hv_charger_mode;
} cancomm_hv_charger_mode_t;

typedef struct {
	bool is_alert;
} cancomm_super_high_volt_t;

#ifdef __cplusplus
}
#endif

#endif // _CANCOMM_TYPES_H_
