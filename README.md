# aliyun-iot-mico-device

mico系统设备通过mqtt连接阿里云iot-hub

本demo测试开发版 mico-3165

下载代码后需要同步 mico-os_v.3.2及以上系统到mico-os文件夹

修改 mqtt文件夹 mico_app_define.h 中阿里云IOT-HUB的配置信息，参考如下链接：
https://help.aliyun.com/document_detail/30539.html?spm=5176.doc42655.6.574.q7IP1P

Demo中包含了mico系统easylink配网，配网成功后直接连接到阿里云IOT-HUB。

（配网APP暂时可通过庆科mico.io下载）

在IOT-HUB后台topic /productkey/devicename/get发送{"r":100,"g":100,"b":100}可以打开mico-3165版 灯光

阿里云IOT-HUB 交流QQ群：568153758