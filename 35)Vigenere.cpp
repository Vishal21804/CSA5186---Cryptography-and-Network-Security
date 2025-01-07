#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ALPHABET_SIZE 26

void generate_key(int *key, int length) {
    for (int i = 0; i < length; i++) {
        key[i] = rand() % ALPHABET_SIZE;
    }
}

void otp_vigenere_encrypt(char *plaintext, int *key, char *ciphertext) {
    int length = strlen(plaintext);
    for (int i = 0; i < length; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((plaintext[i] - 'A' + key[i]) % ALPHABET_SIZE) + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((plaintext[i] - 'a' + key[i]) % ALPHABET_SIZE) + 'a';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[length] = '\0';
}

void otp_vigenere_decrypt(char *ciphertext, int *key, char *plaintext) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((ciphertext[i] - 'A' - key[i] + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((ciphertext[i] - 'a' - key[i] + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0';
}

void print_key(int *key, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", key[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    char plaintext[] = "Hello World!";
    int length = strlen(plaintext);
    int key[length];

    generate_key(key, length);

    printf("Generated Key: ");
    print_key(key, length);

    char ciphertext[length + 1];
    otp_vigenere_encrypt(plaintext, key, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    char decrypted[length + 1];
    otp_vigenere_decrypt(ciphertext, key, decrypted);

    printf("Decrypted: %s\n", decrypted);

    return 0;
}
