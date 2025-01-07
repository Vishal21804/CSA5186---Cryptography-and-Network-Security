#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 16
#define Rb_128 0x87
#define Rb_64 0x1B

void AES_Encrypt(uint8_t *input, uint8_t *output) {
    memcpy(output, input, BLOCK_SIZE);
}

void left_shift(uint8_t *input, uint8_t *output, int size) {
    uint8_t carry = 0;
    for (int i = size - 1; i >= 0; i--) {
        output[i] = (input[i] << 1) | carry;
        carry = input[i] >> 7;
    }
}

void generate_subkeys(uint8_t *K1, uint8_t *K2, int block_size) {
    uint8_t Rb = (block_size == 16) ? Rb_128 : Rb_64;
    uint8_t L[block_size];
    uint8_t zero_block[block_size];
    memset(L, 0, block_size);
    memset(zero_block, 0, block_size);

    AES_Encrypt(zero_block, L);

    left_shift(L, K1, block_size);
    if (L[0] & 0x80) {
        K1[block_size - 1] ^= Rb;
    }

    left_shift(K1, K2, block_size);
    if (K1[0] & 0x80) {
        K2[block_size - 1] ^= Rb;
    }
}

void print_block(uint8_t *block, int size) {
    for (int i = 0; i < size; i++) {
        printf("%02X", block[i]);
    }
    printf("\n");
}

int main() {
    uint8_t K1[BLOCK_SIZE];
    uint8_t K2[BLOCK_SIZE];

    generate_subkeys(K1, K2, BLOCK_SIZE);

    printf("Subkey K1: ");
    print_block(K1, BLOCK_SIZE);

    printf("Subkey K2: ");
    print_block(K2, BLOCK_SIZE);

    return 0;
}
