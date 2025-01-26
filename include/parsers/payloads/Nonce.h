#define NONCE_H
#ifdef NONCE_H
#include "Generic.h"

typedef struct {
  IKEGenericPayloadHeader gpe;
} NoncePayload;

int NonceParsePayload(unsigned char *packet, NoncePayload *payload);

#endif // NONCE_H
