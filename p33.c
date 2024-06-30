#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char BYTE; // Define BYTE as an unsigned char type

// Initial Permutation (IP) table for DES
const int IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Initial Permutation Inverse (IP-1) table for DES
const int IP_INV[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

// Example 56-bit key (8 bytes)
BYTE key[8] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };

// Example 64-bit plaintext (8 bytes)
BYTE plaintext[8] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };

void permute(BYTE *input, BYTE *output, const int *table, int size) {
    for (int i = 0; i < size; i++) {
        int bit_pos = table[i] - 1;
        int byte_pos = bit_pos / 8;
        int bit_shift = bit_pos % 8;

        output[i] = (input[byte_pos] >> (7 - bit_shift)) & 0x01;
    }
}

int main() {
    BYTE permuted_plaintext[8]; // Store the IP permutation result
    BYTE permuted_key[8];       // Store the IP permutation of the key

    // Perform the Initial Permutation (IP) on the plaintext and key
    permute(plaintext, permuted_plaintext, IP, 64);
    permute(key, permuted_key, IP, 64);

    // Display the permuted plaintext and key (in binary form for simplicity)
    printf("Permuted Plaintext: ");
    for (int i = 0; i < 8; i++) {
        printf("%d", permuted_plaintext[i]);
    }
    printf("\n");

    printf("Permuted Key: ");
    for (int i = 0; i < 8; i++) {
        printf("%d", permuted_key[i]);
    }
    printf("\n");

    return 0;
}