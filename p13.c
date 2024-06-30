#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 3  // Define the size of the key matrix (e.g., 3x3 for simplicity)
#define MODULUS 26     // Define the modulus for the Hill cipher (26 for English alphabet)

// Function to compute the modular inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
       if ((a * x) % m == 1)
          return x;
    return -1;
}

// Function to compute the determinant of a matrix
int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE], int n) {
    int det = 0;
    if (n == 1)
        return matrix[0][0];
    
    int temp[MATRIX_SIZE][MATRIX_SIZE];
    int sign = 1;

    for (int f = 0; f < n; f++) {
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == f)
                    continue;
                temp[subi][subj] = matrix[i][j];
                subj++;
            }
            subi++;
        }
        det = det + (sign * matrix[0][f] * determinant(temp, n - 1));
        sign = -sign;
    }
    return det;
}

// Function to compute the adjoint of a matrix
void adjoint(int matrix[MATRIX_SIZE][MATRIX_SIZE], int adj[MATRIX_SIZE][MATRIX_SIZE]) {
    if (MATRIX_SIZE == 1) {
        adj[0][0] = 1;
        return;
    }

    int sign = 1, temp[MATRIX_SIZE][MATRIX_SIZE];

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            int subi = 0;
            for (int row = 0; row < MATRIX_SIZE; row++) {
                if (row == i)
                    continue;
                int subj = 0;
                for (int col = 0; col < MATRIX_SIZE; col++) {
                    if (col == j)
                        continue;
                    temp[subi][subj] = matrix[row][col];
                    subj++;
                }
                subi++;
            }
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign * determinant(temp, MATRIX_SIZE - 1));
        }
    }
}

// Function to compute the inverse of a matrix
int inverse(int matrix[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(matrix, MATRIX_SIZE);
    int invDet = modInverse(det, MODULUS);
    if (invDet == -1) {
        printf("Matrix is not invertible\n");
        return 0;
    }

    int adj[MATRIX_SIZE][MATRIX_SIZE];
    adjoint(matrix, adj);

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            inverse[i][j] = (adj[i][j] * invDet) % MODULUS;
            if (inverse[i][j] < 0)
                inverse[i][j] += MODULUS;
        }
    }
    return 1;
}

// Function to print a matrix
void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to multiply two matrices
void multiplyMatrices(int mat1[MATRIX_SIZE][MATRIX_SIZE], int mat2[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
            result[i][j] %= MODULUS;
        }
    }
}

// Function to perform the known plaintext attack
void knownPlaintextAttack(int plaintext[MATRIX_SIZE][MATRIX_SIZE], int ciphertext[MATRIX_SIZE][MATRIX_SIZE]) {
    int inversePlaintext[MATRIX_SIZE][MATRIX_SIZE];
    
    if (!inverse(plaintext, inversePlaintext)) {
        printf("Failed to compute inverse of the plaintext matrix.\n");
        return;
    }

    int keyMatrix[MATRIX_SIZE][MATRIX_SIZE];
    multiplyMatrices(ciphertext, inversePlaintext, keyMatrix);

    printf("The key matrix is:\n");
    printMatrix(keyMatrix);
}

int main() {
    int plaintext[MATRIX_SIZE][MATRIX_SIZE] = {
        {6, 24, 1},
        {13, 16, 10},
        {20, 17, 15}
    };

    int ciphertext[MATRIX_SIZE][MATRIX_SIZE] = {
        {8, 5, 10},
        {21, 8, 21},
        {21, 12, 8}
    };

    printf("Known plaintext matrix:\n");
    printMatrix(plaintext);

    printf("Known ciphertext matrix:\n");
    printMatrix(ciphertext);

    knownPlaintextAttack(plaintext, ciphertext);

    return 0;
}