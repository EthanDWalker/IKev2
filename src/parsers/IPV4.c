#include "../../include/parsers/IPV4.h"
#include "../../include/parsers/INT.h"

bool IsV4(unsigned char *packet) {
  return (packet[0] >> 4) == 4;
}

int V4Parse(unsigned char *packet, IPv4Header *header) {
  if (!IsV4(packet)) return -1;
  header->headerLength = (packet[0] & 15) * 4; // 15 == 0000 1111
  header->packetLength = Int16Parse(&packet[3]);
  header->protocol = packet[9];
  header->sourceIP[0] = packet[12];
  header->sourceIP[1] = packet[13];
  header->sourceIP[2] = packet[14];
  header->sourceIP[3] = packet[15];
  header->destIP[0] = packet[16];
  header->destIP[1] = packet[17];
  header->destIP[2] = packet[18];
  header->destIP[3] = packet[19];
  return 0;
}
