#ifndef XOR_H
#define XOR_H
#include <string>

class XORCipher {
private:
    int generateGamma(int seed, int position);
    
public:
    //Шифрование/дешифрование строки
    std::string encrypt(const std::string& text, const std::string& key);
    std::string decrypt(const std::string& text, const std::string& key);
    
    //Шифрование/ дешифрование файла
    bool encryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);
    bool decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);
    
    // Проверка ключа ключ должен быть числом
    bool isValidKey(const std::string& key);
};

#endif
