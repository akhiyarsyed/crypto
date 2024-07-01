#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int mod(int a, int b) {
    int result = a % b;
    return result >= 0 ? result : result + b;
}

int mod_inverse(int a, int m) {
    a = mod(a, m);
    for (int x = 1; x < m; x++) {
        if (mod((a * x), m) == 1) {
            return x;
        }
    }
    return -1;
}

void decrypt_hill_cipher(int key[2][2], const char *ciphertext, char *plaintext) {
    int det_inverse = mod_inverse(mod(key[0][0] * key[1][1] - key[0][1] * key[1][0], 26), 26);

    for (int i = 0; ciphertext[i] != '\0'; i += 2) {
        int c1 = ciphertext[i] - 'A';
        int c2 = ciphertext[i + 1] - 'A';

        int p1 = mod(det_inverse * (key[1][1] * c1 - key[0][1] * c2), 26);
        int p2 = mod(det_inverse * (-key[1][0] * c1 + key[0][0] * c2), 26);

        plaintext[i] = p1 + 'A';
        plaintext[i + 1] = p2 + 'A';
    }

    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    int key[2][2];
    char plaintext[1000], ciphertext[1000];

    strcpy(plaintext, "HELLO"); // Sample known plaintext
    strcpy(ciphertext, "RIJVS"); // Corresponding ciphertext

    for (int i = 0; plaintext[i] != '\0'; i++) {
        plaintext[i] = toupper(plaintext[i]);
    }
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        ciphertext[i] = toupper(ciphertext[i]);
    }

    int n = strlen(plaintext);
    if (n % 2 != 0) {
        printf("Invalid input lengths. Plaintext and ciphertext should have the same length.\n");
        return 1;
    }

    for (int i = 0; i < n; i += 2) {
        int p1 = plaintext[i] - 'A';
        int p2 = plaintext[i + 1] - 'A';

        int c1 = ciphertext[i] - 'A';
        int c2 = ciphertext[i + 1] - 'A';

        key[0][0] = mod_inverse(p1 - p2, 26) * (c1 - c2);
        key[0][1] = mod_inverse(p1 - p2, 26) * (p1 * c2 - p2 * c1);
        key[1][0] = mod_inverse(p2 - p1, 26) * (c2 - c1);
        key[1][1] = mod_inverse(p2 - p1, 26) * (p2 * c1 - p1 * c2);
    }

    decrypt_hill_cipher(key, ciphertext, plaintext);

    printf("Decrypted Plaintext: %s\n", plaintext);

    return 0;
}
