#define SA_INIT_H
#ifdef SA_INIT_H
#include "../payloads.h"
#include "../IKEV2.h"

typedef struct {
  IKEHeader header;
  SAPayload saPayload;
  KEPayload kePayload;
  NoncePayload noncePayload;
} SAInitPacket;

int BuildResponse(SAInitPacket *packet, unsigned char *buffer);

#endif // SA_INIT_H
