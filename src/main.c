#include "../include/parsers/IKEV2.h"
#include "../include/parsers/IPV4.h"
#include "../include/parsers/UDP.h"
#include "../include/parsers/payloads/SA.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Define the buffer size
#define BUFFER_SIZE 65536

void print_byte_binary(unsigned char byte) {
  for (int i = 7; i >= 0; i--) {
    printf("%d", (byte >> i) & 1); // Print each bit
  }
}

void print_raw_packet(unsigned char *buffer, ssize_t packet_size) {
  for (ssize_t i = 0; i < packet_size; i++) {
    print_byte_binary(buffer[i]); // Print byte in binary
    printf(" ");
    if ((i + 1) % 4 == 0) { // Print 8 bytes per line
      printf("\n");
    }
  }
  printf("\n");
}

int main() {
  int sockfd;
  unsigned char *buffer = (unsigned char *)malloc(BUFFER_SIZE);
  struct sockaddr_in source, dest;
  int addr_len = sizeof(struct sockaddr_in);

  sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
  if (sockfd < 0) {
    perror("Socket creation failed");
    return 1;
  }

  printf("Starting packet capture on port 500...\n");

  while (1) {
    ssize_t packet_size =
        recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&source,
                 (socklen_t *)&addr_len);
    if (packet_size < 0) {
      perror("Packet receive failed");
      return 1;
    }
    IPv4Header ipv4Header;
    UDPHeader udpHeader;
    V4Parse(buffer, &ipv4Header);
    UDPParse(&buffer[ipv4Header.headerLength], &udpHeader);
    if (udpHeader.destPort == 500) {
      IKEPacket ike;
      printf("Packet Rec\n");
      IKEParsePacket(&buffer[ipv4Header.headerLength + 8], &ike);
    }
  }

  free(buffer);
  close(sockfd);
  return 0;
}
