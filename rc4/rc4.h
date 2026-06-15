#ifndef RC4_H
#define RC4_H
#include <string>
#include <vector>
#include <stdint.h>

class RC4Cipher {
private:
    // Внутренний метод алгоритма RC4 (генерация гаммы + XOR)
    std::vector<uint8_t> rc4_crypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key);
    
public:
    // Шифрование/дешифрование строки
    std::string encrypt(const std::string& text, const std::string& key);
    std::string decrypt(const std::string& text, const std::string& key);
    
    // Шифрование/дешифрование файла
    bool encryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);
    bool decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);
    
    // Проверка ключа (для RC4 достаточно, чтобы ключ просто не был пустым)
    bool isValidKey(const std::string& key);
};

#endif // RC4_H