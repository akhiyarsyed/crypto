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
	size_t i;
    for ( i = 0; i < strlen(text); i++) {
        char ch = tolower(text[i]);
        if (isalpha(ch)) {
            frequency[ch - 'a']++;
        }
    }
}

void decrypt_substitution_cipher(const char *cipher_text, char *plain_text, char *key) {
	size_t i;
    for ( i = 0; i < strlen(cipher_text); i++) {
        char ch = cipher_text[i];
        if (isalpha(ch)) {
            char decrypted_ch = key[tolower(ch) - 'a'];
            plain_text[i] = isupper(ch) ? toupper(decrypted_ch) : decrypted_ch;
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
    int i,j;
    for ( i = 0; i < ALPHABET_SIZE; i++) {
        letter_frequencies[i].letter = 'a' + i;
        letter_frequencies[i].frequency = frequency[i];
    }

    qsort(letter_frequencies, ALPHABET_SIZE, sizeof(LetterFrequency), compare_frequencies);

    printf("\nTop 10 possible plaintexts:\n");
    for ( i = 0; i < 10; i++) {
        char key[ALPHABET_SIZE + 1];
        for ( j = 0; j < ALPHABET_SIZE; j++) {
            int shift = (letter_frequencies[j].letter - 'a' + i) % ALPHABET_SIZE;
            key[shift] = 'a' + j;
        }
        key[ALPHABET_SIZE] = '\0';

        decrypt_substitution_cipher(cipher_text, plain_text, key);
        printf("Key: %s\tPlaintext: %s\n", key, plain_text);
    }

    return 0;
}
