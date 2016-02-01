// -*- mode: c; tab-width: 4; indent-tabs-mode: 1; st-rulers: [70] -*-
// vim: ts=8 sw=8 ft=c noet

#include <stdio.h>
#include "msgxchng.h"

int
main(int argc, char **argv)
{
	msgxchng_request_t *msgxchng_request;
	msgxchng_response_t *msgxchng_response;
	char *msgpack_request;
	char *msgpack_response;

	char id[] = "123456";
	char command[] = "hello.there";
	char data[] = "other data";
	char status[] = "complete";

	int len = 0;

	printf("Testing libmsgxchng\n");

	msgxchng_request = new_msgxchng_request(id, strlen(id), command, strlen(command), data, strlen(data));
	printf("new_msgxchng_request(id: \"%s\", command: \"%s\", data: \"%s\")\n", msgxchng_request->id, msgxchng_request->command, msgxchng_request->data);
	msgpack_request = pack_msgxchng_request(msgxchng_request, &len);
	printf("pack_msgxchng_request(\"%s\", %d)\n", msgpack_request, len);
	clean_msgxchng_request(msgxchng_request);
	printf("clean_msgxchng_request()\n");
	free(msgxchng_request);
	msgxchng_request = NULL;
	msgxchng_request = unpack_msgxchng_request(msgpack_request, len);
	printf("unpack_msgxchng_request(id: \"%s\", command: \"%s\", data: \"%s\")\n", msgxchng_request->id, msgxchng_request->command, msgxchng_request->data);
	clean_msgxchng_request(msgxchng_request);
	free(msgxchng_request);
	msgxchng_request = NULL;
	free(msgpack_request);
	msgpack_request = NULL;

	msgxchng_response = new_msgxchng_response(id, strlen(id), data, strlen(data), status, strlen(status));
	printf("new_msgxchng_response(id: \"%s\", data: \"%s\", status: \"%s\")\n", msgxchng_response->id, msgxchng_response->data, msgxchng_response->status);
	msgpack_response = pack_msgxchng_response(msgxchng_response, &len);
	printf("pack_msgxchng_response(\"%s\", %d)\n", msgpack_response, len);
	clean_msgxchng_response(msgxchng_response);
	printf("clean_msgxchng_response()\n");
	free(msgxchng_response);
	msgxchng_response = NULL;
	msgxchng_response = unpack_msgxchng_response(msgpack_response, len);
	printf("unpack_msgxchng_response(id: \"%s\", data: \"%s\", status: \"%s\")\n", msgxchng_response->id, msgxchng_response->data, msgxchng_response->status);
	clean_msgxchng_request(msgxchng_response);
	free(msgxchng_response);
	msgxchng_response = NULL;
	free(msgpack_response);
	msgpack_response = NULL;

	return 0;
}