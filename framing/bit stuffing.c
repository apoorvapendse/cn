// by chatgpt

#include <stdio.h>
#include <string.h>

// Function to perform bit stuffing
void bitStuffing(char *data) {
    int len = strlen(data);
    int count = 0;
    int new_len = 0;

    for (int i = 0; i < len; i++) {
        // Append the current bit to the stuffed data
        data[new_len] = data[i];
        new_len++;

        if (data[i] == '1') {
            count++;

            if (count == 5) {
                // Insert a '0' bit (bit stuffing)
                data[new_len] = '0';
                new_len++;
                count = 0;
            }
        } else {
            count = 0;
        }
    }

    // Null-terminate the stuffed data
    data[new_len] = '\0';
}

int main() {
    char data[] = "110111101111111011110"; // Example binary string
    printf("Original Data: %s\n", data);

    bitStuffing(data);

    printf("Stuffed Data:   %s\n", data);

    return 0;
}
