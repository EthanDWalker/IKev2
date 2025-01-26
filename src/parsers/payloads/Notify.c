#include "../../../include/parsers/payloads/Notify.h"
#include <stdlib.h>

int NotifyParsePayload(unsigned char *packet, NotifyPayload *payload) {
  if (IKEParseGenericPayloadHeader(&packet[0], &payload->gpe) < 0) {
    return -1;
  }
  payload->protocol = packet[4];
  payload->spiSize = packet[5];
  payload->messegeType = Int16Parse(&packet[6]);
  payload->spi =
      (unsigned char *)malloc(sizeof(unsigned char) * payload->spiSize);
  for (int i = 0; i < payload->spiSize; i++) {
    payload->spi[i] = packet[i + 8];
  }
  payload->data = (unsigned char *)malloc(
      sizeof(unsigned char) *
      (payload->gpe.payloadLength - (8 + payload->spiSize)));
  for (int i = 0; i < payload->gpe.payloadLength - (8 + payload->spiSize); i++) {
    payload->spi[i] = packet[i + 8 + payload->spiSize];
  }
  return 0;
}
