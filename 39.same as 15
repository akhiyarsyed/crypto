#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

typedef struct {
    char letter;
    int frequency;
} LetterFrequency;

int compare_frequencies(const void *a, const void *b) {
    return ((LetterFrequency *)b)->frequency - ((LetterFrequency *)a)->frequency;
}

void count_letter_frequencies(const char *text, int *frequency) {
    for (size_t i = 0; i < strlen(text); i++) {
        char ch = tolower(text[i]);
        if (isalpha(ch)) {
            frequency[ch - 'a']++;
        }
    }
}

void decrypt_additive_cipher(const char *cipher_text, char *plain_text, int key) {
    for (size_t i = 0; i < strlen(cipher_text); i++) {
        char ch = cipher_text[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            plain_text[i] = (ch - base - key + ALPHABET_SIZE) % ALPHABET_SIZE + base;
        } else {
            plain_text[i] = ch;
        }
    }
    plain_text[strlen(cipher_text)] = '\0';
}

int main() {
    char cipher_text[1000];
    char plain_text[1000];
    int frequency[ALPHABET_SIZE] = {0};
    LetterFrequency letter_frequencies[ALPHABET_SIZE];

    printf("Enter the ciphertext: ");
    fgets(cipher_text, sizeof(cipher_text), stdin);

    count_letter_frequencies(cipher_text, frequency);

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        letter_frequencies[i].letter = 'a' + i;
        letter_frequencies[i].frequency = frequency[i];
    }

    qsort(letter_frequencies, ALPHABET_SIZE, sizeof(LetterFrequency), compare_frequencies);

    printf("\nTop 10 possible plaintexts:\n");
    for (int k = 0; k < 10; k++) {
        int key = (letter_frequencies[0].letter - 'e' + k + ALPHABET_SIZE) % ALPHABET_SIZE;
        decrypt_additive_cipher(cipher_text, plain_text, key);
        printf("Key: %d\tPlaintext: %s\n", key, plain_text);
    }

    return 0;
}
