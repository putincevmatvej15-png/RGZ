#include "xor.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int XORCipher::generateGamma(int seed, int position) {
    unsigned int state = seed;
    const unsigned int a = 1103515245;
    const unsigned int c = 12345;
    const unsigned int m = 256;
    
    for (int i = 0; i <= position; i++) {
        state = (a * state + c) % m;
    }
    return state;
}

bool XORCipher::isValidKey(const string& key) {
    if (key.empty()) return false;
    for (char c : key) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

string XORCipher::encrypt(const string& text, const string& key) {
    if (!isValidKey(key) || text.empty()) return "";
    
    int seed = stoi(key);
    string result = text;
    
    for (size_t i = 0; i < text.size(); i++) {
        int gamma = generateGamma(seed, i);
        result[i] = text[i] ^ gamma;
    }
    return result;
}

string XORCipher::decrypt(const string& text, const string& key) {
    return encrypt(text, key);
}

bool XORCipher::encryptFile(const string& inputFile, const string& outputFile, const string& key) {
    if (!isValidKey(key)) {
        cout << "Ошибка: неверный ключ" << endl;
        return false;
    }
    
    ifstream in(inputFile, ios::binary);
    if (!in.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << inputFile << endl;
        return false;
    }
    
    ofstream out(outputFile, ios::binary);
    if (!out.is_open()) {
        cout << "Ошибка: не удалось создать файл " << outputFile << endl;
        in.close();
        return false;
    }
    
    int seed = stoi(key);
    char byte;
    int position = 0;
    
    while (in.get(byte)) {
        int gamma = generateGamma(seed, position);
        char encryptedByte = byte ^ gamma;
        out.put(encryptedByte);
        position++;
    }
    
    in.close();
    out.close();
    
    cout << "Обработано байт: " << position << endl;
    return true;
}

bool XORCipher::decryptFile(const string& inputFile, const string& outputFile, const string& key) {
    return encryptFile(inputFile, outputFile, key);
}
