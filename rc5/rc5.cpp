#include "rc5.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

uint32_t RC5Cipher::rotl(uint32_t x, uint32_t y) {
    y &= 31;
    if (y == 0) return x;
    return ((x << y) | (x >> (32 - y)));
}

uint32_t RC5Cipher::rotr(uint32_t x, uint32_t y) {
    y &= 31;
    if (y == 0) return x;
    return ((x >> y) | (x << (32 - y)));
}

void RC5Cipher::keyExpansion(const vector<uint8_t>& key) {
    int b = key.size();
    int c = (b + 3) / 4;
    if (c == 0) c = 1;
    vector<uint32_t> L(c, 0);
    
    for (int i = b - 1; i >= 0; i--) {
        L[i / 4] = (L[i / 4] << 8) + key[i];
    }
    
    int t = 2 * (rounds + 1);
    S.resize(t);
    S[0] = P32;
    for (int i = 1; i < t; i++) {
        S[i] = S[i - 1] + Q32;
    }
    
    uint32_t A = 0, B = 0;
    int i = 0, j = 0;
    int v = 3 * max(c, t);
    
    for (int s = 0; s < v; s++) {
        S[i] = rotl(S[i] + A + B, 3);
        A = S[i];
        L[j] = rotl(L[j] + A + B, A + B);
        B = L[j];
        i = (i + 1) % t;
        j = (j + 1) % c;
    }
}

void RC5Cipher::encryptBlock(uint32_t& A, uint32_t& B) {
    A += S[0];
    B += S[1];
    for (int i = 1; i <= rounds; i++) {
        A = rotl(A ^ B, B) + S[2 * i];
        B = rotl(B ^ A, A) + S[2 * i + 1];
    }
}

void RC5Cipher::decryptBlock(uint32_t& A, uint32_t& B) {
    for (int i = rounds; i >= 1; i--) {
        B = rotr(B - S[2 * i + 1], A) ^ A;
        A = rotr(A - S[2 * i], B) ^ B;
    }
    B -= S[1];
    A -= S[0];
}

vector<uint8_t> RC5Cipher::prepareData(const vector<uint8_t>& data) {
    vector<uint8_t> res;
    uint32_t len = data.size();
    // Добавляем 4 байта заголовка с исходной длиной
    res.push_back((len >> 24) & 0xFF);
    res.push_back((len >> 16) & 0xFF);
    res.push_back((len >> 8) & 0xFF);
    res.push_back(len & 0xFF);
    res.insert(res.end(), data.begin(), data.end());
    
    // Добиваем нулями до кратности 8 байт (размер блока RC5)
    while (res.size() % 8 != 0) {
        res.push_back(0);
    }
    return res;
}

string RC5Cipher::encrypt(const string& text, const string& key) {
    vector<uint8_t> key_bytes(key.begin(), key.end());
    keyExpansion(key_bytes);
    
    vector<uint8_t> data_bytes(text.begin(), text.end());
    vector<uint8_t> prepared = prepareData(data_bytes);
    
    vector<uint8_t> result;
    for (size_t i = 0; i < prepared.size(); i += 8) {
        uint32_t A = (prepared[i] << 24) | (prepared[i+1] << 16) | (prepared[i+2] << 8) | prepared[i+3];
        uint32_t B = (prepared[i+4] << 24) | (prepared[i+5] << 16) | (prepared[i+6] << 8) | prepared[i+7];
        
        encryptBlock(A, B);
        
        uint8_t block[8];
        block[0] = (A >> 24) & 0xFF; block[1] = (A >> 16) & 0xFF; block[2] = (A >> 8) & 0xFF; block[3] = A & 0xFF;
        block[4] = (B >> 24) & 0xFF; block[5] = (B >> 16) & 0xFF; block[6] = (B >> 8) & 0xFF; block[7] = B & 0xFF;
        
        result.insert(result.end(), block, block + 8);
    }
    return string(result.begin(), result.end());
}

string RC5Cipher::decrypt(const string& text, const string& key) {
    vector<uint8_t> key_bytes(key.begin(), key.end());
    keyExpansion(key_bytes);
    
    vector<uint8_t> data_bytes(text.begin(), text.end());
    if (data_bytes.size() % 8 != 0 || data_bytes.size() < 8) return "";
    
    vector<uint8_t> decrypted;
    for (size_t i = 0; i < data_bytes.size(); i += 8) {
        uint32_t A = (data_bytes[i] << 24) | (data_bytes[i+1] << 16) | (data_bytes[i+2] << 8) | data_bytes[i+3];
        uint32_t B = (data_bytes[i+4] << 24) | (data_bytes[i+5] << 16) | (data_bytes[i+6] << 8) | data_bytes[i+7];
        
        decryptBlock(A, B);
        
        uint8_t block[8];
        block[0] = (A >> 24) & 0xFF; block[1] = (A >> 16) & 0xFF; block[2] = (A >> 8) & 0xFF; block[3] = A & 0xFF;
        block[4] = (B >> 24) & 0xFF; block[5] = (B >> 16) & 0xFF; block[6] = (B >> 8) & 0xFF; block[7] = B & 0xFF;
        
        decrypted.insert(decrypted.end(), block, block + 8);
    }
    
    if (decrypted.size() < 4) return "";
    // Считываем исходную длину из заголовка
    uint32_t originalLen = (decrypted[0] << 24) | (decrypted[1] << 16) | (decrypted[2] << 8) | decrypted[3];
    if (originalLen > decrypted.size() - 4) return "";
    
    return string(decrypted.begin() + 4, decrypted.begin() + 4 + originalLen);
}

bool RC5Cipher::encryptFile(const string& inputFile, const string& outputFile, const string& key) {
    if (!isValidKey(key)) return false;
    ifstream in(inputFile, ios::binary);
    if (!in.is_open()) return false;
    ofstream out(outputFile, ios::binary);
    if (!out.is_open()) { in.close(); return false; }
    
    vector<uint8_t> fileData((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();
    
    vector<uint8_t> key_bytes(key.begin(), key.end());
    keyExpansion(key_bytes);
    
    vector<uint8_t> prepared = prepareData(fileData);
    vector<uint8_t> processedData;
    
    for (size_t i = 0; i < prepared.size(); i += 8) {
        uint32_t A = (prepared[i] << 24) | (prepared[i+1] << 16) | (prepared[i+2] << 8) | prepared[i+3];
        uint32_t B = (prepared[i+4] << 24) | (prepared[i+5] << 16) | (prepared[i+6] << 8) | prepared[i+7];
        
        encryptBlock(A, B);
        
        uint8_t block[8];
        block[0] = (A >> 24) & 0xFF; block[1] = (A >> 16) & 0xFF; block[2] = (A >> 8) & 0xFF; block[3] = A & 0xFF;
        block[4] = (B >> 24) & 0xFF; block[5] = (B >> 16) & 0xFF; block[6] = (B >> 8) & 0xFF; block[7] = B & 0xFF;
        
        processedData.insert(processedData.end(), block, block + 8);
    }
    
    out.write(reinterpret_cast<const char*>(processedData.data()), processedData.size());
    out.close();
    return true;
}

bool RC5Cipher::decryptFile(const string& inputFile, const string& outputFile, const string& key) {
    if (!isValidKey(key)) return false;
    ifstream in(inputFile, ios::binary);
    if (!in.is_open()) return false;
    ofstream out(outputFile, ios::binary);
    if (!out.is_open()) { in.close(); return false; }
    
    vector<uint8_t> fileData((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();
    
    if (fileData.size() % 8 != 0 || fileData.size() < 8) { out.close(); return false; }
    
    vector<uint8_t> key_bytes(key.begin(), key.end());
    keyExpansion(key_bytes);
    
    vector<uint8_t> decrypted;
    for (size_t i = 0; i < fileData.size(); i += 8) {
        uint32_t A = (fileData[i] << 24) | (fileData[i+1] << 16) | (fileData[i+2] << 8) | fileData[i+3];
        uint32_t B = (fileData[i+4] << 24) | (fileData[i+5] << 16) | (fileData[i+6] << 8) | fileData[i+7];
        
        decryptBlock(A, B);
        
        uint8_t block[8];
        block[0] = (A >> 24) & 0xFF; block[1] = (A >> 16) & 0xFF; block[2] = (A >> 8) & 0xFF; block[3] = A & 0xFF;
        block[4] = (B >> 24) & 0xFF; block[5] = (B >> 16) & 0xFF; block[6] = (B >> 8) & 0xFF; block[7] = B & 0xFF;
        
        decrypted.insert(decrypted.end(), block, block + 8);
    }
    
    if (decrypted.size() < 4) { out.close(); return false; }
    uint32_t originalLen = (decrypted[0] << 24) | (decrypted[1] << 16) | (decrypted[2] << 8) | decrypted[3];
    if (originalLen > decrypted.size() - 4) { out.close(); return false; }
    
    // Записываем только оригинальные данные без заголовка и padding
    out.write(reinterpret_cast<const char*>(decrypted.data() + 4), originalLen);
    out.close();
    return true;
}

bool RC5Cipher::isValidKey(const string& key) {
    return !key.empty() && key.size() <= 255;
}