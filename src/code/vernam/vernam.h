#ifndef VERNAM_H
#define VERNAM_H
#include <string>
#include <vector>
#include <cstdint>

class VernamCipher {
private:
    std::vector<uint8_t> vernam_crypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key);
    
public:
    std::string encrypt(const std::string& text, const std::string& key);
    std::string decrypt(const std::string& text, const std::string& key);
    
    bool encryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);
    bool decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);
    
    bool isValidKey(const std::string& key);
};

#endif 