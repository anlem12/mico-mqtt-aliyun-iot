# Lib_MQTT

本文档通过讲解 Lib_MQTT 示例程序使用，介绍如何在 MiCO 中实现 MQTT 通信功能。

* 适用 MiCO OS 版本： v3.0.0及以上
* 支持模块型号： EMW3165，EMW3166，EMW3031, EMW3080B/C. 

## 

* [准备工作](1.准备工作)
* [Lib_使用](2.Lib_使用)
* [运行结果](3.运行结果)

## 1.准备工作

* 选择一个 [MiCO 开发板](http://developer.mico.io/handbooks/6)
* 玩转 [第一个 MiCO 应用程序](http://developer.mico.io/handbooks/11)


## 2.Lib_使用
### 2.1 导入工程


1. 使用micocube 导入工程。在命令行输入以下指令:`mico import https://code.aliyun.com/mico/mqtt.git`

### 2.2 修改代码
lib部分不需修改，只需修改demo部分代码即可。


### 2.3 编译，下载

* 以3031模块为例：输入指令：`mqtt@MK3031@moc total download run`








## 3.API说明

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

### 3.5 IoT_Error_t mqtt_resubscribe(MQTT_Client *pClient);

|名称|`IoT_Error_t mqtt_resubscribe(MQTT_Client *pClient);`|
|:---|:---|
|功能|`重新订阅一个主题`|
|参数|`pClient 指向MQTT对象 `|
|返回|`成功或失败的类型`|

### 3.6 IoT_Error_t mqtt_unsubscribe(MQTT_Client *pClient, const char *pTopicFilter, uint16_t topicFilterLen);

|名称|`IoT_Error_t mqtt_unsubscribe(MQTT_Client *pClient, const char *pTopicFilter, uint16_t topicFilterLen);`|
|:---|:---|
|功能|`发送退订消息请求去除MQTT主题`|
|参数|`pClient 指向MQTT对象 `|
|参数|`pTopicFilter 主题名称 `|
|参数|`topicFilterLen 主题名称的长度 `|
|返回|`成功或失败的类型`|

### 3.7 IoT_Error_t mqtt_disconnect(MQTT_Client *pClient);

|名称|`IoT_Error_t mqtt_disconnect(MQTT_Client *pClient);`|
|:---|:---|
|功能|`断开MQTT连接`|
|参数|`pClient 指向MQTT对象 `|
|返回|`void`|

### 3.8 IoT_Error_t mqtt_yield(MQTT_Client *pClient, uint32_t timeout_ms);

|名称|`IoT_Error_t mqtt_yield(MQTT_Client *pClient, uint32_t timeout_ms);`|
|:---|:---|
|功能|`监控TCP连接 处理接收消息`|
|参数|`pClient 指向MQTT对象 `|
|参数|`timeout_ms 线程执行的最大毫秒数 `|
|返回|`成功或失败的类型`|

### 3.9 IoT_Error_t mqtt_attempt_reconnect(MQTT_Client *pClient);

|名称|`IoT_Error_t mqtt_attempt_reconnect(MQTT_Client *pClient);`|
|:---|:---|
|功能|`MQTT手动重连函数`|
|功能|`断开MQTT连接`|
|返回|`成功或失败的类型`|
