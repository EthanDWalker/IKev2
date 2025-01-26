#define VENDORID_H
#ifdef VENDORID_H
#include "Generic.h"

typedef struct {
  IKEGenericPayloadHeader gpe;
  unsigned char *id;
} VendorIdPayload;

int VendorIdParsePayload(unsigned char *packet, VendorIdPayload *payload);

#endif // VENDORID_H
