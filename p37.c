#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Structure to hold letter frequency information
typedef struct {
    char letter;
    int frequency;
} LetterFrequency;

// Function to calculate letter frequencies in a string
void calculate_letter_frequencies(const char *text, LetterFrequency frequencies[]) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i].letter = 'A' + i;
        frequencies[i].frequency = 0;
    }

    for (int i = 0; text[i] != '\0'; i++) {
        char c = toupper(text[i]);
        if (isalpha(c)) {
            frequencies[c - 'A'].frequency++;
        }
    }
}

// Comparator function for sorting LetterFrequency array by frequency in descending order
int compare_frequency(const void *a, const void *b) {
    const LetterFrequency *freq1 = (const LetterFrequency *)a;
    const LetterFrequency *freq2 = (const LetterFrequency *)b;
    return freq2->frequency - freq1->frequency;
}

// Function to perform a letter frequency attack and print possible plaintexts
void letter_frequency_attack(const char *ciphertext, int top_count) {
    LetterFrequency frequencies[ALPHABET_SIZE];
    calculate_letter_frequencies(ciphertext, frequencies);

    // Sort frequencies array in descending order
    qsort(frequencies, ALPHABET_SIZE, sizeof(LetterFrequency), compare_frequency);

    printf("Top %d possible plaintexts:\n", top_count);
    for (int i = 0; i < top_count; i++) {
        char key = 'A' + ((frequencies[i].letter - 'E' + ALPHABET_SIZE) % ALPHABET_SIZE); // Shift by frequency analysis
        printf("Key: %c - Decryption: ", key);

        for (int j = 0; ciphertext[j] != '\0'; j++) {
            char c = ciphertext[j];
            if (isalpha(c)) {
                if (islower(c)) {
                    printf("%c", 'a' + ((c - 'a' - (key - 'A') + ALPHABET_SIZE) % ALPHABET_SIZE));
                } else {
                    printf("%c", 'A' + ((c - 'A' - (key - 'A') + ALPHABET_SIZE) % ALPHABET_SIZE));
                }
            } else {
                printf("%c", c);
            }
        }
        printf("\n");
    }
}

int main() {
    char ciphertext[] = "Lxfopv ef xfc krxvjri reu Jyfwxuznfk Zjtzxty. Hy nsqqty xi Efqf kfw Rtyinrzty. Hy kfw Yjjhyrjx, Faj Anzw Dfdq Kfw Htrrfsj kfw Nsxtrjynts. Rtr Bnyyji Kwtrjy, Ywzxnsl, Jywywtyji, xfc Ywnsxxjwjsy Ktwzqjxxfljx zk Xfc Lztwj Ymfajwy xfc tzw Rtyinrzty mnx Fsnr F Jfw Zhhm kfw Nszw Hfwfr. Jfmjsij fwj Xfymzrk Ymfsyji ymj Xjwfyjw xfc Jfxxfwx tk Ymj Jfajw ymj Lztwj Rtyinrzty.";
    int top_count = 5;

    letter_frequency_attack(ciphertext, top_count);

    return 0;
}