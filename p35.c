#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vigenere_encrypt(char *plaintext, int *key, int key_length) {
    int plaintext_length = strlen(plaintext);
    char ciphertext[plaintext_length + 1];

    for (int i = 0; i < plaintext_length; i++) {
        char current_char = plaintext[i];
        int shift = key[i % key_length];
        
        // Handle uppercase letters
        if (current_char >= 'A' && current_char <= 'Z') {
            ciphertext[i] = ((current_char - 'A' + shift) % 26) + 'A';
        }
        // Handle lowercase letters
        else if (current_char >= 'a' && current_char <= 'z') {
            ciphertext[i] = ((current_char - 'a' + shift) % 26) + 'a';
        }
        // Leave non-alphabetic characters unchanged
        else {
            ciphertext[i] = current_char;
        }
    }

    ciphertext[plaintext_length] = '\0';
    printf("Encrypted Text: %s\n", ciphertext);
}

int main() {
    char plaintext[] = "Hello, world!";
    int key[] = {3, 19, 5}; // Example key: 3 19 5

    int key_length = sizeof(key) / sizeof(key[0]);

    vigenere_encrypt(plaintext, key, key_length);

    return 0;
}