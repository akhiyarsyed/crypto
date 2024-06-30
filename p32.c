#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Simulate the generation of a DSA signature with a unique k value
void dsa_sign(const char *message, uint8_t *signature, size_t sig_len) {
    // Generate a random k value (for demonstration)
    srand(time(NULL));
    for (size_t i = 0; i < sig_len; i++) {
        signature[i] = rand() % 256;
    }
    // Append the message hash (simplified)
    strncpy((char *)(signature + sig_len / 2), message, sig_len / 2);
}

// Simulate the generation of an RSA signature (deterministic for the same message)
void rsa_sign(const char *message, uint8_t *signature, size_t sig_len) {
    // Use a simple hash of the message as the signature (for demonstration)
    for (size_t i = 0; i < sig_len; i++) {
        signature[i] = message[i % strlen(message)] + i;
    }
}

void print_signature(const uint8_t *signature, size_t sig_len) {
    for (size_t i = 0; i < sig_len; i++) {
        printf("%02x", signature[i]);
    }
    printf("\n");
}

int main() {
    const char *message = "Hello, world!";
    size_t sig_len = 16;

    uint8_t dsa_signature1[sig_len];
    uint8_t dsa_signature2[sig_len];
    uint8_t rsa_signature1[sig_len];
    uint8_t rsa_signature2[sig_len];

    // Generate two DSA signatures for the same message
    dsa_sign(message, dsa_signature1, sig_len);
    dsa_sign(message, dsa_signature2, sig_len);

    // Generate two RSA signatures for the same message
    rsa_sign(message, rsa_signature1, sig_len);
    rsa_sign(message, rsa_signature2, sig_len);

    printf("DSA Signature 1: ");
    print_signature(dsa_signature1, sig_len);
    printf("DSA Signature 2: ");
    print_signature(dsa_signature2, sig_len);

    printf("RSA Signature 1: ");
    print_signature(rsa_signature1, sig_len);
    printf("RSA Signature 2: ");
    print_signature(rsa_signature2, sig_len);

    return 0;
}