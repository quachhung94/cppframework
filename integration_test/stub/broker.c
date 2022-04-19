#include <stdint.h>

#include "libbroker.h"
#include "libbroker_messages.h"

int32_t Libbroker_Start(BrokerItf* itf, BrokerConnectStatusCallback callback_func, void* callback_arg)
{
    (void)itf;
    (void)callback_func;
    (void)callback_arg;
    return 0;
}

void Libbroker_GetDefaultConfig(BrokerConfig* config) { (void)config; }

BrokerItf* Libbroker_Init(const char* node_id, BrokerConfig* config)
{
    (void)node_id;
    (void)config;
    return 0;
}

int32_t Libbroker_Publish(BrokerItf* itf, BrokerTopics topic, void* message, uint32_t message_len, int32_t qos,
                          BrokerPublishCallback callback_func, void* callback_arg)
{
    (void)itf;
    (void)topic;
    (void)message;
    (void)message_len;
    (void)qos;
    (void)callback_func;
    (void)callback_arg;
    return 0;
}

int32_t Libbroker_SetPostDetailResult(void* output_message, uint32_t message_len, PostDetailResult_t* info)
{
    (void)output_message;
    (void)message_len;
    (void)info;
    return 0;
}

int32_t Libbroker_Subscribe(BrokerItf* itf, BrokerTopics topic, uint8_t qos,
                            BrokerSubscribeCallback subscrible_callback_func,
                            BrokerReceiveCallback receive_callback_func, void* callback_arg)
{
    (void)itf;
    (void)topic;
    (void)qos;
    (void)subscrible_callback_func;
    (void)receive_callback_func;
    (void)callback_arg;
    return 0;
}

int32_t Libbroker_SetErrorCode(void* output_message, uint32_t message_len, uint32_t error_code)
{
    (void)output_message;
    (void)message_len;
    (void)error_code;
    return 0;
}

int32_t Libbroker_SetIconStatus(void* output_message, uint32_t message_len, bool is_active)
{
    (void)output_message;
    (void)message_len;
    (void)is_active;
    return 0;
}

int32_t Libbroker_GetErrorCode(void* input_message, uint32_t message_len, uint32_t* error_code) {}