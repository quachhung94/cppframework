
#ifndef _LIBBROKER_H_
#define _LIBBROKER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "libbroker_topics.h"

/**
 * 
 */
typedef struct {
    int32_t  protocol_version;
    uint32_t max_inflight_message;
    char*    host;
    uint32_t port;
    uint32_t keep_alive;

    uint32_t max_topic;
    uint32_t max_queued_message;
    uint32_t periodic_interval;
} BrokerConfig;

typedef struct broker_interface BrokerItf;

typedef void (*BrokerConnectStatusCallback)(bool is_connected, void* ex_arg);
typedef void (*BrokerSubscribeCallback)(BrokerTopics topic, bool is_subscribled, void* ex_arg);
typedef void (*BrokerReceiveCallback)(BrokerTopics topic, void* message, uint32_t message_len, void* ex_arg);
typedef void (*BrokerPublishCallback)(int32_t mid, void* ex_arg);

void Libbroker_GetDefaultConfig(BrokerConfig* config);

BrokerItf* Libbroker_Init(const char* node_id, BrokerConfig* config);

int32_t Libbroker_Start(BrokerItf* itf, BrokerConnectStatusCallback callback_func, void* callback_arg);

int32_t Libbroker_Disconnect(BrokerItf* itf);

int32_t Libbroker_Subscribe(BrokerItf*              itf,
                            BrokerTopics            topic,
                            uint8_t                 qos,
                            BrokerSubscribeCallback subscrible_callback_func,
                            BrokerReceiveCallback   receive_callback_func,
                            void*                   callback_arg);

int32_t Libbroker_Unsubscribe(BrokerItf* itf, const char* topic, int32_t id);

int32_t Libbroker_Publish(BrokerItf*            itf,
                          BrokerTopics          topic,
                          void*                 message,
                          uint32_t              message_len,
                          int32_t               qos,
                          BrokerPublishCallback callback_func,
                          void*                 callback_arg);

bool Libbroker_IsRunning(BrokerItf* itf);

#ifdef __cplusplus
}
#endif

#endif // _LIBBROKER_H_
