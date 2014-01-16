// -*- mode: c; tab-width: 4; indent-tabs-mode: 1; st-rulers: [70] -*-
// vim: ts=8 sw=8 ft=c noet

#include "msgxchng.h"

static void msgpack_pack_key_value(msgpack_packer *packer, char *key, 
	int key_len, char *value, int value_len);

msgxchng_request_t 
*new_msgxchng_request(char 	*id, int id_len, char *command, 
	int	command_len, char *data, int data_len)
{
	msgxchng_request_t *request = (msgxchng_request_t *)malloc(sizeof *request);

	request->id_len 	= id_len;
	request->id			= (char *)malloc(id_len + 1);
	request->id[id_len]	= '\0';
	memcpy(request->id, id, id_len);

	request->command_len 			= command_len;
	request->command				= (char *)malloc(command_len + 1);
	request->command[command_len]	= '\0';
	memcpy(request->command, command, command_len);

	request->data_len 		= data_len;
	request->data			= (char *)malloc(data_len + 1);
	request->data[data_len]	= '\0';
	memcpy(request->data, data, data_len);

	return request;
}

msgxchng_request_t 
*unpack_msgxchng_request(char *msgpack_request, int len)
{
	msgpack_zone *mempool = (msgpack_zone*)malloc(sizeof(msgpack_zone));
	msgpack_object deserialized;
	msgxchng_request_t *request = NULL;
	char *id = NULL;
	char *command = NULL;
	char *data = NULL;
	int id_len = 0;
	int command_len = 0;
	int data_len = 0;

	msgpack_zone_init(mempool, 4096);
	msgpack_unpack(msgpack_request, len, NULL, mempool, &deserialized);

	if (deserialized.type == MSGPACK_OBJECT_MAP) {
		msgpack_object_kv* p = deserialized.via.map.ptr;
		msgpack_object_kv* const pend = deserialized.via.map.ptr + deserialized.via.map.size;
		for (; p < pend; ++p) {
			if (p->key.type == MSGPACK_OBJECT_RAW && p->val.type == MSGPACK_OBJECT_RAW) {
				if ( strncmp( p->key.via.raw.ptr , "id", p->key.via.raw.size ) == 0 ) {
					id_len	= p->val.via.raw.size;
					id		= (char *)p->val.via.raw.ptr;
				} else if ( strncmp( p->key.via.raw.ptr , "command", p->key.via.raw.size ) == 0 ) {
					command_len	= p->val.via.raw.size;
					command		= (char *)p->val.via.raw.ptr;
				} else if ( strncmp( p->key.via.raw.ptr , "data", p->key.via.raw.size ) == 0 ) {
					data_len	= p->val.via.raw.size;
					data		= (char *)p->val.via.raw.ptr;
				}
			}
		}
	}

	request = new_msgxchng_request(id, id_len, command, command_len, data, data_len);

	msgpack_zone_destroy(mempool);
	free(mempool);
	mempool = NULL;

	return request;
}

char 
*pack_msgxchng_request(msgxchng_request_t *request, int *size)
{
	msgpack_sbuffer *buffer = NULL;
	msgpack_packer *packer = NULL;
	char *msgpack_request;

	buffer = msgpack_sbuffer_new();
	msgpack_sbuffer_init(buffer);
	packer = msgpack_packer_new((void *)buffer, msgpack_sbuffer_write);

	msgpack_pack_map(packer, 3);
	msgpack_pack_key_value(packer, "id", 2, request->id, request->id_len);
	msgpack_pack_key_value(packer, "command", 7, request->command, request->command_len);
	msgpack_pack_key_value(packer, "data", 4, request->data, request->data_len);

	msgpack_request = (char *)malloc(buffer->size + 1);
	memcpy(msgpack_request, &buffer->data[0], buffer->size);
	msgpack_request[buffer->size] = '\0';
	*size = buffer->size;

	msgpack_packer_free(packer);
	msgpack_sbuffer_free(buffer);

	return msgpack_request;
}

msgxchng_response_t 
*new_msgxchng_response(char *id, int id_len, char *data, int data_len, 
	char *status, int status_len)
{
	msgxchng_response_t *response = (msgxchng_response_t *)malloc(sizeof *response);

	response->id_len 		= id_len;
	response->id			= (char *)malloc(id_len + 1);
	response->id[id_len]	= '\0';
	memcpy(response->id, id, id_len);

	response->data_len 			= data_len;
	response->data				= (char *)malloc(data_len + 1);
	response->data[data_len]	= '\0';
	memcpy(response->data, data, data_len);

	response->status_len 			= status_len;
	response->status				= (char *)malloc(status_len + 1);
	response->status[status_len]	= '\0';
	memcpy(response->status, status, status_len);

	return response;
}

msgxchng_response_t 
*unpack_msgxchng_response(char *msgpack_response, int len)
{
	msgpack_zone *mempool = (msgpack_zone*)malloc(sizeof(msgpack_zone));
	msgpack_object deserialized;
	msgxchng_response_t *response = NULL;
	char *id = NULL;
	char *data = NULL;
	char *status = NULL;
	int id_len = 0;
	int data_len = 0;
	int status_len = 0;

	msgpack_zone_init(mempool, 4096);
	msgpack_unpack(msgpack_response, len, NULL, mempool, &deserialized);

	if (deserialized.type == MSGPACK_OBJECT_MAP) {
		msgpack_object_kv* p = deserialized.via.map.ptr;
		msgpack_object_kv* const pend = deserialized.via.map.ptr + deserialized.via.map.size;
		for (;p < pend; ++p) {
			if (p->key.type == MSGPACK_OBJECT_RAW && p->val.type == MSGPACK_OBJECT_RAW) {
				if ( strncmp( p->key.via.raw.ptr , "id", p->key.via.raw.size ) == 0 ) {
					id_len = p->val.via.raw.size;
					id = (char *)p->val.via.raw.ptr;
				} else if ( strncmp( p->key.via.raw.ptr , "data", p->key.via.raw.size ) == 0 ) {
					data_len = p->val.via.raw.size;
					data = (char *)p->val.via.raw.ptr;
				} else if ( strncmp( p->key.via.raw.ptr , "status", p->key.via.raw.size ) == 0 ) {
					status_len = p->val.via.raw.size;
					status = (char *)p->val.via.raw.ptr;
				}
			}
		}
	}

	response = new_msgxchng_response(id, id_len, data, data_len, status, status_len);

	msgpack_zone_destroy(mempool);
	free(mempool);
	mempool = NULL;

	return response;
}

char 
*pack_msgxchng_response(msgxchng_response_t *response, int *size)
{
	msgpack_sbuffer *buffer = NULL;
	msgpack_packer *packer = NULL;
	char *msgpack_response;

	buffer = msgpack_sbuffer_new();
	msgpack_sbuffer_init(buffer);
	packer = msgpack_packer_new((void *)buffer, msgpack_sbuffer_write);

	msgpack_pack_map(packer, 3);
	msgpack_pack_key_value(packer, "id", 2, response->id, response->id_len);
	msgpack_pack_key_value(packer, "data", 4, response->data, response->data_len);
	msgpack_pack_key_value(packer, "status", 6, response->status, response->status_len);

	msgpack_response = (char *)malloc(buffer->size + 1);
	memcpy(msgpack_response, &buffer->data[0], buffer->size);
	msgpack_response[buffer->size] = '\0';
	*size = buffer->size;

	msgpack_packer_free(packer);
	msgpack_sbuffer_free(buffer);

	return msgpack_response;
}

static void 
msgpack_pack_key_value(msgpack_packer *packer, char *key, int key_len, 
	char *value, int value_len)
{
	msgpack_pack_raw(packer, key_len);
	msgpack_pack_raw_body(packer, key, key_len);
	msgpack_pack_raw(packer, value_len);
	msgpack_pack_raw_body(packer, value, value_len);
}

void 
clean_msgxchng_request(msgxchng_request_t *request)
{
	free(request->id);
	request->id = NULL;
	request->id_len = 0;
	free(request->command);
	request->command = NULL;
	request->command_len = 0;
	free(request->data);
	request->data = NULL;
	request->data_len = 0;
}

void 
clean_msgxchng_response(msgxchng_response_t *response)
{
	free(response->id);
	response->id = NULL;
	response->id_len = 0;
	free(response->data);
	response->data = NULL;
	response->data_len = 0;
	free(response->status);
	response->status = NULL;
	response->status_len = 0;
}