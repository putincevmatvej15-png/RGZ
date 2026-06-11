#ifndef XOR_H
#define XOR_H
#include <string>

class XORCipher {
private:
    int generateGamma(int seed, int position);
    
public:
    bool isValidKey(const std::string& key);
    std::string encrypt(const std::string& text, const std::string& key);
    std::string decrypt(const std::string& text, const std::string& key);
    bool encryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);
    bool decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);
    std::string getName() { return "XOR (Гаммирование)"; }
    std::string getKeyHint() { return "целое число (например, 42)"; }
};

#endif
