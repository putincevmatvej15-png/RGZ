#ifndef AFFINE_H
#define AFFINE_H

#include <cstdint>
#include <cstddef>

// Функция поиска модульной инверсии (нужна для расшифрования)
uint8_t ModInverse(uint8_t a);

// Экспортируемые функции с C-связыванием для динамической загрузки
extern "C" {
    
    // Функция побайтового шифрования/дешифрования Аффинного шифра
    // data    - указатель на массив байт (входные данные изменятся прямо в памяти)
    // len     - количество байт (размер файла/данных)
    // key_a   - первый множитель ключа (должен быть взаимно прост с 256, т.е. нечетным)
    // key_b   - сдвиг ключа
    // encrypt - true для шифрования, false для дешифрования
    void ProcessData(uint8_t* data, size_t len, int key_a, int key_b, bool encrypt);

}

#endif // AFFINE_H