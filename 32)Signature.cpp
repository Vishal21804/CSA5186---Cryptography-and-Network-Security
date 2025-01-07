#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

unsigned int hash_message(const char *message) {
    unsigned int hash = 0;
    while (*message) {
        hash = (hash << 5) + *message++;
    }
    return hash;
}

void dsa_sign(const char *message, unsigned int private_key, unsigned int p, unsigned int q, unsigned int g) {
    unsigned int k = rand() % q;
    unsigned int hash = hash_message(message);
    unsigned int r = (g ^ k) % p;
    unsigned int s = (hash + private_key * r) / k % q;
    printf("DSA Signature: r = %u, s = %u\n", r, s);
}

unsigned int rsa_sign(const char *message, unsigned int private_key, unsigned int n) {
    unsigned int hash = hash_message(message);
    return (hash ^ private_key) % n;
}

int main() {
    const char *message = "Test Message";
    unsigned int dsa_private_key = 7;
    unsigned int rsa_private_key = 11;
    unsigned int p = 23, q = 11, g = 5;
    unsigned int n = 77;

    srand(time(NULL));

    printf("Signing with DSA:\n");
    dsa_sign(message, dsa_private_key, p, q, g);
    dsa_sign(message, dsa_private_key, p, q, g);

    printf("\nSigning with RSA:\n");
    unsigned int rsa_signature1 = rsa_sign(message, rsa_private_key, n);
    unsigned int rsa_signature2 = rsa_sign(message, rsa_private_key, n);
    printf("RSA Signature 1: %u\n", rsa_signature1);
    printf("RSA Signature 2: %u\n", rsa_signature2);

    return 0;
}
