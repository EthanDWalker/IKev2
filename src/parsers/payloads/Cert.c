#include "../../../include/parsers/payloads/Cert.h"
#include <stdlib.h>

int CertParsePayload(unsigned char *packet, CertPayload *payload) {
  if (IKEParseGenericPayloadHeader(&packet[0], &payload->gpe) < 0) {
    return -1;
  }
  payload->data = (unsigned char *)malloc(sizeof(unsigned char) * (payload->gpe.payloadLength - 8));
  for (int i = 0; i < payload->gpe.payloadLength - 8; i++) {
    payload->data[i] = packet[i + 8];
  }
  return 0;
}
