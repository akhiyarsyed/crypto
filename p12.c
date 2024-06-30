#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MATRIX_SIZE 2
void hill_cipher_encrypt(int key[MATRIX_SIZE][MATRIX_SIZE], int plaintext[], int n, int encrypted[]) {
    int i, j, k;
    int sum;
    for (i = 0; i < n; i += MATRIX_SIZE) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            sum = 0;
            for (k = 0; k < MATRIX_SIZE; k++) {
                sum += key[j][k] * plaintext[i + k];
            }
            encrypted[i + j] = sum % 26;
        }
    }
}
void hill_cipher_decrypt(int key[MATRIX_SIZE][MATRIX_SIZE], int ciphertext[], int n, int decrypted[]) {
    // Calculate the modular inverse of the determinant of the key matrix modulo 26
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    int det_inv = 0;
    
    // Find modular inverse of determinant
    for (int i = 1; i < 26; i++) {
        if ((det * i) % 26 == 1) {
            det_inv = i;
            break;
        }
    }

    // Calculate the inverse key matrix
    int inv_key[MATRIX_SIZE][MATRIX_SIZE];
    inv_key[0][0] = key[1][1];
    inv_key[0][1] = -key[0][1];
    inv_key[1][0] = -key[1][0];
    inv_key[1][1] = key[0][0];
    
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            inv_key[i][j] = (inv_key[i][j] * det_inv) % 26;
            if (inv_key[i][j] < 0) {
                inv_key[i][j] += 26; // Ensure positive result
            }
        }
    }

    // Decrypt the ciphertext
    hill_cipher_encrypt(inv_key, ciphertext, n, decrypted);
}

int main() {
    int key[MATRIX_SIZE][MATRIX_SIZE] = {
        {9, 4},
        {5, 7}
    };
    char plaintext[] = "meetmeattheusualplaceattenratherthaneightoclock";
    int n = strlen(plaintext);

    int numerical_plaintext[n];
    for (int i = 0; i < n; i++) {
        numerical_plaintext[i] = plaintext[i] - 'a'; 
    }

    int encrypted[n];
    hill_cipher_encrypt(key, numerical_plaintext, n, encrypted);

    printf("Encrypted ciphertext: ");
    for (int i = 0; i < n; i++) {
        printf("%c", encrypted[i] + 'a'); 
    }
    printf("\n");

    int decrypted[n];
    hill_cipher_decrypt(key, encrypted, n, decrypted);

    printf("Decrypted plaintext: ");
    for (int i = 0; i < n; i++) {
        printf("%c", decrypted[i] + 'a'); 
    }
    printf("\n");

    return 0;
}
