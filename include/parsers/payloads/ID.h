#define ID_H
#ifdef ID_H
#include "Generic.h"

typedef struct {
  IKEGenericPayloadHeader gpe; 
  uint8_t idType;
  unsigned char *data;
} IDPayload;

int IDParsePayload(unsigned char *packet, IDPayload *payload);

#endif // ID_H
