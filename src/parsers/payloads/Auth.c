#include "../../../include/parsers/payloads/Auth.h"
#include <stdlib.h>

int AuthParsePayload(unsigned char *packet, AuthPayload *payload) {
  if (packet[5] != 0 || packet[6] != 0 || packet[7] != 0) {
    return -1;
  }
  if (IKEParseGenericPayloadHeader(&packet[0], &payload->gpe) < 0) {
    return -1;
  }
  payload->method = packet[4];
  payload->data = (unsigned char *)malloc(sizeof(unsigned char)  * (payload->gpe.payloadLength - 8));
  for (int i = 0; i < payload->gpe.payloadLength - 8; i++) {
    payload->data[i] = packet[i + 8];
  }
  return 0;
}
