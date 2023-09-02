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
    bool acked;
    char data[PACKET_SIZE];
} Packet;

int main() {
    int sender_socket;
    struct sockaddr_in receiver_address;
    socklen_t receiver_address_length = sizeof(receiver_address);

    // Create sender socket
    sender_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (sender_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Setup receiver address
    memset(&receiver_address, 0, sizeof(receiver_address));
    receiver_address.sin_family = AF_INET;
    receiver_address.sin_port = htons(12345);
    receiver_address.sin_addr.s_addr = inet_addr("127.0.0.1");  // Change this to receiver's IP address

    Packet packets[TOTAL_PACKETS];
    for (int i = 0; i < TOTAL_PACKETS; i++) {
        packets[i].seq_num = i;
        packets[i].acked = false;
        memset(packets[i].data, 'A' + i, PACKET_SIZE);  // Fill data with some content
    }

    int base = 0;
    int next_seq_num = 0;

    while (base < TOTAL_PACKETS) {
        while (next_seq_num < base + WINDOW_SIZE && next_seq_num < TOTAL_PACKETS) {
            printf("Sending packet %d\n", next_seq_num);

            // Send packet over the network
            sendto(sender_socket, &packets[next_seq_num], sizeof(Packet), 0,
                   (struct sockaddr *)&receiver_address, receiver_address_length);

            next_seq_num++;
        }

        // Receive ACKs
        while (1) {
            Packet ack_packet;
            recvfrom(sender_socket, &ack_packet, sizeof(Packet), 0, NULL, NULL);

            if (ack_packet.seq_num >= base && ack_packet.seq_num < next_seq_num) {
                printf("Received ACK for packet %d\n", ack_packet.seq_num);
                packets[ack_packet.seq_num].acked = true;
                base = ack_packet.seq_num + 1;
            } else {
                printf("Received out-of-order ACK for packet %d\n", ack_packet.seq_num);
            }

            if (base == next_seq_num) {
                break;
            }
        }
    }

    close(sender_socket);
    return 0;
}
