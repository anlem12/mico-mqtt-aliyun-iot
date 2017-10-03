/**
 * @file mqtt_config.h
 * @brief MQTT specific configuration file
 */

#ifndef MICO_APP_DEFINE_H_
#define MICO_APP_DEFINE_H_

#define MQTT_USE_SSL_

#ifdef MQTT_USE_SSL
#define MQTT_HOST                   "${productKey}.iot-as-mqtt.cn-shanghai.aliyuncs.com" ///< Customer specific MQTT HOST. The same will be used for Thing Shadow
#define MQTT_PORT                   1883 ///< default port for MQTT/S
#define MQTT_ROOT_CA_FILENAME       "root.cer" ///< Root CA file name
#define MQTT_CERTIFICATE_FILENAME   NULL ///< device signed certificate file name
#define MQTT_PRIVATE_KEY_FILENAME   NULL ///< Device private key filename
#define MQTT_USERNAME               "deviceName&productKey"
#define MQTT_PASSWORD               "参考阿里云IOT PASSWORD"
#else
#define MQTT_HOST                   "${productKey}.iot-as-mqtt.cn-shanghai.aliyuncs.com" ///< Customer specific MQTT HOST. The same will be used for Thing Shadow
#define MQTT_PORT                   1883 ///< default port for MQTT/S
#define MQTT_USERNAME               "deviceName&productKey"
#define MQTT_PASSWORD               "参考阿里云IOT PASSWORD"
#endif

#define MQTT_SUB_NAME "订阅topic"
#define MQTT_PUB_NAME "发布topic"
#define MQTT_ERROR_NAME "异常topic"

#define MQTT_CLIENT_ID "12345|securemode=3,signmethod=hmacsha1,timestamp=789|"

#define DEVICE_ID "设备ID"

#endif /* SRC_SHADOW_IOT_SHADOW_CONFIG_H_ */
