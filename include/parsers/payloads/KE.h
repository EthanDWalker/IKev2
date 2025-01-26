#define KE_H
#ifdef KE_H
#include "Generic.h"

typedef struct {
  IKEGenericPayloadHeader gpe;
  uint16_t DHGroupNumber;
  unsigned char *data;
} KEPayload;

int KEParsePayload(unsigned char *packet, KEPayload *payload);

#endif // KE_H
