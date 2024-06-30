#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// Function to check if a number is prime
int is_prime(unsigned long long num) {
    if (num <= 1) return 0;
    if (num <= 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;
    for (unsigned long long i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return 0;
    }
    return 1;
}

// Function to generate a random prime number
unsigned long long generate_prime() {
    unsigned long long prime;
    do {
        prime = rand() % 100 + 100; // Generate a random number in the range [100, 199]
    } while (!is_prime(prime));
    return prime;
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    // Step 1: Generate two distinct prime numbers p and q
    unsigned long long p = generate_prime();
    unsigned long long q;
    do {
        q = generate_prime();
    } while (p == q);

    // Step 2: Compute n = p * q
    unsigned long long n = p * q;

    // Step 3: Compute phi(n) = (p-1) * (q-1)
    unsigned long long phi = (p - 1) * (q - 1);

    // Step 4: Choose e such that 1 < e < phi(n) and gcd(e, phi(n)) = 1
    unsigned long long e;
    do {
        e = rand() % (phi - 2) + 2; // Generate a random number in the range [2, phi-1]
    } while (gcd(e, phi) != 1);

    // Step 5: Compute d as the modular inverse of e modulo phi(n)
    unsigned long long d = mod_inverse(e, phi);

    printf("New RSA keys generated:\n");
    printf("Public key (e, n) = (%llu, %llu)\n", e, n);
    printf("Private key (d, n) = (%llu, %llu)\n", d, n);

    return 0;
}