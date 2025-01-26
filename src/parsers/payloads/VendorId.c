#include "../../../include/parsers/payloads/VendorID.h"
#include <stdlib.h>

int VendorIdParsePayload(unsigned char *packet, VendorIdPayload *payload) {
  if (IKEParseGenericPayloadHeader(&packet[0], &payload->gpe) < 0) {
    return -1;
  }
  payload->id = (unsigned char *)malloc(sizeof(unsigned char) * (payload->gpe.payloadLength - 4));
  for (int i = 0; i < payload->gpe.payloadLength - 4; i++) {
    payload->id[i] = packet[i + 4];
  }
  return 0;
}
