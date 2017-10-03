#include "mico.h"

#define app_log(M, ...) custom_log("APP", M, ##__VA_ARGS__)
#define app_log_trace() custom_log_trace("APP")

extern OSStatus start_mqtt_sub_pub( void );

static mico_semaphore_t wait_sem = NULL;

/* MICO system callback: Restore default configuration provided by application */
void appRestoreDefault_callback( void * const user_config_data, uint32_t size )
{
    memset( user_config_data, 0x0, size );
}

static void micoNotify_WifiStatusHandler( WiFiEvent status, void* const inContext )
{
    switch ( status )
    {
        case NOTIFY_STATION_UP:
            if( wait_sem != NULL ){
                mico_rtos_set_semaphore( &wait_sem );
            }
            break;
        case NOTIFY_STATION_DOWN:
            case NOTIFY_AP_UP:
            case NOTIFY_AP_DOWN:
            break;
    }
}

int application_start( void )
{
    app_log_trace();
    OSStatus err = kNoErr;
    mico_Context_t* mico_context;

    mico_rtos_init_semaphore( &wait_sem, 1 );

    /*Register user function for MiCO nitification: WiFi status changed */
    err = mico_system_notify_register( mico_notify_WIFI_STATUS_CHANGED,
                                       (void *) micoNotify_WifiStatusHandler,
                                       NULL );
    require_noerr( err, exit );

    /* Create mico system context and read application's config data from flash */
    mico_context = mico_system_context_init( 0 );

    /* mico system initialize */
    err = mico_system_init( mico_context );
    require_noerr( err, exit );

    /* Wait for wlan connection*/
    mico_rtos_get_semaphore( &wait_sem, MICO_WAIT_FOREVER );
    app_log("wifi connected successful");

    /*≥ı ºªØ RGB LED(P9813)*/
   // rgb_led_init();

    start_mqtt_sub_pub();

    exit:
    mico_system_notify_remove( mico_notify_WIFI_STATUS_CHANGED,
                               (void *) micoNotify_WifiStatusHandler );
    mico_rtos_deinit_semaphore( &wait_sem );
    mico_rtos_delete_thread( NULL );
    return err;
}

