#include "../../../include/parsers/payloads/ID.h"
#include <stdlib.h>

int IDParsePayload(unsigned char *packet, IDPayload *payload) {
  if (IKEParseGenericPayloadHeader(&packet[0], &payload->gpe) < 0) {
    return -1;
  }
  payload->idType = packet[4];
  payload->data = (unsigned char *)malloc(sizeof(unsigned char) *
                                          (payload->gpe.payloadLength - 8));
  for (int i = 0; i < payload->gpe.payloadLength - 8; i++) {
    payload->data[i] = packet[i + 8];
  }
  return 0;
}
