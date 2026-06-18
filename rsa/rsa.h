#ifndef RSA_H
#define RSA_H

#include <cstdint>
#include <cstddef>

// Функция модульного возведения в степень (base^exp % mod)
uint64_t ModPow(uint64_t base, uint64_t exp, uint64_t mod);

extern "C" {
// Шифрование: массив байт -> массив 16-битных чисел
void RSA_Encrypt(const uint8_t* in, size_t in_len, uint16_t* out, uint32_t e, uint32_t n);

// Дешифрование: массив 16-битных чисел -> массив байт
void RSA_Decrypt(const uint16_t* in, size_t in_len, uint8_t* out, uint32_t d, uint32_t n);
}

#endif // RSA_H