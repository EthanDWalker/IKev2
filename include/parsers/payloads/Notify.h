#define NOTIFY_H
#ifdef NOTIFY_H
#include "../INT.h"
#include "Generic.h"

typedef struct {
  IKEGenericPayloadHeader gpe;
  uint8_t protocol;
  uint8_t spiSize;
  uint16_t messegeType;
  unsigned char *spi;
  unsigned char *data;
} NotifyPayload;

int NotifyParsePayload(unsigned char *packet, NotifyPayload *payload);

#endif // NOTIFY_H
