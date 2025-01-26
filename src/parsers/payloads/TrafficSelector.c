#include "../../../include/parsers/payloads/TrafficSelector.h"
#include <stdlib.h>

int TrafficSelectorParse(unsigned char *packet, TrafficSelector *selector) {
  if (packet[0] != 7 && packet[0] != 8) {
    return -1;
  }
  selector->type = packet[0];
  selector->ipProtocol = packet[1];
  selector->length = Int16Parse(&packet[2]);
  selector->startPort = Int16Parse(&packet[4]);
  selector->endPort = Int16Parse(&packet[6]);
  if (selector->type == 7) {
    for (int i = 0; i < 4; i++) {
      selector->startAddress[i] = packet[i + 8];
      selector->endAddress[i] = packet[i + 8 + 4];
    }
  } else {
    for (int i = 0; i < 4; i++) {
      selector->startAddress[i] = Int32Parse(&packet[(i * 4) + 8]);
      selector->endAddress[i] = Int32Parse(&packet[(i * 4) + 8 + 16]);
    }
  }
  return 0;
}

int TrafficSelectorParsePayload(unsigned char *packet,
                                TrafficSelectorPayload *payload) {
  if (packet[5] != 0 && packet[6] != 0 && packet[7] != 0) {
    return -1;
  }
  if (IKEParseGenericPayloadHeader(&packet[0], &payload->gpe) < 0) {
    return -1;
  }
  payload->numTrafficSelectors = packet[4];
  payload->trafficSelectors = (TrafficSelector *)malloc(
      sizeof(TrafficSelector) * payload->numTrafficSelectors);
  int index = 0;
  int currentByte = 8;
  while (currentByte < payload->gpe.payloadLength) {
    TrafficSelectorParse(&packet[currentByte], &payload->trafficSelectors[index]);
    index++;
    currentByte += payload->trafficSelectors[index].length;
  }
  return 0;
}
