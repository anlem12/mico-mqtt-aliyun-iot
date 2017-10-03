/**
 * @file mqtt_log.h
 * @brief Logging macros for the SDK.
 * This file defines common logging macros with log levels to be used within the SDK.
 * These macros can also be used in the IoT application code as a common way to output
 * logs.  The log levels can be tuned by modifying the makefile.  Removing (commenting
 * out) the IOT_* statement in the makefile disables that log level.
 *
 * It is expected that the macros below will be modified or replaced when porting to
 * specific hardware platforms as printf may not be the desired behavior.
 */

#ifndef _MQTT_LOG_H
#define _MQTT_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "mico_rtos.h"

extern mico_mutex_t stdio_tx_mutex;

/**
 * @brief Debug level logging macro.
 *
 * Macro to expose function, line number as well as desired log message.
 */
#ifdef ENABLE_IOT_DEBUG
#define IOT_DEBUG(...)    \
	{\
    mico_rtos_lock_mutex( &stdio_tx_mutex ); \
	printf("DEBUG:   %s L#%d ", __func__, __LINE__);  \
	printf(__VA_ARGS__); \
	printf("\r\n"); \
	mico_rtos_unlock_mutex( &stdio_tx_mutex );\
	}
#else
#define IOT_DEBUG(...)
#endif

/**
 * @brief Debug level trace logging macro.
 *
 * Macro to print message function entry and exit
 */
#ifdef ENABLE_IOT_TRACE
#define FUNC_ENTRY    \
	{\
    mico_rtos_lock_mutex( &stdio_tx_mutex ); \
	printf("FUNC_ENTRY:   %s L#%d \r\n", __func__, __LINE__);  \
	mico_rtos_unlock_mutex( &stdio_tx_mutex );\
	}
#define FUNC_EXIT    \
	{\
    mico_rtos_lock_mutex( &stdio_tx_mutex ); \
	printf("FUNC_EXIT:   %s L#%d \r\n", __func__, __LINE__);  \
	mico_rtos_unlock_mutex( &stdio_tx_mutex );\
	}
#define FUNC_EXIT_RC(x)    \
	{\
    mico_rtos_lock_mutex( &stdio_tx_mutex ); \
	printf("FUNC_EXIT:   %s L#%d Return Code : %d \r\n", __func__, __LINE__, x);  \
	mico_rtos_unlock_mutex( &stdio_tx_mutex );\
	return x; \
	}
#else
#define FUNC_ENTRY

#define FUNC_EXIT
#define FUNC_EXIT_RC(x) { return x; }
#endif

/**
 * @brief Info level logging macro.
 *
 * Macro to expose desired log message.  Info messages do not include automatic function names and line numbers.
 */
#ifdef ENABLE_IOT_INFO
#define IOT_INFO(...)    \
	{\
    mico_rtos_lock_mutex( &stdio_tx_mutex ); \
	printf(__VA_ARGS__); \
	printf("\r\n"); \
	mico_rtos_unlock_mutex( &stdio_tx_mutex );\
	}
#else
#define IOT_INFO(...)
#endif

/**
 * @brief Warn level logging macro.
 *
 * Macro to expose function, line number as well as desired log message.
 */
#ifdef ENABLE_IOT_WARN
#define IOT_WARN(...)   \
	{ \
    mico_rtos_lock_mutex( &stdio_tx_mutex ); \
	printf("WARN:  %s L#%d ", __func__, __LINE__);  \
	printf(__VA_ARGS__); \
	printf("\r\n"); \
	mico_rtos_unlock_mutex( &stdio_tx_mutex );\
	}
#else
#define IOT_WARN(...)
#endif

/**
 * @brief Error level logging macro.
 *
 * Macro to expose function, line number as well as desired log message.
 */
#ifdef ENABLE_IOT_ERROR
#define IOT_ERROR(...)  \
	{ \
    mico_rtos_lock_mutex( &stdio_tx_mutex ); \
	printf("ERROR: %s L#%d ", __func__, __LINE__); \
	printf(__VA_ARGS__); \
	printf("\r\n"); \
	mico_rtos_unlock_mutex( &stdio_tx_mutex );\
	}
#else
#define IOT_ERROR(...)
#endif

#ifdef __cplusplus
}
#endif

#endif // _IOT_LOG_H
