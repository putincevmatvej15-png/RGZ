#include <cstdint>
#include <cstddef>
#include "affine.h"

// Алгоритм Евклида для поиска модульной инверсии (a^-1 mod 256)
uint8_t ModInverse(uint8_t a) {
    a = a % 256;
    for (int x = 1; x < 256; x++) {
        if ((a * x) % 256 == 1) {
            return static_cast<uint8_t>(x); // Нашли число, обратное к a
        }
    }
    return 1;
}

extern "C" {
    // Основная функция шифрования и дешифрования данных
    void ProcessData(uint8_t* data, size_t len, int key_a, int key_b, bool encrypt) {
        if (key_a % 2 == 0) {
            key_a += 1; 
        }

        if (encrypt) {
            // Формула шифрования: y = (a * x + b) mod 256
            for (size_t i = 0; i < len; i++) {
                data[i] = static_cast<uint8_t>((key_a * data[i] + key_b) % 256);
            }
        } else {
            // Формула дешифрования: x = a^-1 * (y - b) mod 256
            uint8_t a_inv = ModInverse(static_cast<uint8_t>(key_a));
            for (size_t i = 0; i < len; i++) {
                int delta = data[i] - key_b;
                // Корректируем отрицательные значения под остаток
                while (delta < 0) {
                    delta += 256;
                }
                data[i] = static_cast<uint8_t>((a_inv * delta) % 256);
            }
        }
    }
}