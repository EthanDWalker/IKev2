#define CERT_H
#ifdef CERT_H
#include "Generic.h"
#include "../INT.h"

typedef struct {
  IKEGenericPayloadHeader gpe;
  uint8_t encoding;
  unsigned char *data;
} CertPayload;

int CertParsePayload(unsigned char *packet, CertPayload *payload);

#endif // CERT_H
