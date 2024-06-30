#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY 3  // Shift key for Caesar cipher

// Function to encrypt plaintext using ECB mode (Caesar cipher)
void encrypt_ecb(const char *plaintext, char *ciphertext) {
    int i;
    for (i = 0; i < strlen(plaintext); i++) {
        ciphertext[i] = plaintext[i] + KEY;  // Caesar cipher encryption
    }
    ciphertext[i] = '\0';
}

// Function to decrypt ciphertext using ECB mode (Caesar cipher)
void decrypt_ecb(const char *ciphertext, char *plaintext) {
    int i;
    for (i = 0; i < strlen(ciphertext); i++) {
        plaintext[i] = ciphertext[i] - KEY;  // Caesar cipher decryption
    }
    plaintext[i] = '\0';
}

int main() {
    char plaintext[100];
    char ciphertext[100];
    char decryptedtext[100];

    printf("Enter plaintext to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  // Remove newline if present

    // Encrypt using ECB mode
    encrypt_ecb(plaintext, ciphertext);
    printf("Encrypted ciphertext: %s\n", ciphertext);

    // Decrypt using ECB mode
    decrypt_ecb(ciphertext, decryptedtext);
    printf("Decrypted plaintext: %s\n", decryptedtext);

    return 0;
}