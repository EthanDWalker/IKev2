#include "../../include/parsers/IKEV2.h"
#include "../../include/parsers/INT.h"
#include "../../include/parsers/payloads.h"
#include <stdio.h>

const char IKEHeaderSize = 28;

int IKEParseHeader(unsigned char *packet, IKEHeader *header) {
  if (packet[17] >> 4 != 2 || packet[17] != 32) {
    return -1;
  }
  header->initSPI = Int64Parse(&packet[0]);

  header->respSPI = Int64Parse(&packet[8]);

  header->nextType = packet[16];
  header->exchangeType = packet[18];

  header->msgID = Int32Parse(&packet[20]);
  header->length = Int32Parse(&packet[24]);
  return 0;
}

int IKEParsePacket(unsigned char *packet, IKEPacket *ike) {
  if (IKEParseHeader(&packet[0], &ike->header) < 0) {
    return -1;
  }
  int currentByte = IKEHeaderSize;
  uint8_t nextPayload = ike->header.nextType;
  while (nextPayload != 0) {
    printf("nextPayload:%d\n", nextPayload);
    switch (nextPayload) {
    case 33: {
      SAPayload payload;
      printf("SA\n");
      if (SAParsePayload(&packet[currentByte], &payload) < 0) {
        printf("error in SA");
        return -1;
      }
      nextPayload = payload.gpe.nextPayload;
      currentByte += payload.gpe.payloadLength;
      break;
    }
    case 34: {
      KEPayload payload;
      printf("KE\n");
      if (KEParsePayload(&packet[currentByte], &payload) < 0) {
        printf("error in KE");
        return -1;
      }
      nextPayload = payload.gpe.nextPayload;
      currentByte += payload.gpe.payloadLength;
      break;
    }
    case 35: {
      IDPayload payload;
      printf("ID\n");
      if (IDParsePayload(&packet[currentByte], &payload) < 0) {
        printf("error in ID");
        return -1;
      }
      nextPayload = payload.gpe.nextPayload;
      currentByte += payload.gpe.payloadLength;
      break;
    }
    case 37:
    case 38: {
      CertPayload payload;
      printf("Cert\n");
      if (CertParsePayload(&packet[currentByte], &payload) < 0) {
        printf("error in Cert");
        return -1;
      }
      nextPayload = payload.gpe.nextPayload;
      currentByte += payload.gpe.payloadLength;
      break;
    }
    case 39: {
      AuthPayload payload;
      printf("Auth\n");
      if (AuthParsePayload(&packet[currentByte], &payload) < 0) {
        printf("error in Auth");
        return -1;
      }
      nextPayload = payload.gpe.nextPayload;
      currentByte += payload.gpe.payloadLength;
      break;
    }
    case 40: {
      NoncePayload payload;
      printf("Nonce\n");
      if (NonceParsePayload(&packet[currentByte], &payload) < 0) {
        printf("error in Nonce");
        return -1;
      }
      nextPayload = payload.gpe.nextPayload;
      currentByte += payload.gpe.payloadLength;
      break;
    }
    case 41: {
      NotifyPayload payload;
      printf("Notify\n");
      if (NotifyParsePayload(&packet[currentByte], &payload) < 0) {
        printf("error in Notify");
        return -1;
      }
      printf("%d\n", payload.messegeType);
      printf("%d\n", payload.protocol);
      nextPayload = payload.gpe.nextPayload;
      currentByte += payload.gpe.payloadLength;
      break;
    }
    case 42: {
      DeletePayload payload;
      printf("Delete\n");
      if (DeleteParsePayload(&packet[currentByte], &payload) < 0) {
        printf("error in Delete");
        return -1;
      }
      nextPayload = payload.gpe.nextPayload;
      currentByte += payload.gpe.payloadLength;
      break;
    }
    case 43: {
      VendorIdPayload payload;
      printf("VendorID\n");
      if (VendorIdParsePayload(&packet[currentByte], &payload) < 0) {
        printf("error in VendorId");
        return -1;
      }
      nextPayload = payload.gpe.nextPayload;
      currentByte += payload.gpe.payloadLength;
      break;
    }
    case 44: {
      TrafficSelectorPayload payload;
      printf("TrafficSelector\n");
      if (TrafficSelectorParsePayload(&packet[currentByte], &payload) < 0) {
        printf("error in TrafficSelector");
        return -1;
      }
      nextPayload = payload.gpe.nextPayload;
      currentByte += payload.gpe.payloadLength;
      break;
    }
    default: {
      printf("defualt/noimpl");
      return -1;
    }
    }
  }
  return 0;
}
