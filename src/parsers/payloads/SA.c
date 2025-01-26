#include "../../../include/parsers/payloads/SA.h"
#include "../../../include/parsers/INT.h"
#include <stdio.h>
#include <stdlib.h>

const char PROPOSALHEADERSIZENOSPI = 8;
const char TRANSFORMHEADERSIZE = 8;
const char ATTRIBUTESIZE = 8;

int SAParseAttribute(unsigned char *packet, SAAttribute *attribute) {
  if (packet[0] != 128 && packet[0] != 0) {
    return -1;
  }
  attribute->format = packet[0] / 128;
  attribute->type = Int16Parse(&packet[0]) & 32767; // 0111 1111 1111 1111
  if (attribute->format == 0) {
    attribute->length = Int16Parse(&packet[2]);
    attribute->data = (unsigned char *)malloc(sizeof(unsigned char) *
                                              (attribute->length - 4));
    for (int i = 0; i < attribute->length - 4; i++) {
      attribute->data[i] = packet[i + 4];
    }
    return 0;
  } else if (attribute->format == 1) {
    attribute->length = 4;
    attribute->data = (unsigned char *)malloc(sizeof(unsigned char) * 2);
    for (int i = 0; i < 2; i++) {
      attribute->data[i] = packet[i + 2];
    }
    return 0;
  }
  return -1;
}

int SAParseTransform(unsigned char *packet, SATransform *transform) {
  if (packet[0] != 0 && packet[0] != 3) {
    return -1;
  }

  transform->length = Int16Parse(&packet[2]);
  transform->type = packet[4];
  transform->id = Int16Parse(&packet[6]);

  transform->attributes = (SAAttribute *)malloc(
      sizeof(SAAttribute) * (transform->length - TRANSFORMHEADERSIZE));
  if (transform->attributes == NULL) {
    perror("Memory allocation failed for transform attributes");
    return -1;
  }

  int currentByte = TRANSFORMHEADERSIZE;
  int index = 0;
  while (currentByte < transform->length) {
    SAAttribute saAttribute = {0};
    if (SAParseAttribute(&packet[currentByte], &saAttribute) < 0) {
      free(transform->attributes);
      return -1;
    }
    transform->attributes[index] = saAttribute;
    currentByte += saAttribute.length;
    index++;
  }
  return packet[0];
}

int SAParseProposal(unsigned char *packet, SAProposal *proposal) {

  if (packet[0] != 0 && packet[0] != 2) {
    return -1;
  }
  if (packet[4] < 1) {
    return -1;
  }

  proposal->length = Int16Parse(&packet[2]);
  proposal->index = packet[4];
  proposal->protocolType = packet[5];
  proposal->spiSize = packet[6];
  proposal->numTransforms = packet[7];

  proposal->transforms = malloc(
      sizeof(SATransform) *
      (proposal->length - (PROPOSALHEADERSIZENOSPI + proposal->spiSize)));
  if (proposal->transforms == NULL) {
    perror("Memory allocation failed for proposal transforms");
    return -1;
  }

  proposal->spi = 0;
  if (proposal->spiSize == 4) {
    proposal->spi = Int32Parse(&packet[8]);
  } else if (proposal->spiSize == 8) {
    proposal->spi = Int64Parse(&packet[8]);
  }

  int currentByte = PROPOSALHEADERSIZENOSPI + proposal->spiSize;
  int index = 0;
  while (currentByte < proposal->length) {
    if (currentByte > proposal->length)
      return -1;

    SATransform saTransform = {0};
    if (SAParseTransform(&packet[currentByte], &saTransform) < 0) {
      free(proposal->transforms);
      return -1;
    }

    proposal->transforms[index] = saTransform;
    currentByte += saTransform.length;
    index++;
  }
  return packet[0];
}

int SAParsePayload(unsigned char *packet, SAPayload *payload) {
  if (IKEParseGenericPayloadHeader(&packet[0], &payload->gpe) < 0) {
    return -1;
  }

  int currentByte = 4;
  int index = 0;

  payload->proposals =
      malloc(sizeof(SAProposal) * (payload->gpe.payloadLength - currentByte));
  if (payload->proposals == NULL) {
    perror("Memory allocation failed for proposals");
    return -1;
  }

  while (currentByte < payload->gpe.payloadLength) {
    if (SAParseProposal(&packet[currentByte], &payload->proposals[index]) >=
        0) {
      currentByte += payload->proposals[index].length;
      index++;
    } else {
      free(payload->proposals);
      return -1;
    }
  }
  return 0;
}
