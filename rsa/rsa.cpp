#include "rsa.h"

// Быстрое модульное возведение в степень
uint64_t ModPow(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

extern "C" {
void RSA_Encrypt(const uint8_t* in, size_t in_len, uint16_t* out, uint32_t e, uint32_t n) {
    for (size_t i = 0; i < in_len; i++) {
        // c = m^e mod n
        out[i] = static_cast<uint16_t>(ModPow(in[i], e, n));
    }
}

void RSA_Decrypt(const uint16_t* in, size_t in_len, uint8_t* out, uint32_t d, uint32_t n) {
    for (size_t i = 0; i < in_len; i++) {
        // m = c^d mod n
        out[i] = static_cast<uint8_t>(ModPow(in[i], d, n));
    }
}
}