#ifndef RC5_H
#define RC5_H
#include <string>
#include <vector>
#include <stdint.h>

class RC5Cipher {
private:
    // Вспомогательные методы для циклических сдвигов
    uint32_t rotl(uint32_t x, uint32_t y);
    uint32_t rotr(uint32_t x, uint32_t y);
    
    // Расширение ключа и шифрование/дешифрование одного 64-битного блока
    void keyExpansion(const std::vector<uint8_t>& key);
    void encryptBlock(uint32_t& A, uint32_t& B);
    void decryptBlock(uint32_t& A, uint32_t& B);
    
    // Подготовка данных
    std::vector<uint8_t> prepareData(const std::vector<uint8_t>& data);

    // Таблица раундовых ключей
    std::vector<uint32_t> S;
    int rounds = 12;
    uint32_t P32 = 0xB7E15163;
    uint32_t Q32 = 0x9E3779B9;

public:
    // Шифрование/дешифрование строки
    std::string encrypt(const std::string& text, const std::string& key);
    std::string decrypt(const std::string& text, const std::string& key);
    
    // Шифрование/дешифрование файла
    bool encryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);
    bool decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);
    
    // Проверка ключа
    bool isValidKey(const std::string& key);
};
#endif