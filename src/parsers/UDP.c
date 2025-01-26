#include "../../include/parsers/UDP.h"
#include "../../include/parsers/INT.h"

int UDPParse(unsigned char *packet, UDPHeader *header) {
  header->sourcePort = Int16Parse(&packet[0]);
  header->destPort = Int16Parse(&packet[2]);
  header->packetLength = Int16Parse(&packet[4]);
  header->checksum = Int16Parse(&packet[6]);
  return 0;
}
