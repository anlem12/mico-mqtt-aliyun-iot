/**
 * @file mqtt_config.h
 * @brief MQTT specific configuration file
 */

#ifndef MQTT_CONFIG_H_
#define MQTT_CONFIG_H_

// MQTT pub and sub buff len
#define MQTT_TX_BUF_LEN                     (2048+200) ///< Any time a message is sent out through the MQTT layer. The message is copied into this buffer anytime a publish is done. This will also be used in the case of Thing Shadow
#define MQTT_RX_BUF_LEN                     (2048+200) ///< Any message that comes into the device should be less than this buffer size. If a received message is bigger than this buffer size the message will be dropped.
#define MQTT_NUM_SUBSCRIBE_HANDLERS         (6) ///< Maximum number of topic filters the MQTT client can handle at any given time. This should be increased appropriately when using Thing Shadow

// if enablle auto reconnect, auto reconnect specific config
#define MQTT_MIN_RECONNECT_WAIT_INTERVAL    (1000) ///< Minimum time before the First reconnect attempt is made as part of the exponential back-off algorithm
#define MQTT_MAX_RECONNECT_WAIT_INTERVAL    (20000) ///< Maximum time interval after which exponential back-off will stop attempting to reconnect.

// rtos config
//#define _ENABLE_THREAD_SUPPORT_

// ssl config
#define _ENABLE_SSL_SUPPORT_

// debug config
#define ENABLE_IOT_DEBUG
//#define ENABLE_IOT_TRACE
#define ENABLE_IOT_INFO
#define ENABLE_IOT_WARN
#define ENABLE_IOT_ERROR

#endif /* SRC_SHADOW_IOT_SHADOW_CONFIG_H_ */
