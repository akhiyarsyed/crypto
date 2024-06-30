#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_SIZE 1024

// English letter frequencies (approximate)
double englishFrequencies[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094,
    6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929,
    0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};

// Function to calculate the frequency score of a text
double frequencyScore(char *text) {
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

    double score = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        double frequency = ((double) count[i] / length) * 100.0;
        score += frequency * englishFrequencies[i];
    }

    return score;
}

// Function to decrypt the ciphertext with a given key
void decrypt(char *ciphertext, int key, char *plaintext) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((ciphertext[i] - 'a' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((ciphertext[i] - 'A' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0';
}

// Structure to hold the key and its score
typedef struct {
    int key;
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

// Function to perform a letter frequency attack
void letterFrequencyAttack(char *ciphertext, int topN) {
    DecryptionCandidate candidates[ALPHABET_SIZE];

    for (int key = 0; key < ALPHABET_SIZE; key++) {
        decrypt(ciphertext, key, candidates[key].plaintext);
        candidates[key].key = key;
        candidates[key].score = frequencyScore(candidates[key].plaintext);
    }

    qsort(candidates, ALPHABET_SIZE, sizeof(DecryptionCandidate), compareCandidates);

    printf("Top %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN && i < ALPHABET_SIZE; i++) {
        printf("Key: %d, Score: %.2f, Plaintext: %s\n", candidates[i].key, candidates[i].score, candidates[i].plaintext);
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