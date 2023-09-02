#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>

#define WINDOW_SIZE 4
#define TOTAL_PACKETS 10
#define PACKET_SIZE 1024

typedef struct {
    int seq_num;
} AckPacket;

typedef struct {
    int seq_num;
    char data[PACKET_SIZE];
} Packet;

int main() {
    int receiver_socket;
    struct sockaddr_in receiver_address, sender_address;
    socklen_t sender_address_length = sizeof(sender_address);

    // Create receiver socket
    receiver_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (receiver_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Setup receiver address
    memset(&receiver_address, 0, sizeof(receiver_address));
    receiver_address.sin_family = AF_INET;
    receiver_address.sin_port = htons(12345);
    receiver_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the receiver socket to the receiver address
    if (bind(receiver_socket, (struct sockaddr *)&receiver_address, sizeof(receiver_address)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    AckPacket ack_packet;

    int expected_seq_num = 0;
    while (expected_seq_num < TOTAL_PACKETS) {
        Packet received_packet;
        recvfrom(receiver_socket, &received_packet, sizeof(Packet), 0,
                 (struct sockaddr *)&sender_address, &sender_address_length);

        printf("Received packet %d\n", received_packet.seq_num);

        if (received_packet.seq_num == expected_seq_num) {
            // Process received packet and send ACK
            ack_packet.seq_num = expected_seq_num;
            sendto(receiver_socket, &ack_packet, sizeof(AckPacket), 0,
                   (struct sockaddr *)&sender_address, sender_address_length);
            expected_seq_num++;
        } else {
            // Send ACK for the last correctly received packet
            ack_packet.seq_num = expected_seq_num - 1;
            sendto(receiver_socket, &ack_packet, sizeof(AckPacket), 0,
                   (struct sockaddr *)&sender_address, sender_address_length);
        }
    }

    close(receiver_socket);
    return 0;
}
