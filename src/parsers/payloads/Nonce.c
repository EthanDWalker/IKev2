#include "../../../include/parsers/payloads/Nonce.h"
#include <stdlib.h>

int NonceParsePayload(unsigned char *packet, NoncePayload *payload) {
  if (IKEParseGenericPayloadHeader(&packet[0], &payload->gpe) < 0) {
    return -1;
  }
  return 0;
}
