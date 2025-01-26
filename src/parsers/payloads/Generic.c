#include "../../../include/parsers/payloads/Generic.h"
#include "../../../include/parsers/INT.h"

int IKEParseGenericPayloadHeader(unsigned char *packet, IKEGenericPayloadHeader *header) {
  header->nextPayload = packet[0];
  header->critical = packet[1] / 128;
  header->payloadLength = Int16Parse(&packet[2]);
  return 0;
}
