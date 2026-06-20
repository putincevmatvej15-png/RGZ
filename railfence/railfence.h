#ifndef RAILFENCE_H
#define RAILFENCE_H
#include <string>

class RailFenceCipher {
private:
    int getRow(int position, int rails);

public:
    bool isValidKey(int rails);

    std::string encrypt(const std::string& text, int rails);
    std::string decrypt(const std::string& text, int rails);

    bool encryptFile(const std::string& inputFile, const std::string& outputFile, int rails);
    bool decryptFile(const std::string& inputFile, const std::string& outputFile, int rails);

    std::string getName() { return "Rail Fence (Зигзаг)"; }
    std::string getKeyHint() { return "целое число >= 2 (количество рельсов)"; }
};
#endif
