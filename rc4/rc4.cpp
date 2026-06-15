#include "rc4.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

// Внутренний метод генерации гаммы RC4 и побайтового XOR
vector<uint8_t> RC4Cipher::rc4_crypt(const vector<uint8_t>& data, const vector<uint8_t>& key) {
    vector<uint8_t> result(data.size());
    if (key.empty() || data.empty()) return data;

    // Инициализация S-блока (массив от 0 до 255)
    vector<uint8_t> s(256);
    for (int i = 0; i < 256; ++i) {
        s[i] = i;
    }

    // Алгоритм генерации ключа KSA (перемешивание элементов S-блока на основе ключа)
    int j = 0;
    for (int i = 0; i < 256; ++i) {
        j = (j + s[i] + key[i % key.size()]) % 256;
        swap(s[i], s[j]);
    }

    // Генератор псевдослучайных чисел PRGA и наложение гаммы через XOR
    int i = 0;
    j = 0;
    for (size_t k = 0; k < data.size(); ++k) {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        swap(s[i], s[j]);
        
        uint8_t prga_byte = s[(s[i] + s[j]) % 256]; // Получаем байт гаммы
        result[k] = data[k] ^ prga_byte;            // Смешиваем с исходным текстом
    }

    return result;
}

string RC4Cipher::encrypt(const string& text, const string& key) {
    vector<uint8_t> data_bytes(text.begin(), text.end());
    vector<uint8_t> key_bytes(key.begin(), key.end());
    vector<uint8_t> crypt_bytes = rc4_crypt(data_bytes, key_bytes);
    return string(crypt_bytes.begin(), crypt_bytes.end());
}

string RC4Cipher::decrypt(const string& text, const string& key) {
    // В RC4 операции шифрования и расшифрования полностью идентичны
    return encrypt(text, key);
}

bool RC4Cipher::encryptFile(const string& inputFile, const string& outputFile, const string& key) {
    if (!isValidKey(key)) return false;

    ifstream in(inputFile, ios::binary);
    if (!in.is_open()) return false;

    ofstream out(outputFile, ios::binary);
    if (!out.is_open()) {
        in.close();
        return false;
    }

    // Чтение данных файла в бинарный буфер
    vector<uint8_t> fileData((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    vector<uint8_t> key_bytes(key.begin(), key.end());

    vector<uint8_t> processedData = rc4_crypt(fileData, key_bytes);

    out.write(reinterpret_cast<const char*>(processedData.data()), processedData.size());

    in.close();
    out.close();
    return true;
}

bool RC4Cipher::decryptFile(const string& inputFile, const string& outputFile, const string& key) {
    return encryptFile(inputFile, outputFile, key);
}

bool RC4Cipher::isValidKey(const string& key) {
    return !key.empty();
}