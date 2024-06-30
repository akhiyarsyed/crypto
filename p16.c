#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_SIZE 1024
double englishFrequencies[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094,
    6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929,
    0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};

// Function to calculate the frequency of each letter in the ciphertext
void calculateFrequency(char *text, double *frequencies) {
    int count[ALPHABET_SIZE] = {0};
    int length = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            count[text[i] - 'a']++;
            length++;
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            count[text[i] - 'A']++;
            length++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i] = ((double) count[i] / length) * 100.0;
    }
}

// Function to map the sorted frequency of ciphertext to the sorted frequency of English
void mapFrequencies(char *ciphertext, char *mapping, double *ciphertextFreq, double *sortedEnglishFreq) {
    int sortedIndices[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sortedIndices[i] = i;
    }

    // Sort indices based on frequencies
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (ciphertextFreq[sortedIndices[i]] < ciphertextFreq[sortedIndices[j]]) {
                int temp = sortedIndices[i];
                sortedIndices[i] = sortedIndices[j];
                sortedIndices[j] = temp;
            }
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        mapping[sortedIndices[i]] = 'a' + i;
    }
}

// Function to decrypt the ciphertext with the given mapping
void decryptWithMapping(char *ciphertext, char *plaintext, char *mapping) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = mapping[ciphertext[i] - 'a'];
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = mapping[ciphertext[i] - 'A'] - ('a' - 'A');
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0';
}

// Structure to hold the decryption candidate and its score
typedef struct {
    double score;
    char plaintext[MAX_TEXT_SIZE];
} DecryptionCandidate;

// Comparison function for sorting candidates by score
int compareCandidates(const void *a, const void *b) {
    DecryptionCandidate *candidateA = (DecryptionCandidate *)a;
    DecryptionCandidate *candidateB = (DecryptionCandidate *)b;
    if (candidateB->score > candidateA->score) return 1;
    else if (candidateB->score < candidateA->score) return -1;
    else return 0;
}

// Function to perform a letter frequency attack on the ciphertext
void letterFrequencyAttack(char *ciphertext, int topN) {
    double ciphertextFrequencies[ALPHABET_SIZE];
    calculateFrequency(ciphertext, ciphertextFrequencies);

    DecryptionCandidate candidates[ALPHABET_SIZE];
    char mapping[ALPHABET_SIZE + 1];

    // Trying different mappings by shifting sorted English frequencies
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        // Create a shifted version of English frequencies
        double shiftedEnglishFreq[ALPHABET_SIZE];
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            shiftedEnglishFreq[i] = englishFrequencies[(i + shift) % ALPHABET_SIZE];
        }

        mapFrequencies(ciphertext, mapping, ciphertextFrequencies, shiftedEnglishFreq);
        decryptWithMapping(ciphertext, candidates[shift].plaintext, mapping);
        
        // Calculate score based on how well frequencies match
        double score = 0.0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            score += ciphertextFrequencies[i] * shiftedEnglishFreq[i];
        }
        candidates[shift].score = score;
    }

    qsort(candidates, ALPHABET_SIZE, sizeof(DecryptionCandidate), compareCandidates);

    printf("Top %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN && i < ALPHABET_SIZE; i++) {
        printf("Score: %.2f, Plaintext: %s\n", candidates[i].score, candidates[i].plaintext);
    }
}

int main() {
    char ciphertext[MAX_TEXT_SIZE];
    int topN;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT_SIZE, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);

    letterFrequencyAttack(ciphertext, topN);

    return 0;
}