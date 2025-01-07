#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define DES_KEY_SIZE 8
#define DES_BLOCK_SIZE 8

void des_encrypt(uint8_t *data, uint8_t *key, uint8_t *output) {
    for (int i = 0; i < DES_BLOCK_SIZE; i++) {
        output[i] = data[i] ^ key[i];
    }
}

void des_decrypt(uint8_t *data, uint8_t *key, uint8_t *output) {
    for (int i = 0; i < DES_BLOCK_SIZE; i++) {
        output[i] = data[i] ^ key[i];
    }
}

void print_bytes(uint8_t *bytes, int size) {
    for (int i = 0; i < size; i++) {
        printf("%02X", bytes[i]);
    }
    printf("\n");
}

int main() {
    uint8_t plaintext[DES_BLOCK_SIZE] = {0x32, 0x43, 0xF6, 0xA8, 0x88, 0x5A, 0x30, 0x8D};
    uint8_t key[DES_KEY_SIZE] = {0x13, 0x34, 0x56, 0x79, 0x9A, 0xBC, 0xDF, 0xF1};
    uint8_t encrypted[DES_BLOCK_SIZE];
    uint8_t decrypted[DES_BLOCK_SIZE];

    printf("Plaintext: ");
    print_bytes(plaintext, DES_BLOCK_SIZE);

    des_encrypt(plaintext, key, encrypted);
    printf("Encrypted (Ciphertext): ");
    print_bytes(encrypted, DES_BLOCK_SIZE);

    des_decrypt(encrypted, key, decrypted);
    printf("Decrypted (Plaintext): ");
    print_bytes(decrypted, DES_BLOCK_SIZE);

    return 0;
}
