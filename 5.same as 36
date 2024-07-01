#include <stdio.h>
#include <string.h>
#include <ctype.h>


int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}


int isValidA(int a) {
    return gcd(a, 26) == 1;
}


void affineEncrypt(char* plaintext, int a, int b, char* ciphertext) {
    int i;
    char ch;

    for (i = 0; plaintext[i] != '\0'; ++i) {
        ch = plaintext[i];

        if (isupper(ch)) {
            ciphertext[i] = ((a * (ch - 'A') + b) % 26) + 'A';
        } else if (islower(ch)) {
            ciphertext[i] = ((a * (ch - 'a') + b) % 26) + 'a';
        } else {
            ciphertext[i] = ch; 
        }
    }
    ciphertext[i] = '\0'; 
}

int main() {
    char plaintext[100];
    char ciphertext[100];
    int a, b;

    
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; 

    
    printf("Enter value for a: ");
    scanf("%d", &a);
    printf("Enter value for b: ");
    scanf("%d", &b);

    
    if (!isValidA(a)) {
        printf("Invalid value for a. 'a' must be coprime with 26.\n");
        return 1;
    }

    
    affineEncrypt(plaintext, a, b, ciphertext);

    
    printf("Encrypted string: %s\n", ciphertext);

    return 0;
}
