/*******************************************************************************
 * Copyright (c) 2014 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Allan Stockdill-Mander/Ian Craggs - initial API and implementation and/or initial documentation
 *******************************************************************************/

/**
 * @file aws_iot_mqtt_client.c
 * @brief MQTT client API definitions
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "mqtt_log.h"
#include "mqtt_client_interface.h"
#include "../user_config/mqtt_config.h"

#ifdef _ENABLE_THREAD_SUPPORT_
#include "threads_interface.h"
#endif

const IoT_Client_Init_Params iotClientInitParamsDefault = IoT_Client_Init_Params_initializer;
const IoT_MQTT_Will_Options iotMqttWillOptionsDefault = IoT_MQTT_Will_Options_Initializer;
const IoT_Client_Connect_Params iotClientConnectParamsDefault = IoT_Client_Connect_Params_initializer;

ClientState mqtt_get_client_state(MQTT_Client *pClient) {
	FUNC_ENTRY;
	if(NULL == pClient) {
		return CLIENT_STATE_INVALID;
	}

	FUNC_EXIT_RC(pClient->clientStatus.clientState);
}

#ifdef _ENABLE_THREAD_SUPPORT_
IoT_Error_t mqtt_client_lock_mutex(MQTT_Client *pClient, IoT_Mutex_t *pMutex) {
	FUNC_ENTRY;
	IoT_Error_t threadRc = MQTT_FAILURE;

	if(NULL == pClient || NULL == pMutex){
		FUNC_EXIT_RC(NULL_VALUE_ERROR);
	}

	if(false == pClient->clientData.isBlockOnThreadLockEnabled) {
		threadRc = aws_iot_thread_mutex_trylock(pMutex);
	} else {
		threadRc = aws_iot_thread_mutex_lock(pMutex);
		/* Should never return Error because the above request blocks until lock is obtained */
	}

	if(MQTT_SUCCESS != threadRc) {
		FUNC_EXIT_RC(threadRc);
	}

	FUNC_EXIT_RC(MQTT_SUCCESS);
}

IoT_Error_t mqtt_client_unlock_mutex(MQTT_Client *pClient, IoT_Mutex_t *pMutex) {
	if(NULL == pClient || NULL == pMutex) {
		return NULL_VALUE_ERROR;
	}
	IOT_UNUSED(pClient);
	return aws_iot_thread_mutex_unlock(pMutex);
}
#endif

IoT_Error_t mqtt_set_client_state(MQTT_Client *pClient, ClientState expectedCurrentState,
										  ClientState newState) {
	IoT_Error_t rc;
#ifdef _ENABLE_THREAD_SUPPORT_
	IoT_Error_t threadRc = MQTT_FAILURE;
#endif

	FUNC_ENTRY;
	if(NULL == pClient) {
		FUNC_EXIT_RC(NULL_VALUE_ERROR);
	}

#ifdef _ENABLE_THREAD_SUPPORT_
	rc = mqtt_client_lock_mutex(pClient, &(pClient->clientData.state_change_mutex));
	if(MQTT_SUCCESS != rc) {
		return rc;
	}
#endif
	if(expectedCurrentState == mqtt_get_client_state(pClient)) {
		pClient->clientStatus.clientState = newState;
		rc = MQTT_SUCCESS;
	} else {
		rc = MQTT_UNEXPECTED_CLIENT_STATE_ERROR;
	}

#ifdef _ENABLE_THREAD_SUPPORT_
	threadRc = mqtt_client_unlock_mutex(pClient, &(pClient->clientData.state_change_mutex));
	if(MQTT_SUCCESS == rc && MQTT_SUCCESS != threadRc) {
		rc = threadRc;
	}
#endif

	FUNC_EXIT_RC(rc);
}

IoT_Error_t mqtt_set_connect_params(MQTT_Client *pClient, IoT_Client_Connect_Params *pNewConnectParams) {
	FUNC_ENTRY;
	if(NULL == pClient || NULL == pNewConnectParams) {
		FUNC_EXIT_RC(NULL_VALUE_ERROR);
	}

	pClient->clientData.options.isWillMsgPresent = pNewConnectParams->isWillMsgPresent;
	pClient->clientData.options.MQTTVersion = pNewConnectParams->MQTTVersion;
	pClient->clientData.options.pClientID = pNewConnectParams->pClientID;
	pClient->clientData.options.clientIDLen = pNewConnectParams->clientIDLen;
	pClient->clientData.options.pUsername = pNewConnectParams->pUsername;
	pClient->clientData.options.usernameLen = pNewConnectParams->usernameLen;
	pClient->clientData.options.pPassword = pNewConnectParams->pPassword;
	pClient->clientData.options.passwordLen = pNewConnectParams->passwordLen;
	pClient->clientData.options.will.pTopicName = pNewConnectParams->will.pTopicName;
	pClient->clientData.options.will.topicNameLen = pNewConnectParams->will.topicNameLen;
	pClient->clientData.options.will.pMessage = pNewConnectParams->will.pMessage;
	pClient->clientData.options.will.msgLen = pNewConnectParams->will.msgLen;
	pClient->clientData.options.will.qos = pNewConnectParams->will.qos;
	pClient->clientData.options.will.isRetained = pNewConnectParams->will.isRetained;
	pClient->clientData.options.keepAliveIntervalInSec = pNewConnectParams->keepAliveIntervalInSec;
	pClient->clientData.options.isCleanSession = pNewConnectParams->isCleanSession;

	FUNC_EXIT_RC(MQTT_SUCCESS);
}

IoT_Error_t mqtt_init(MQTT_Client *pClient, IoT_Client_Init_Params *pInitParams) {
	uint32_t i;
	IoT_Error_t rc;
	IoT_Client_Connect_Params default_options = IoT_Client_Connect_Params_initializer;

	FUNC_ENTRY;

	if(NULL == pClient || NULL == pInitParams || NULL == pInitParams->pHostURL || 0 == pInitParams->port) {
		FUNC_EXIT_RC(NULL_VALUE_ERROR);
	}

	if( true == pInitParams->isUseSSL ){
	    if( true == pInitParams->isSSLHostnameVerify ){
	        if( NULL == pInitParams->pRootCALocation ){
	            FUNC_EXIT_RC(NULL_VALUE_ERROR);
	        }
	    }
	    if( true == pInitParams->isClientnameVerify ){
	        if( NULL == pInitParams->pDevicePrivateKeyLocation ||
	            NULL == pInitParams->pDeviceCertLocation){
	            FUNC_EXIT_RC(NULL_VALUE_ERROR);
	        }
	    }else{
	        pInitParams->pDevicePrivateKeyLocation = NULL;
	        pInitParams->pDeviceCertLocation = NULL;
	    }
	}

	for(i = 0; i < MQTT_NUM_SUBSCRIBE_HANDLERS; ++i) {
		pClient->clientData.messageHandlers[i].topicName = NULL;
		pClient->clientData.messageHandlers[i].pApplicationHandler = NULL;
		pClient->clientData.messageHandlers[i].pApplicationHandlerData = NULL;
		pClient->clientData.messageHandlers[i].qos = QOS0;
	}

	pClient->clientData.packetTimeoutMs = pInitParams->mqttPacketTimeout_ms;
	pClient->clientData.commandTimeoutMs = pInitParams->mqttCommandTimeout_ms;
	pClient->clientData.writeBufSize = MQTT_TX_BUF_LEN;
	pClient->clientData.readBufSize = MQTT_RX_BUF_LEN;
	pClient->clientData.counterNetworkDisconnected = 0;
	pClient->clientData.disconnectHandler = pInitParams->disconnectHandler;
	pClient->clientData.disconnectHandlerData = pInitParams->disconnectHandlerData;
	pClient->clientData.nextPacketId = 1;

	/* Initialize default connection options */
	rc = mqtt_set_connect_params(pClient, &default_options);
	if(MQTT_SUCCESS != rc) {
		FUNC_EXIT_RC(rc);
	}

#ifdef _ENABLE_THREAD_SUPPORT_
	pClient->clientData.isBlockOnThreadLockEnabled = pInitParams->isBlockOnThreadLockEnabled;
	rc = aws_iot_thread_mutex_init(&(pClient->clientData.state_change_mutex));
	if(MQTT_SUCCESS != rc) {
		FUNC_EXIT_RC(rc);
	}
	rc = aws_iot_thread_mutex_init(&(pClient->clientData.tls_read_mutex));
	if(MQTT_SUCCESS != rc) {
		FUNC_EXIT_RC(rc);
	}
	rc = aws_iot_thread_mutex_init(&(pClient->clientData.tls_write_mutex));
	if(MQTT_SUCCESS != rc) {
		FUNC_EXIT_RC(rc);
	}
#endif

	pClient->clientStatus.isPingOutstanding = 0;
	pClient->clientStatus.isAutoReconnectEnabled = pInitParams->enableAutoReconnect;

	rc = iot_tls_init(&(pClient->networkStack), pInitParams->pRootCALocation, pInitParams->pDeviceCertLocation,
					  pInitParams->pDevicePrivateKeyLocation, pInitParams->pHostURL, pInitParams->port,
					  pInitParams->tlsHandshakeTimeout_ms, pInitParams->isSSLHostnameVerify,
					  pInitParams->isUseSSL);

	if(MQTT_SUCCESS != rc) {
		pClient->clientStatus.clientState = CLIENT_STATE_INVALID;
		FUNC_EXIT_RC(rc);
	}

	init_timer(&(pClient->pingTimer));
	init_timer(&(pClient->reconnectDelayTimer));

	pClient->clientStatus.clientState = CLIENT_STATE_INITIALIZED;

	FUNC_EXIT_RC(MQTT_SUCCESS);
}

uint16_t mqtt_get_next_packet_id(MQTT_Client *pClient) {
	return pClient->clientData.nextPacketId = (uint16_t) ((MAX_PACKET_ID == pClient->clientData.nextPacketId) ? 1 : (
			pClient->clientData.nextPacketId + 1));
}

bool mqtt_is_client_connected(MQTT_Client *pClient) {
	bool isConnected;

	FUNC_ENTRY;

	if(NULL == pClient) {
		IOT_WARN(" Client is null! ");
		FUNC_EXIT_RC(false);
	}

	switch(pClient->clientStatus.clientState) {
		case CLIENT_STATE_INVALID:
		case CLIENT_STATE_INITIALIZED:
		case CLIENT_STATE_CONNECTING:
			isConnected = false;
			break;
		case CLIENT_STATE_CONNECTED_IDLE:
		case CLIENT_STATE_CONNECTED_YIELD_IN_PROGRESS:
		case CLIENT_STATE_CONNECTED_PUBLISH_IN_PROGRESS:
		case CLIENT_STATE_CONNECTED_SUBSCRIBE_IN_PROGRESS:
		case CLIENT_STATE_CONNECTED_UNSUBSCRIBE_IN_PROGRESS:
		case CLIENT_STATE_CONNECTED_RESUBSCRIBE_IN_PROGRESS:
		case CLIENT_STATE_CONNECTED_WAIT_FOR_CB_RETURN:
			isConnected = true;
			break;
		case CLIENT_STATE_DISCONNECTING:
		case CLIENT_STATE_DISCONNECTED_ERROR:
		case CLIENT_STATE_DISCONNECTED_MANUALLY:
		case CLIENT_STATE_PENDING_RECONNECT:
		default:
			isConnected = false;
			break;
	}

	FUNC_EXIT_RC(isConnected);
}

bool mqtt_is_autoreconnect_enabled(MQTT_Client *pClient) {
	FUNC_ENTRY;
	if(NULL == pClient) {
		IOT_WARN(" Client is null! ");
		FUNC_EXIT_RC(false);
	}

	FUNC_EXIT_RC(pClient->clientStatus.isAutoReconnectEnabled);
}

IoT_Error_t mqtt_autoreconnect_set_status(MQTT_Client *pClient, bool newStatus) {
	FUNC_ENTRY;
	if(NULL == pClient) {
		FUNC_EXIT_RC(NULL_VALUE_ERROR);
	}
	pClient->clientStatus.isAutoReconnectEnabled = newStatus;
	FUNC_EXIT_RC(MQTT_SUCCESS);
}

IoT_Error_t mqtt_set_disconnect_handler(MQTT_Client *pClient, iot_disconnect_handler pDisconnectHandler,
												void *pDisconnectHandlerData) {
	FUNC_ENTRY;
	if(NULL == pClient || NULL == pDisconnectHandler) {
		FUNC_EXIT_RC(NULL_VALUE_ERROR);
	}

	pClient->clientData.disconnectHandler = pDisconnectHandler;
	pClient->clientData.disconnectHandlerData = pDisconnectHandlerData;
	FUNC_EXIT_RC(MQTT_SUCCESS);
}

uint32_t mqtt_get_network_disconnected_count(MQTT_Client *pClient) {
	return pClient->clientData.counterNetworkDisconnected;
}

void mqtt_reset_network_disconnected_count(MQTT_Client *pClient) {
	pClient->clientData.counterNetworkDisconnected = 0;
}

#ifdef __cplusplus
}
#endif

