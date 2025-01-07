#include <stdio.h>

int extendedGCD(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extendedGCD(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

int modInverse(int e, int phi) {
    int x, y;
    int gcd = extendedGCD(e, phi, &x, &y);
    if (gcd != 1) {
        return -1; 
    } else {
        return (x % phi + phi) % phi;
    }
}

int modularExponentiation(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    int e = 31, n = 3599;
    int p = 59, q = 61; 
    int phi = (p - 1) * (q - 1);
    int d = modInverse(e, phi);

    if (d == -1) {
        printf("No modular inverse exists for e = %d and f(n) = %d\n", e, phi);
        return 1;
    }

    printf("Public Key (e, n): (%d, %d)\n", e, n);
    printf("Private Key (d, n): (%d, %d)\n", d, n);

    int plaintext = 123; 
    int ciphertext = modularExponentiation(plaintext, e, n);
    int decryptedText = modularExponentiation(ciphertext, d, n);

    printf("Plaintext: %d\n", plaintext);
    printf("Ciphertext: %d\n", ciphertext);
    printf("Decrypted Text: %d\n", decryptedText);

    return 0;
}
