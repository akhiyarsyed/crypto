#include <stdio.h>
#include <stdlib.h>

// Function to compute the GCD of two numbers
unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to compute the modular inverse of e modulo phi
unsigned long long mod_inverse(unsigned long long e, unsigned long long phi) {
    unsigned long long t = 0, newt = 1;
    unsigned long long r = phi, newr = e;
    while (newr != 0) {
        unsigned long long quotient = r / newr;
        unsigned long long temp = newt;
        newt = t - quotient * newt;
        t = temp;
        temp = newr;
        newr = r - quotient * newr;
        r = temp;
    }
    if (t < 0) {
        t = t + phi;
    }
    return t;
}

int main() {
    unsigned long long n = 221; // Example n = pq, replace with your n
    unsigned long long e = 5;   // Example public key e, replace with your e
    unsigned long long m = 34;  // Example plaintext block m, replace with your m

    // Step 1: Find the common factor of m and n
    unsigned long long p = gcd(m, n);
    if (p == 1 || p == n) {
        printf("No common factor found.\n");
        return 1;
    }

    // Step 2: Factor n to find q
    unsigned long long q = n / p;

    // Step 3: Compute phi(n)
    unsigned long long phi = (p - 1) * (q - 1);

    // Step 4: Compute the private key d
    unsigned long long d = mod_inverse(e, phi);

    printf("p = %llu\n", p);
    printf("q = %llu\n", q);
    printf("phi(n) = %llu\n", phi);
    printf("Private key d = %llu\n", d);

    return 0;
}