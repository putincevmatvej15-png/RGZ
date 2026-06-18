#ifndef RSA_H
#define RSA_H

#include <cstdint>
#include <cstddef>

// Функция модульного возведения в степень
uint64_t ModPow(uint64_t base, uint64_t exp, uint64_t mod);

extern "C" {
// Шифрование
void RSA_Encrypt(const uint8_t* in, size_t in_len, uint16_t* out, uint32_t e, uint32_t n);

// Дешифрование
void RSA_Decrypt(const uint16_t* in, size_t in_len, uint8_t* out, uint32_t d, uint32_t n);
}

#endif