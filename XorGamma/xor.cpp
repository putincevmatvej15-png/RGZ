#include "xor.h"
#include <fstream>
#include <iostream>
#include <vector>

// Генератор гаммы псевдослучайной последовательности
//Используем линейный конгруэнтный генератор
int XORCipher::generateGamma(int seed, int position) {
    unsigned int state = seed;
    // вычисление X_{n+1} = (a * X_n + c) mod m
    const unsigned int a = 1103515245;
    const unsigned int c = 12345;
    const unsigned int m = 256;
    
    for (int i = 0; i <= position; i++) {
        state = (a * state + c) % m;
    }
    return state;
}

//Проверка что ключ  это целое число
bool XORCipher::isValidKey(const std::string& key) {
    if (key.empty()) return false;
    for (char c : key) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

// Шифрование строки
std::string XORCipher::encrypt(const std::string& text, const std::string& key) {
    if (!isValidKey(key) || text.empty()) {
        return "";
    }
    
    int seed = std::stoi(key);
    std::string result = text;
    
    for (size_t i = 0; i < text.size(); i++) {
        int gamma = generateGamma(seed, i);
        result[i] = text[i] ^ gamma;
    }
    
    return result;
}

//Дешифрование строки
std::string XORCipher::decrypt(const std::string& text, const std::string& key) {
    return encrypt(text, key);
}

//Шифрование файла работа с любыми файлами текст картинки документы
bool XORCipher::encryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key) {
    if (!isValidKey(key)) {
        std::cerr << "Ошибка: неверный ключ!" << std::endl;
        return false;
    }
    
    // Открываем входной файл бинарный режим
    std::ifstream in(inputFile, std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "Ошибка не удалось открыть файл " << inputFile << std::endl;
        return false;
    }
    
    // Открываем выходной файл бинарный режим
    std::ofstream out(outputFile, std::ios::binary);
    if (!out.is_open()) {
        std::cerr << "Ошибка не удалось создать файл " << outputFile << std::endl;
        in.close();
        return false;
    }
    
    int seed = std::stoi(key);
    char byte;
    int position = 0;
    
    //Читаем файл побайтово и шифруем
    while (in.get(byte)) {
        int gamma = generateGamma(seed, position);
        char encryptedByte = byte ^ gamma;
        out.put(encryptedByte);
        position++;
    }
    
    in.close();
    out.close();
    
    std::cout << "Файл обработан обработано байт " << position << std::endl;
    return true;
}

//Дешифрование файла
bool XORCipher::decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key) {
    return encryptFile(inputFile, outputFile, key);
}
