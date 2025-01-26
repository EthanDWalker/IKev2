#include "../../../include/parsers/payloads/KE.h"
#include "../../../include/parsers/INT.h"
#include <stdlib.h>

int KEParsePayload(unsigned char *packet, KEPayload *payload) {
  if (packet[6] != 0 || packet[7] != 0)
    return -1;
  if (IKEParseGenericPayloadHeader(&packet[0], &payload->gpe) < 0) {
    return -1;
  }
  payload->DHGroupNumber = Int16Parse(&packet[4]);
  payload->data = (unsigned char *)malloc(sizeof(unsigned char) *
                                          (payload->gpe.payloadLength - 8));
  for (int i = 0; i < payload->gpe.payloadLength - 8; i++) {
    payload->data[i] = packet[i + 8];
  }
  return 0;
}
