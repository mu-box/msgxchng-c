# msgxchng c library

## Overview:

## Using:

### Building and installing:

### Example

```C
#include <msgxchng.h>

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

  msgxchng_request = new_msgxchng_request(id, strlen(id), command, strlen(command), data, strlen(data));

  msgpack_request = pack_msgxchng_request(msgxchng_request, &len);

  clean_msgxchng_request(msgxchng_request);
  free(msgxchng_request);

  msgxchng_request = unpack_msgxchng_request(msgpack_request, len);

  clean_msgxchng_request(msgxchng_request);
  free(msgxchng_request);
  free(msgpack_request);

  msgxchng_response = new_msgxchng_response(id, strlen(id), data, strlen(data), status, strlen(status));

  msgpack_response = pack_msgxchng_response(msgxchng_response, &len);

  clean_msgxchng_response(msgxchng_response);
  free(msgxchng_response);

  msgxchng_response = unpack_msgxchng_response(msgpack_response, len);

  clean_msgxchng_request(msgxchng_response);
  free(msgxchng_response);
  free(msgpack_response);

  return 0;
}
```