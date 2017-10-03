# MQTT_Demo

本文档通过讲解 Demo 示例程序使用，介绍如何在 MiCO 中实现 MQTT 通信功能。

* 适用 MiCO OS 版本： v3.0.0及以上
* 支持模块型号： EMW3165，EMW3166，EMW3031, EMW3080B/C. 

## 

* 1.[准备工作](#1.准备工作)
* 2.[Demo_使用](#2.Demo_使用)
* 3.[运行结果](#3.运行结果)

## 1.准备工作

* 选择一个 [MiCO 开发板](http://developer.mico.io/handbooks/6)
* 玩转 [第一个 MiCO 应用程序](http://developer.mico.io/handbooks/11)


## 2.Demo 使用
### 2.1 导入 MiCO 工程

1. 使用micocube 导入工程。在命令行输入以下指令:`mico import https://code.aliyun.com/mico/lib_mqtt.git`


### 2.2 修改代码

```
//是否启用SSL
#define MQTT_USE_SSL

#ifdef MQTT_USE_SSL
#define MQTT_HOST                   "6618fdda2a4f11e7a554fa163e876164.mqtt.iot.gz.baidubce.com" ///< Customer specific MQTT HOST. The same will be used for Thing Shadow
#define MQTT_PORT                   1884 ///< default port for MQTT/S
#define MQTT_ROOT_CA_FILENAME       NULL ///< Root CA file name
#define MQTT_CERTIFICATE_FILENAME   NULL ///< device signed certificate file name
#define MQTT_PRIVATE_KEY_FILENAME   NULL ///< Device private key filename
#define MQTT_USERNAME               "6618fdda2a4f11e7a554fa163e876164/77a0853e3a1a11e7a554fa163e876164"
#define MQTT_PASSWORD               "ibV/zzpOyHKDUVH4EEXK7RoZtJHp6GTj6fazxst2+k4="
#else
#define MQTT_HOST                   "19b2b220150911e7a554fa163e876164.mqtt.iot.gz.baidubce.com" ///< Customer specific MQTT HOST. The same will be used for Thing Shadow
#define MQTT_PORT                   1883 ///< default port for MQTT/S
#define MQTT_USERNAME               "19b2b220150911e7a554fa163e876164/5cc06e7215db11e7a554fa163e876164"
#define MQTT_PASSWORD               "KbjSBnOnVm+nB6XxMD8Suw1T6G17RbZAcEd2fEVGhVo="
#endif

#define MQTT_CLIENT_ID         "MiCO" ///< MQTT client ID should be unique for every device

```

### 2.3 编译与下载
* 以3031模块为例：输入指令：`mqtt@MK3031@moc total download run`


### 2.4 调试串口log

```c

[54867][SYSTEM: system_misc.c:  75] Station up
[54875][APP: mico_main.c:  55] wifi connected successful
[54879][mqtt: mqtt_main.c: 111] Connecting...
[59637][mqtt: mqtt_main.c: 119] Subscribing...
[59733][mqtt: mqtt_main.c: 128] publish...
[59834][mqtt: mqtt_main.c: 153] -->sleep
[60503][mqtt: mqtt_main.c:  46] Subscribe callback
[60505][mqtt: mqtt_main.c:  47] 6618fdda2a4f11e7a554fa163e876164/df358c1a348611e7a554fa163e876164/77a0853e3a1a11e7a554fa163e876164/status/json	hello from SDK QOS0 : 0 
[60521][mqtt: mqtt_main.c:  46] Subscribe callback
[60524][mqtt: mqtt_main.c:  47] 6618fdda2a4f11e7a554fa163e876164/df358c1a348611e7a554fa163e876164/77a0853e3a1a11e7a554fa163e876164/status/json	hello from SDK QOS1 : 1 
[60600][mqtt: mqtt_main.c: 153] -->sleep
[61213][mqtt: mqtt_main.c:  46] Subscribe callback
[61215][mqtt: mqtt_main.c:  47] 6618fdda2a4f11e7a554fa163e876164/df358c1a348611e7a554fa163e876164/77a0853e3a1a11e7a554fa163e876164/status/json	hello from SDK QOS0 : 2 
[61272][mqtt: mqtt_main.c:  46] Subscribe callback
[61274][mqtt: mqtt_main.c:  47] 6618fdda2a4f11e7a554fa163e876164/df358c1a348611e7a554fa163e876164/77a0853e3a1a11e7a554fa163e876164/status/json	hello from SDK QOS1 : 3 
	

```
### 2.5 API说明

### 3.1 IoT_Error_t mqtt_init(MQTT_Client *pClient, IoT_Client_Init_Params *pInitParams);

|名称|`IoT_Error_t mqtt_init(MQTT_Client *pClient, IoT_Client_Init_Params *pInitParams);`|
|:---|:---|
|功能|`mqtt client初始化函数`|
|参数|`pClient 指向MQTT对象 `|
|参数|`pInitParams 指向MQtt连接参数的指针 `|
|返回|`成功或失败的类型`|

### 3.2 IoT_Error_t mqtt_connect(MQTT_Client *pClient, IoT_Client_Connect_Params *pConnectParams);

|名称|`IoT_Error_t mqtt_connect(MQTT_Client *pClient, IoT_Client_Connect_Params *pConnectParams);`|
|:---|:---|
|功能|`MQTT连接函数`|
|参数|`pClient 指向MQTT对象 `|
|参数|`pConnectParams 指向MQtt连接参数的指针`|
|返回|`成功或失败的类型`|

### 3.3IoT_Error_t mqtt_publish(MQTT_Client *pClient, const char *pTopicName, uint16_t topicNameLen,
								 IoT_Publish_Message_Params *pParams);

|名称|`IoT_Error_t mqtt_publish(MQTT_Client *pClient, const char *pTopicName, uint16_t topicNameLen,IoT_Publish_Message_Params *pParams);`|
|:---|:---|
|功能|`向一个主题发布MQTT消息 `|
|参数|`pClient 指向MQTT对象 `|
|参数|`pTopicName 发送的主题名字 `|
|参数|`topicNameLen 主题名字的长度 `|
|参数|`pParams 发布的消息内容 `|
|返回|`成功或失败的类型`|

### 3.4IoT_Error_t mqtt_subscribe(MQTT_Client *pClient, const char *pTopicName, uint16_t topicNameLen, QoS qos, pApplicationHandler_t pApplicationHandler, void *pApplicationHandlerData);

|名称|`IoT_Error_t mqtt_subscribe(MQTT_Client *pClient, const char *pTopicName, uint16_t topicNameLen,QoS qos, pApplicationHandler_t pApplicationHandler, void *pApplicationHandlerData);`|
|:---|:---|
|功能|`订阅一个MQTT主题`|
|参数|`pClient 指向MQTT对象 `|
|参数|`pTopicName 将要订阅的主题名字 `|
|参数|`topicNameLen 主题名字的长度 `|
|参数|`argslen 服务请求数组参数长度 `|
|参数|`pApplicationHandler_t 此订阅的处理函数 `|
|参数|`pApplicationHandlerData 将数据作为参数传递给应用程序处理程序回调 `|
|返回|`成功或失败的类型`|



### 2.6 关键代码注解



```

static void mqtt_sub_pub_main( mico_thread_arg_t arg )
{
    IoT_Error_t rc = FAILURE;

    char clientid[40];
    char cPayload[100];
    int i = 0;
    MQTT_Client client;
    IoT_Client_Init_Params mqttInitParams = iotClientInitParamsDefault;
    IoT_Client_Connect_Params connectParams = iotClientConnectParamsDefault;
    IoT_Publish_Message_Params paramsQOS0;
    IoT_Publish_Message_Params paramsQOS1;

    /*
     * Enable Auto Reconnect functionality. Minimum and Maximum time of Exponential backoff are set in aws_iot_config.h
     *  #AWS_IOT_MQTT_MIN_RECONNECT_WAIT_INTERVAL
     *  #AWS_IOT_MQTT_MAX_RECONNECT_WAIT_INTERVAL
     */
    mqttInitParams.enableAutoReconnect = true;
    mqttInitParams.pHostURL = MQTT_HOST;
    mqttInitParams.port = MQTT_PORT;
    mqttInitParams.mqttPacketTimeout_ms = 20000;
    mqttInitParams.mqttCommandTimeout_ms = 20000;
    mqttInitParams.tlsHandshakeTimeout_ms = 5000;
    mqttInitParams.disconnectHandler = disconnectCallbackHandler;
    mqttInitParams.disconnectHandlerData = NULL;
    mqttInitParams.isBlockOnThreadLockEnabled = true;
#ifdef MQTT_USE_SSL
    mqttInitParams.pRootCALocation = MQTT_ROOT_CA_FILENAME;
    mqttInitParams.pDeviceCertLocation = MQTT_CERTIFICATE_FILENAME;
    mqttInitParams.pDevicePrivateKeyLocation = MQTT_PRIVATE_KEY_FILENAME;
    mqttInitParams.isSSLHostnameVerify = false;
    mqttInitParams.isClientnameVerify = false;
    mqttInitParams.isUseSSL = true;
#else
    mqttInitParams.pRootCALocation = NULL;
    mqttInitParams.pDeviceCertLocation = NULL;
    mqttInitParams.pDevicePrivateKeyLocation = NULL;
    mqttInitParams.isSSLHostnameVerify = false;
    mqttInitParams.isClientnameVerify = false;
    mqttInitParams.isUseSSL = false;
#endif
//MQTT初始化
    rc = mqtt_init( &client, &mqttInitParams );
    if ( SUCCESS != rc )
    {
        mqtt_log("aws_iot_mqtt_init returned error : %d ", rc);
        goto exit;
    }
//设置MQTT连接参数
    connectParams.keepAliveIntervalInSec = 30;
    connectParams.isCleanSession = true;
    connectParams.MQTTVersion = MQTT_3_1_1;
    connectParams.pClientID = MQTT_CLIENT_ID;
    connectParams.clientIDLen = (uint16_t) strlen( MQTT_CLIENT_ID );
    connectParams.isWillMsgPresent = false;
    connectParams.pUsername = MQTT_USERNAME;
    connectParams.usernameLen = strlen(MQTT_USERNAME);
    connectParams.pPassword = MQTT_PASSWORD;
    connectParams.passwordLen = strlen(MQTT_PASSWORD);
//MQTT连接。。。
    mqtt_log("Connecting...");
    rc = mqtt_connect( &client, &connectParams );
    if ( SUCCESS != rc )
    {
        mqtt_log("Error(%d) connecting to %s:%d", rc, mqttInitParams.pHostURL, mqttInitParams.port);
        goto exit;
    }

//MQTT订阅 
    mqtt_log("Subscribing...");
    rc = mqtt_subscribe( &client, MQTT_SUB_NAME, strlen( MQTT_SUB_NAME ), QOS0,
                         iot_subscribe_callback_handler, NULL );
    if ( SUCCESS != rc )
    {
        mqtt_log("Error subscribing : %d ", rc);
        goto exit;
    }

    mqtt_log("publish...");
    sprintf( cPayload, "%s : %d ", "hello from SDK", i );

    paramsQOS0.qos = QOS0;
    paramsQOS0.payload = (void *) cPayload;
    paramsQOS0.isRetained = 0;

    paramsQOS1.qos = QOS1;
    paramsQOS1.payload = (void *) cPayload;
    paramsQOS1.isRetained = 0;

    while ( 1 )
    {
        //Max time the yield function will wait for read messages
        rc = mqtt_yield( &client, 100 );
        if ( NETWORK_ATTEMPTING_RECONNECT == rc )
        {
            // If the client is attempting to reconnect we will skip the rest of the loop.
            mico_rtos_thread_sleep( 1 );
            continue;
        } else if ( NETWORK_RECONNECTED == rc )
        {
            mqtt_log("Reconnect Successful");
        }

        mqtt_log("-->sleep");
        mico_rtos_thread_msleep( 500 );
        sprintf( cPayload, "%s : %d ", "hello from SDK QOS0", i++ );
        paramsQOS0.payloadLen = strlen( cPayload );
//MQTT发送
        mqtt_publish( &client, MQTT_SUB_NAME, strlen( MQTT_SUB_NAME ), &paramsQOS0 );

        sprintf( cPayload, "%s : %d ", "hello from SDK QOS1", i++ );
        paramsQOS1.payloadLen = strlen( cPayload );
        rc = mqtt_publish( &client, MQTT_SUB_NAME, strlen( MQTT_SUB_NAME ), &paramsQOS1 );
        if ( rc == MQTT_REQUEST_TIMEOUT_ERROR )
        {
            mqtt_log("QOS1 publish ack not received");
            rc = SUCCESS;
        }
    }

    if ( SUCCESS != rc )
    {
        mqtt_log("An error occurred in the loop.\n");
    } else
    {
        mqtt_log("Publish done\n");
    }

    exit:
    mico_rtos_delete_thread( NULL );
}

 ```



## 3.运行结果 
本Demo可实现： 在MiCO 中实现 MQTT 通信功能。




