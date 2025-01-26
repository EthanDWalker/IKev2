#define AUTH_H
#ifdef AUTH_H
#include "Generic.h"
#include "../INT.h"

typedef struct {
  IKEGenericPayloadHeader gpe;
  uint8_t method;
  unsigned char *data;
} AuthPayload;

int AuthParsePayload(unsigned char *packet, AuthPayload *payload);

#endif // AUTH_H
