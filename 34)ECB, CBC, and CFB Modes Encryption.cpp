#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8
#define KEY_SIZE 8

void xor_block(uint8_t *a, uint8_t *b, uint8_t *out) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        out[i] = a[i] ^ b[i];
    }
}

void ecb_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext, int length) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ key[j];
        }
    }
}

void cbc_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *iv, uint8_t *ciphertext, int length) {
    uint8_t previous_block[BLOCK_SIZE];
    memcpy(previous_block, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        uint8_t block[BLOCK_SIZE];
        xor_block(plaintext + i, previous_block, block);
        ecb_encrypt(block, key, ciphertext + i, BLOCK_SIZE);
        memcpy(previous_block, ciphertext + i, BLOCK_SIZE);
    }
}

void cfb_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *iv, uint8_t *ciphertext, int length) {
    uint8_t shift_register[BLOCK_SIZE];
    memcpy(shift_register, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i++) {
        uint8_t output[BLOCK_SIZE];
        ecb_encrypt(shift_register, key, output, BLOCK_SIZE);
        ciphertext[i] = plaintext[i] ^ output[0];
        memmove(shift_register, shift_register + 1, BLOCK_SIZE - 1);
        shift_register[BLOCK_SIZE - 1] = ciphertext[i];
    }
}

void print_bytes(uint8_t *bytes, int size) {
    for (int i = 0; i < size; i++) {
        printf("%02X", bytes[i]);
    }
    printf("\n");
}

int main() {
    uint8_t plaintext[] = "Hello, World! This is a test message."; 
    uint8_t key[KEY_SIZE] = {0x13, 0x34, 0x56, 0x79, 0x9A, 0xBC, 0xDF, 0xF1};
    uint8_t iv[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    int length = strlen((char*)plaintext);
    
    uint8_t encrypted_ecb[length];
    uint8_t encrypted_cbc[length];
    uint8_t encrypted_cfb[length];

    printf("Plaintext: ");
    print_bytes(plaintext, length);

    ecb_encrypt(plaintext, key, encrypted_ecb, length);
    printf("Encrypted (ECB): ");
    print_bytes(encrypted_ecb, length);

    cbc_encrypt(plaintext, key, iv, encrypted_cbc, length);
    printf("Encrypted (CBC): ");
    print_bytes(encrypted_cbc, length);

    cfb_encrypt(plaintext, key, iv, encrypted_cfb, length);
    printf("Encrypted (CFB): ");
    print_bytes(encrypted_cfb, length);

    return 0;
}
