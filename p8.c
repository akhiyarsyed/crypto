#include <stdio.h>
#include <string.h>
#include <ctype.h>


void generateCipherAlphabet(char *keyword, char *cipherAlphabet) {
    int used[26] = {0}; 
    int len = strlen(keyword);
    int index = 0;

   
    for (int i = 0; i < len; i++) {
        char ch = toupper(keyword[i]);
        if (!used[ch - 'A']) {
            cipherAlphabet[index++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipherAlphabet[index++] = ch;
        }
    }

    cipherAlphabet[26] = '\0'; 
}


void encrypt(char *plaintext, char *cipherAlphabet, char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        char ch = plaintext[i];
        if (isalpha(ch)) {
            if (islower(ch)) {
                ciphertext[i] = tolower(cipherAlphabet[ch - 'a']);
            } else {
                ciphertext[i] = toupper(cipherAlphabet[ch - 'A']);
            }
        } else {
            ciphertext[i] = ch; 
        }
    }
    ciphertext[len] = '\0'; 
}

int main() {
    char keyword[] = "CIPHER"; 
    char plaintext[100], ciphertext[100], cipherAlphabet[27];

    
    generateCipherAlphabet(keyword, cipherAlphabet);

    
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    
    plaintext[strcspn(plaintext, "\n")] = '\0';

    
    encrypt(plaintext, cipherAlphabet, ciphertext);

    
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}