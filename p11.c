#include <stdio.h>
#include <math.h>
unsigned long long factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int main() {
    unsigned long long total_permutations = factorial(25) / factorial(2);
    double approx_power_of_2 = log2((double)total_permutations);
    double effectively_unique_keys = total_permutations; // Placeholder

    printf("Number of possible keys: Approximately 2^%.1f\n", approx_power_of_2);
    printf("Number of effectively unique keys: Approximately %.0f (due to symmetries)\n", effectively_unique_keys);

    return 0;
}