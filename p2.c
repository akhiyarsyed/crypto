#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt the plaintext using the substitution cipher
void encrypt(char *plaintext, char *ciphertext, const char *substitution) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        char ch = plaintext[i];
        if (isalpha(ch)) {
            int index = tolower(ch) - 'a';
            if (islower(ch)) {
                ciphertext[i] = tolower(substitution[index]);
            } else {
                ciphertext[i] = toupper(substitution[index]);
            }
        } else {
            ciphertext[i] = ch; // Non-alphabetic characters remain unchanged
        }
    }
    ciphertext[i] = '\0'; // Null-terminate the ciphertext
}

int main() {
    // Define the substitution alphabet (cipher alphabet)
    const char *substitution = "QWERTYUIOPASDFGHJKLZXCVBNM";
    char plaintext[100];
    char ciphertext[100];

    // Get the plaintext from the user
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove the newline character

    // Encrypt the plaintext
    encrypt(plaintext, ciphertext, substitution);

    // Output the ciphertext
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
