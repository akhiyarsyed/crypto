#include <stdio.h>
#include <stdint.h>

#define KEY_SIZE 64
#define SUBKEY_SIZE 48

// Initial permutation table (simulated for this example)
int IP[64] = { /* values 1 to 64 in some permutation */ };

// Subset masks
uint64_t MASK1 = 0xFFFFFFF0000000; // Mask for the first 28 bits
uint64_t MASK2 = 0x0000000FFFFFFF; // Mask for the second 28 bits

// Initial key (64 bits)
uint64_t initial_key = 0x133457799BBCDFF1;

// Function to generate subkeys
void generate_subkeys(uint64_t key, uint64_t subkeys[16]) {
    uint64_t left, right;
    
    // Extract the first and second subsets of 28 bits
    left = (key & MASK1) >> 36;  // Get the first 28 bits and align to the left
    right = (key & MASK2);       // Get the second 28 bits
    
    // Simulate the generation of 16 subkeys
    for (int i = 0; i < 16; i++) {
        // Rotate left and right subsets (simulated for simplicity)
        left = (left << 1) | (left >> 27);
        right = (right << 1) | (right >> 27);
        
        // Combine the subsets to form the subkey
        uint64_t subkey = ((left & 0xFFFFFFF) << 24) | (right & 0xFFFFFFF);
        
        // Store the subkey
        subkeys[i] = subkey & 0xFFFFFFFFFFFF; // Ensure it's 48 bits
    }
}

int main() {
    uint64_t subkeys[16];
    
    // Generate the subkeys
    generate_subkeys(initial_key, subkeys);
    
    // Print the subkeys
    for (int i = 0; i < 16; i++) {
        printf("Subkey %2d: %012llX\n", i + 1, subkeys[i]);
    }
    
    return 0;
}