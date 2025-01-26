#define DELETE_H
#ifdef DELETE_H
#include "../../../include/parsers/INT.h"
#include "Generic.h"

typedef struct {
  IKEGenericPayloadHeader gpe;
  uint8_t protocol;
  uint8_t spiSize;
  uint16_t numSpi;
  uint32_t *spis;
} DeletePayload;

int DeleteParsePayload(unsigned char *packet, DeletePayload *payload);

#endif // DELETE_H
