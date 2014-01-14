// -*- mode: c; tab-width: 4; indent-tabs-mode: 1; st-rulers: [70] -*-
// vim: ts=8 sw=8 ft=c noet

#ifndef MSGXCHNG_H
#define MSGXCHNG_H

#include <msgpack.h>

typedef struct msgxchng_request_s {
	char	*id;
	int		id_len;
	char	*command;
	int		command_len;
	char	*data;
	int		data_len;
} msgxchng_request_t;

typedef struct msgxchng_response_s {
	char	*id;
	int		id_len;
	char	*data;
	int		data_len;
	char	*status;
	int		status_len;
} msgxchng_response_t;

msgxchng_request_t *new_msgxchng_request(char *id, int id_len, char *command, int command_len, char *data, int data_len);
msgxchng_request_t *unpack_msgxchng_request(char *msgpack_request, int len);
char *pack_msgxchng_request(msgxchng_request_t *request, int *size);

msgxchng_response_t *new_msgxchng_response(char *id, int id_len, char *data, int data_len, char *status, int status_len);
msgxchng_response_t *unpack_msgxchng_response(char *msgpack_response, int len);
char *pack_msgxchng_response(msgxchng_response_t *response, int *size);


void msgpack_pack_key_value(msgpack_packer *packer, char *key, int key_len, char *value, int value_len);

void clean_request(msgxchng_request_t *request);
void clean_response(msgxchng_response_t *response);

#endif