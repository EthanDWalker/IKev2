#define TRAFFICSELECTOR_H
#ifdef TRAFFICSELECTOR_H
#include "../INT.h"
#include "Generic.h"


typedef struct {
  uint8_t type;
  uint8_t ipProtocol;
  uint16_t length;
  uint16_t startPort;
  uint16_t endPort;
  uint32_t startAddress[4];
  uint32_t endAddress[4];
} TrafficSelector;

typedef struct {
  IKEGenericPayloadHeader gpe;
  uint8_t numTrafficSelectors;
  TrafficSelector *trafficSelectors;
} TrafficSelectorPayload;

int TrafficSelectorParse(unsigned char *packet, TrafficSelector *selector);

int TrafficSelectorParsePayload(unsigned char *packet,
                                TrafficSelectorPayload *payload);

#endif // TRAFFICSELECTOR_H
