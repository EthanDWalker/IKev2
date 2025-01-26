#pragma once
#define GENERIC_H
#ifdef GENERIC_H
#include <stdint.h>

typedef struct {
  uint8_t nextPayload;
  uint8_t critical;
  uint16_t payloadLength;
} IKEGenericPayloadHeader;

int IKEParseGenericPayloadHeader(unsigned char *packet, IKEGenericPayloadHeader *header);

#endif // GENERIC_H
