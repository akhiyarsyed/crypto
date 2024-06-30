#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8  // Block size in bytes (for this example)

// Function to pad plaintext if necessary
void pad_plaintext(char *plaintext, int *len) {
    int remainder = *len % BLOCK_SIZE;
    int padding = BLOCK_SIZE - remainder;
    
    // Add padding block if necessary
    if (remainder == 0) {
        plaintext[*len] = 0x80;  // Padding start with 1
        (*len)++;
    } else {
        padding = BLOCK_SIZE - remainder;
        memset(&plaintext[*len], 0, padding);
        plaintext[*len] = 0x80;  // Padding start with 1
        (*len) += padding;
    }
}

// Function to remove padding from decrypted plaintext
void remove_padding(char *plaintext, int *len) {
    int i = *len - 1;
    
    while (plaintext[i] == 0 && i >= 0) {
        i--;
    }
    
    if (plaintext[i] == 0x80) {
        *len = i;
    }
}

// Function to perform ECB encryption
void encrypt_ecb(const char *plaintext, char *ciphertext, int len) {
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        // Perform XOR encryption (dummy encryption for demonstration)
        for (int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ 0xAB;  // Example XOR key (dummy)
        }
    }
}

// Function to perform ECB decryption
void decrypt_ecb(const char *ciphertext, char *plaintext, int len) {
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        // Perform XOR decryption (dummy decryption for demonstration)
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i + j] = ciphertext[i + j] ^ 0xAB;  // Example XOR key (dummy)
        }
    }
}

// Function to perform CBC encryption
void encrypt_cbc(const char *plaintext, char *ciphertext, int len, char *iv) {
    char prev_cipher_block[BLOCK_SIZE];
    memcpy(prev_cipher_block, iv, BLOCK_SIZE);
    
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        // XOR plaintext with previous ciphertext block (or IV)
        for (int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ prev_cipher_block[j];
        }
        
        // Perform XOR encryption (dummy encryption for demonstration)
        for (int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i + j] ^= 0xAB;  // Example XOR key (dummy)
        }
        
        // Update previous ciphertext block
        memcpy(prev_cipher_block, &ciphertext[i], BLOCK_SIZE);
    }
}

// Function to perform CBC decryption
void decrypt_cbc(const char *ciphertext, char *plaintext, int len, char *iv) {
    char prev_cipher_block[BLOCK_SIZE];
    memcpy(prev_cipher_block, iv, BLOCK_SIZE);
    
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        // Perform XOR decryption (dummy decryption for demonstration)
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i + j] = ciphertext[i + j] ^ 0xAB;  
        }
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i + j] ^= prev_cipher_block[j];
        }
        memcpy(prev_cipher_block, &ciphertext[i], BLOCK_SIZE);
    }
}
void encrypt_cfb(const char *plaintext, char *ciphertext, int len, char *iv) {
    char feedback[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE);
    
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ 0xAB;
        }
        for (int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i + j] ^= feedback[j];
        }
        memcpy(feedback, &ciphertext[i], BLOCK_SIZE);
    }
}
void decrypt_cfb(const char *ciphertext, char *plaintext, int len, char *iv) {
    char feedback[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE);
    
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i + j] = ciphertext[i + j] ^ feedback[j];
        }
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i + j] ^= 0xAB; 
        }
        memcpy(feedback, &ciphertext[i], BLOCK_SIZE);
    }
}

int main() {
    char plaintext[256];
    char ciphertext[256];
    char decryptedtext[256];
    int len;
    printf("Enter plaintext to encrypt (multiple of %d bytes): ", BLOCK_SIZE);
    fgets(plaintext, sizeof(plaintext), stdin);
    len = strlen(plaintext);
    plaintext[len - 1] = '\0'; 
    pad_plaintext(plaintext, &len);
    char iv[BLOCK_SIZE] = { 0 };
    encrypt_ecb(plaintext, ciphertext, len);
    printf("\nECB Mode:\n");
    printf("Encrypted ciphertext: ");
    for (int i = 0; i < len; i++) {
        printf("%02X ", (unsigned char)ciphertext[i]);
    }
    decrypt_ecb(ciphertext, decryptedtext, len);
    remove_padding(decryptedtext, &len);
    printf("\nDecrypted plaintext: %s\n", decryptedtext);
    encrypt_cbc(plaintext, ciphertext, len, iv);
    printf("\nCBC Mode:\n");
    printf("Encrypted ciphertext: ");
    for (int i = 0; i < len; i++) {
        printf("%02X ", (unsigned char)ciphertext[i]);
    }
    decrypt_cbc(ciphertext, decryptedtext, len, iv);
    remove_padding(decryptedtext, &len);
    printf("\nDecrypted plaintext: %s\n", decryptedtext);
    encrypt_cfb(plaintext, ciphertext, len, iv);
    printf("\nCFB Mode:\n");
    printf("Encrypted ciphertext: ");
    for (int i = 0; i < len; i++) {
        printf("%02X ", (unsigned char)ciphertext[i]);
    }
    decrypt_cfb(ciphertext, decryptedtext, len, iv);
    remove_padding(decryptedtext, &len);
    printf("\nDecrypted plaintext: %s\n", decryptedtext);
    return 0;
}