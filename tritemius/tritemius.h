#ifndef TRITEMIUS_H
#define TRITEMIUS_H
#include <string>
#include <vector>
#include <cstdint>

class TritemiusCipher {
private:
    std::vector<uint8_t> tritemius_crypt(const std::vector<uint8_t>& data, bool encrypt);
    
public:
    std::string encrypt(const std::string& text);
    std::string decrypt(const std::string& text);
    
    bool encryptFile(const std::string& inputFile, const std::string& outputFile);
    bool decryptFile(const std::string& inputFile, const std::string& outputFile);
};

#endif 