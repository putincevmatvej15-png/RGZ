#include "vernam.h"
#include <fstream>
#include <iostream>

std::vector<uint8_t> VernamCipher::vernam_crypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key) {
    std::vector<uint8_t> result(data.size());
    if (key.empty() || data.empty()) return data;
    for (size_t i = 0; i < data.size(); i++) {
        result[i] = data[i] ^ key[i % key.size()];
    }
    return result;
}

bool VernamCipher::isValidKey(const std::string& key) {
    return !key.empty(); 
}

std::string VernamCipher::encrypt(const std::string& text, const std::string& key) {
    if (!isValidKey(key) || text.empty()) return "";
    if (key.size() < text.size()) {
        std::cout << "[Предупреждение]: Ключ короче текста, будет использовано циклическое повторение." << std::endl;
    }
    std::vector<uint8_t> data_bytes(text.begin(), text.end());
    std::vector<uint8_t> key_bytes(key.begin(), key.end());
    std::vector<uint8_t> cipher_bytes = vernam_crypt(data_bytes, key_bytes);
    return std::string(cipher_bytes.begin(), cipher_bytes.end());
}

std::string VernamCipher::decrypt(const std::string& text, const std::string& key) {
    return encrypt(text, key); 
}

bool VernamCipher::encryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key) {
    if (!isValidKey(key)) {
        std::cerr << "Ошибка: неверный ключ!" << std::endl;
        return false;
    }
    std::ifstream in(inputFile, std::ios::binary);
    if (!in.is_open()) return false;
    std::ofstream out(outputFile, std::ios::binary);
    if (!out.is_open()) { in.close(); return false; }
    std::vector<uint8_t> fileData((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    std::vector<uint8_t> key_bytes(key.begin(), key.end());
    std::vector<uint8_t> processedData = vernam_crypt(fileData, key_bytes);
    out.write(reinterpret_cast<const char*>(processedData.data()), processedData.size());
    in.close();
    out.close();
    std::cout << "Файл обработан. Байт: " << processedData.size() << std::endl;
    return true;
}

bool VernamCipher::decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key) {
    return encryptFile(inputFile, outputFile, key);
}