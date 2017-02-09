/**
 * Copyright 2016 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef  _LIBPARODUS_H
#define  _LIBPARODUS_H

#include <wrp-c/wrp-c.h>
#include "libparodus_log.h"

/**
 * This module is linked with the client, and provides connectivity
 * to the parodus service.
 */ 

typedef struct {
	const char *service_name;
	bool receive;
	int  keepalive_timeout_secs; 
	const char *parodus_url;
	const char *client_url;
	parlibLogHandler log_handler;		// will remove later
} libpd_cfg_t;

typedef void *libpd_instance_t;

/**
 * Initialize the parodus wrp interface
 *
 * @param instance pointer to receive instance object that must be provided
 *   to all subsequent API calls.
 * @param cfg configuration information: service_name must be provided,
 * @return 0 on success, valid errno otherwise.
 */
int libparodus_init (libpd_instance_t *instance, libpd_cfg_t *libpd_cfg);

/**
 *  Receives the next message in the queue that was sent to this service, waiting
 *  the prescribed number of milliseconds before returning.
 *
 *  @note msg will be set to NULL if no message is present during the time
 *  allotted.
 *
 *  @param instance instance object
 *  @param msg the pointer to receive the next msg struct
 *  @param ms the number of milliseconds to wait for the next message
 *
 *  @return 0 on success, 2 if closed msg received, 1 if timed out, 
 *   -1 if receive error, -3 no receiver option
 *
 *  @note don't free the msg when return is 2. 
 */
int libparodus_receive (libpd_instance_t instance, wrp_msg_t **msg, uint32_t ms);

/**
 * Sends a close message to the receiver
 *
 *  @param instance instance object
 */
int libparodus_close_receiver (libpd_instance_t instance);

/**
 * Shut down the parodus wrp interface
 *
 * @param instance instance object
*/
int libparodus_shutdown (libpd_instance_t *instance);


/**
 * Send a wrp message to the parodus service
 *
 * @param instance instance object
 * @param msg wrp message to send
 *
 * @return 0 on success, -1 otherwise.
 */
int libparodus_send (libpd_instance_t instance, wrp_msg_t *msg);


#endif
