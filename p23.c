#include <stdio.h>
#include <stdint.h>

// Initial permutation for S-DES
const int IP[] = {2, 6, 3, 1, 4, 8, 5, 7};

// Final permutation for S-DES
const int IP_INV[] = {4, 1, 3, 5, 7, 2, 8, 6};

// P10 permutation for key generation
const int P10[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};

// P8 permutation for key generation
const int P8[] = {6, 3, 7, 4, 8, 5, 10, 9};

// Initial permutation for 8-bit data
const int P4[] = {2, 4, 3, 1};

// S-boxes for S-DES
const int S0[4][4] = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 3, 2}
};

const int S1[4][4] = {
    {0, 1, 2, 3},
    {2, 0, 1, 3},
    {3, 0, 1, 0},
    {2, 1, 0, 3}
};

// Key schedule
void generateKeys(uint8_t key, uint8_t *k1, uint8_t *k2) {
    uint8_t p10, p8, shift1, shift2;

    // Apply P10 permutation
    p10 = 0;
    for (int i = 0; i < 10; ++i) {
        p10 <<= 1;
        p10 |= (key >> (10 - P10[i])) & 1;
    }

    // Split into two halves
    uint8_t left = (p10 >> 5) & 0x1F;
    uint8_t right = p10 & 0x1F;

    // Perform first circular left shift
    shift1 = ((left << 1) & 0x1E) | ((left >> 4) & 1);
    shift1 <<= 5;
    shift1 |= ((right << 1) & 0x1E) | ((right >> 4) & 1);

    // Generate k1 (first subkey)
    *k1 = 0;
    for (int i = 0; i < 8; ++i) {
        *k1 <<= 1;
        *k1 |= (shift1 >> (10 - P8[i])) & 1;
    }

    // Perform second circular left shift
    shift2 = ((shift1 << 2) & 0x1C) | ((shift1 >> 3) & 3);
    // Generate k2 (second subkey)
    *k2 = 0;
    for (int i = 0; i < 8; ++i) {
        *k2 <<= 1;
        *k2 |= (shift2 >> (10 - P8[i])) & 1;
    }
}

// Initial permutation
uint8_t initialPermutation(uint8_t input) {
    uint8_t output = 0;
    for (int i = 0; i < 8; ++i) {
        output <<= 1;
        output |= (input >> (8 - IP[i])) & 1;
    }
    return output;
}

// Final permutation
uint8_t finalPermutation(uint8_t input) {
    uint8_t output = 0;
    for (int i = 0; i < 8; ++i) {
        output <<= 1;
        output |= (input >> (8 - IP_INV[i])) & 1;
    }
    return output;
}

// Expansion permutation (for F function)
uint8_t expansionPermutation(uint8_t input) {
    uint8_t output = 0;
    for (int i = 0; i < 4; ++i) {
        output <<= 1;
        output |= (input >> (4 - P4[i])) & 1;
    }
    return output;
}

// S-box substitution
uint8_t sBox(uint8_t input, const int S[4][4]) {
    int row = ((input & 0x08) >> 2) | (input & 0x01);
    int col = (input & 0x06) >> 1;
    return S[row][col];
}

// F function (Feistel function)
uint8_t fFunction(uint8_t input, uint8_t key) {
    uint8_t expanded = expansionPermutation(input);
    uint8_t xored = expanded ^ key;

    uint8_t substituted = 0;
    uint8_t upper = (xored & 0xF0) >> 4;
    uint8_t lower = xored & 0x0F;

    substituted |= sBox(upper, S0) << 2;
    substituted |= sBox(lower, S1);

    // Apply P4 permutation
    uint8_t output = 0;
    for (int i = 0; i < 4; ++i) {
        output <<= 1;
        output |= (substituted >> (4 - P4[i])) & 1;
    }

    return output;
}

// Encrypt one round of S-DES
uint8_t encryptRound(uint8_t input, uint8_t key) {
    uint8_t left = (input >> 4) & 0x0F;
    uint8_t right = input & 0x0F;

    uint8_t fOutput = fFunction(right, key);
    uint8_t newRight = left ^ fOutput;
    uint8_t newLeft = right;

    return (newLeft << 4) | newRight;
}

// Decrypt one round of S-DES
uint8_t decryptRound(uint8_t input, uint8_t key) {
    uint8_t left = (input >> 4) & 0x0F;
    uint8_t right = input & 0x0F;

    uint8_t fOutput = fFunction(left, key);
    uint8_t newRight = right ^ fOutput;
    uint8_t newLeft = left;

    return (newLeft << 4) | newRight;
}

// S-DES CTR encryption
void sdesCTR(uint8_t *plaintext, int len, uint8_t key, uint8_t counter) {
    uint8_t k1, k2;
    generateKeys(key, &k1, &k2);

    for (int i = 0; i < len; ++i) {
        uint8_t keystream = encryptRound(counter, k1); // Generate keystream using encryption
        plaintext[i] ^= keystream;
        counter++; // Increment counter for next block
    }
}

// S-DES CTR decryption (same as encryption because of XOR properties)
void sdesCTRDecrypt(uint8_t *ciphertext, int len, uint8_t key, uint8_t counter) {
    sdesCTR(ciphertext, len, key, counter); // Decryption is the same as encryption in CTR mode
}

// Print binary representation of an 8-bit number
void printBinary(uint8_t num) {
    for (int i = 7; i >= 0; --i) {
        printf("%d", (num >> i) & 1);
    }
}

int main() {
    uint8_t plaintext[] = {0b00000001, 0b00000010, 0b00000100};
    int plaintext_len = sizeof(plaintext) / sizeof(plaintext[0]);
    uint8_t key = 0b01111101;
    uint8_t counter = 0b00000000;

    printf("Plaintext (binary): ");
    for (int i = 0; i < plaintext_len; ++i) {
        printBinary(plaintext[i]);
        printf(" ");
    }
    printf("\n");

    // Encrypt
    sdesCTR(plaintext, plaintext_len, key, counter);

    printf("Ciphertext (binary): ");
    for (int i = 0; i < plaintext_len; ++i) {
        printBinary(plaintext[i]);
        printf(" ");
    }
    printf("\n");

    // Decrypt
    sdesCTRDecrypt(plaintext, plaintext_len, key, counter);

    printf("Decrypted plaintext (binary): ");
    for (int i = 0; i < plaintext_len; ++i) {
        printBinary(plaintext[i]);
        printf(" ");
    }
    printf("\n");

    return 0;
}