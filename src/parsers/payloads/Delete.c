#include "../../../include/parsers/payloads/Delete.h"
#include <stdlib.h>

int DeleteParsePayload(unsigned char *packet, DeletePayload *payload) {
  if (IKEParseGenericPayloadHeader(&packet[0], &payload->gpe) < 0) {
    return -1;
  }
  payload->protocol = packet[4];
  payload->spiSize = packet[5];
  payload->numSpi = Int16Parse(&packet[6]);
  if (payload->spiSize == 0)
    return 0;
  payload->spis = malloc(payload->spiSize * payload->numSpi);
  for (int i = 0; i < payload->gpe.payloadLength - 8; i++) {
    payload->spis[i] = Int32Parse(&packet[(i * payload->spiSize) + 8]);
  }
  return 0;
}
