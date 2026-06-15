#include "tritemius.h"
#include <fstream>
#include <iostream>

std::vector<uint8_t> TritemiusCipher::tritemius_crypt(const std::vector<uint8_t>& data, bool encrypt) {
    std::vector<uint8_t> result(data.size());
    for (size_t i = 0; i < data.size(); i++) {
        int shift = static_cast<int>(i % 256); 
        if (encrypt) {
            result[i] = static_cast<uint8_t>((data[i] + shift) % 256);
        } else {
            int val = data[i] - shift;
            while (val < 0) val += 256;
            result[i] = static_cast<uint8_t>(val % 256);
        }
    }
    return result;
}

std::string TritemiusCipher::encrypt(const std::string& text) {
    if (text.empty()) return "";
    std::vector<uint8_t> data_bytes(text.begin(), text.end());
    std::vector<uint8_t> cipher_bytes = tritemius_crypt(data_bytes, true);
    return std::string(cipher_bytes.begin(), cipher_bytes.end());
}

std::string TritemiusCipher::decrypt(const std::string& text) {
    if (text.empty()) return "";
    std::vector<uint8_t> data_bytes(text.begin(), text.end());
    std::vector<uint8_t> cipher_bytes = tritemius_crypt(data_bytes, false);
    return std::string(cipher_bytes.begin(), cipher_bytes.end());
}

bool TritemiusCipher::encryptFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in.is_open()) return false;
    std::ofstream out(outputFile, std::ios::binary);
    if (!out.is_open()) { in.close(); return false; }
    std::vector<uint8_t> fileData((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    std::vector<uint8_t> processedData = tritemius_crypt(fileData, true);
    out.write(reinterpret_cast<const char*>(processedData.data()), processedData.size());
    in.close();
    out.close();
    std::cout << "Файл обработан Тритемиусом. Байт: " << processedData.size() << std::endl;
    return true;
}

bool TritemiusCipher::decryptFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in.is_open()) return false;
    std::ofstream out(outputFile, std::ios::binary);
    if (!out.is_open()) { in.close(); return false; }
    std::vector<uint8_t> fileData((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    std::vector<uint8_t> processedData = tritemius_crypt(fileData, false);
    out.write(reinterpret_cast<const char*>(processedData.data()), processedData.size());
    in.close();
    out.close();
    return true;
}