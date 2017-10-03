/**
 * @file threads_interface.h
 * @brief Thread interface definition for MQTT client.
 *
 * Defines an interface that can be used by system components for multithreaded situations.
 * Starting point for porting the SDK to the threading hardware layer of a new platform.
 */

#include "../user_config/mqtt_config.h"

#ifdef _ENABLE_THREAD_SUPPORT_
#ifndef __THREADS_INTERFACE_H_
#define __THREADS_INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The platform specific timer header that defines the Timer struct
 */
#include "threads_platform.h"

#include <mqtt_error.h>

/**
 * @brief Mutex Type
 *
 * Forward declaration of a mutex struct.  The definition of this struct is
 * platform dependent.  When porting to a new platform add this definition
 * in "threads_platform.h".
 *
 */
typedef struct _IoT_Mutex_t IoT_Mutex_t;

/**
 * @brief Initialize the provided mutex
 *
 * Call this function to initialize the mutex
 *
 * @param IoT_Mutex_t - pointer to the mutex to be initialized
 * @return IoT_Error_t - error code indicating result of operation
 */
IoT_Error_t aws_iot_thread_mutex_init(IoT_Mutex_t *);

/**
 * @brief Lock the provided mutex
 *
 * Call this function to lock the mutex before performing a state change
 * This is a blocking call.
 *
 * @param IoT_Mutex_t - pointer to the mutex to be locked
 * @return IoT_Error_t - error code indicating result of operation
 */
IoT_Error_t aws_iot_thread_mutex_lock(IoT_Mutex_t *);

/**
 * @brief Lock the provided mutex
 *
 * Call this function to lock the mutex before performing a state change.
 * This is not a blocking call.
 *
 * @param IoT_Mutex_t - pointer to the mutex to be locked
 * @return IoT_Error_t - error code indicating result of operation
 */
IoT_Error_t aws_iot_thread_mutex_trylock(IoT_Mutex_t *);

/**
 * @brief Unlock the provided mutex
 *
 * Call this function to unlock the mutex before performing a state change
 *
 * @param IoT_Mutex_t - pointer to the mutex to be unlocked
 * @return IoT_Error_t - error code indicating result of operation
 */
IoT_Error_t aws_iot_thread_mutex_unlock(IoT_Mutex_t *);

/**
 * @brief Destroy the provided mutex
 *
 * Call this function to destroy the mutex
 *
 * @param IoT_Mutex_t - pointer to the mutex to be destroyed
 * @return IoT_Error_t - error code indicating result of operation
 */
IoT_Error_t aws_iot_thread_mutex_destroy(IoT_Mutex_t *);

#ifdef __cplusplus
}
#endif

#endif /*__THREADS_INTERFACE_H_*/
#endif /*_ENABLE_THREAD_SUPPORT_*/
