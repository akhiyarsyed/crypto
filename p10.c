#include <stdio.h>
#include <string.h>
#include <ctype.h>
void findPosition(char matrix[5][5], char ch, int *row, int *col) {
    if (ch == 'J')  
        ch = 'I';
    for (*row = 0; *row < 5; (*row)++) {
        for (*col = 0; *col < 5; (*col)++) {
            if (matrix[*row][*col] == ch)
                return;
        }
    }
}
void encryptPlayfair(char message[], char matrix[5][5]) {
    int len = strlen(message);
    char ciphertext[len * 2];  
    int k = 0;
    int j = 0;
    char processed_message[len];
    for (int i = 0; i < len; i++) {
        char ch = toupper(message[i]);
        if (isalpha(ch)) {
            processed_message[j++] = ch;
        }
    }
    processed_message[j] = '\0';
    len = j;

    // Encrypt the processed message
    for (int i = 0; i < len; i += 2) {
        char a = processed_message[i];
        char b = (i + 1 < len) ? processed_message[i + 1] : 'X';  // 'X' padding if message length is odd
        int row1, col1, row2, col2;

        // Find positions in the matrix
        findPosition(matrix, a, &row1, &col1);
        findPosition(matrix, b, &row2, &col2);

        if (row1 == row2) {
            // Same row, shift right
            ciphertext[k++] = matrix[row1][(col1 + 1) % 5];
            ciphertext[k++] = matrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            // Same column, shift down
            ciphertext[k++] = matrix[(row1 + 1) % 5][col1];
            ciphertext[k++] = matrix[(row2 + 1) % 5][col2];
        } else {
            // Form a rectangle, swap corners
            ciphertext[k++] = matrix[row1][col2];
            ciphertext[k++] = matrix[row2][col1];
        }
    }

    ciphertext[k] = '\0';  // Null terminate the ciphertext string
    printf("Encrypted Message:\n%s\n", ciphertext);
}

int main() {
    char matrix[5][5] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };

    char message[] = "Must see you over Cadogan West. Coming at once.";

    encryptPlayfair(message, matrix);

    return 0;
}