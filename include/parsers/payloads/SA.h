#define SA_H
#ifdef SA_H
#include "Generic.h"

typedef struct {
  uint8_t format;
  uint16_t type;
  uint8_t length;
  unsigned char *data;
} SAAttribute ;

typedef struct {
  uint16_t length;
  uint8_t type;
  uint8_t id;
  SAAttribute *attributes;
} SATransform;

typedef struct {
  uint16_t length;
  uint8_t index;
  uint8_t protocolType;
  uint8_t spiSize;
  uint8_t numTransforms;
  uint64_t spi;
  SATransform *transforms;
} SAProposal;

typedef struct {
  IKEGenericPayloadHeader gpe;
  SAProposal *proposals;
} SAPayload;

int SAParseProposal(unsigned char *packet, SAProposal *proposal);

int SAParseTransform(unsigned char *packet, SATransform *transform);

int SAParseAttribute(unsigned char *packet, SAAttribute *attribute);

int SAParsePayload(unsigned char *packet, SAPayload *payload);

#endif // SA_H
