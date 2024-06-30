#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to perform modular exponentiation
unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    unsigned long long q = 23;  // Example large prime modulus
    unsigned long long a = 5;   // Example primitive root modulo q

    // Alice's secret key
    unsigned long long x = 6;   // Example secret key for Alice
    // Bob's secret key
    unsigned long long y = 15;  // Example secret key for Bob

    // Alice sends Bob a^x mod q
    unsigned long long A = mod_exp(a, x, q);
    // Bob sends Alice a^y mod q
    unsigned long long B = mod_exp(a, y, q);

    // Alice computes the shared secret key
    unsigned long long shared_key_Alice = mod_exp(B, x, q);
    // Bob computes the shared secret key
    unsigned long long shared_key_Bob = mod_exp(A, y, q);

    printf("Standard Diffie-Hellman Key Exchange:\n");
    printf("Alice's computed shared key: %llu\n", shared_key_Alice);
    printf("Bob's computed shared key: %llu\n", shared_key_Bob);

    // Demonstration of insecure method (sending x * a)
    unsigned long long insecure_Alice = x * a;
    unsigned long long insecure_Bob = y * a;

    printf("\nInsecure Method (sending x * a):\n");
    printf("Alice sends: %llu\n", insecure_Alice);
    printf("Bob sends: %llu\n", insecure_Bob);

    // Eve can easily find the secret keys if they are sent as x * a
    unsigned long long eve_Alice_key = insecure_Alice / a;
    unsigned long long eve_Bob_key = insecure_Bob / a;

    printf("Eve's discovered Alice's secret key: %llu\n", eve_Alice_key);
    printf("Eve's discovered Bob's secret key: %llu\n", eve_Bob_key);

    return 0;
}