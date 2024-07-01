#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_SIZE 1024

void encrypt(char *plaintext, char *key, char *ciphertext) {
    int text_len = strlen(plaintext);
    int key_len = strlen(key);
    int i, j;

    for (i = 0, j = 0; i < text_len; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = (plaintext[i] - base + (tolower(key[j % key_len]) - 'a')) % 26 + base;
            j++;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}

void decrypt(char *ciphertext, char *key, char *plaintext) {
    int text_len = strlen(ciphertext);
    int key_len = strlen(key);
    int i, j;

    for (i = 0, j = 0; i < text_len; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - base - (tolower(key[j % key_len]) - 'a') + 26) % 26 + base;
            j++;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char plaintext[MAX_TEXT_SIZE];
    char key[MAX_TEXT_SIZE];
    char ciphertext[MAX_TEXT_SIZE];

    printf("Enter the plaintext: ");
    fgets(plaintext, MAX_TEXT_SIZE, stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  // Remove the newline character

    printf("Enter the key: ");
    fgets(key, MAX_TEXT_SIZE, stdin);
    key[strcspn(key, "\n")] = '\0';  // Remove the newline character

    encrypt(plaintext, key, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    decrypt(ciphertext, key, plaintext);
    printf("Decrypted text: %s\n", plaintext);

    return 0;
}
