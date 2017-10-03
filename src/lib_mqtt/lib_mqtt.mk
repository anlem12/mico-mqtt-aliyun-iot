#
#  UNPUBLISHED PROPRIETARY SOURCE CODE
#  Copyright (c) 2016 MXCHIP Inc.
#
#  The contents of this file may not be disclosed to third parties, copied or
#  duplicated in any form, in whole or in part, without the prior written
#  permission of MXCHIP Corporation.
#

NAME := Lib_MQTT_AWS

GLOBAL_INCLUDES := 	./include \
					./platform
$(NAME)_SOURCES := ./src/mqtt_client_common_internal.c \
				   ./src/mqtt_client_connect.c \
				   ./src/mqtt_client_publish.c \
				   ./src/mqtt_client_subscribe.c \
				   ./src/mqtt_client_unsubscribe.c \
				   ./src/mqtt_client_yield.c \
				   ./src/mqtt_client.c \
				   ./platform/network_platform.c \
				   ./platform/threads_platform.c \
				   ./platform/timer_platform.c
				   