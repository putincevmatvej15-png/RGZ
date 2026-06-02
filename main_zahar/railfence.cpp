#include "railfence.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int RailFenceCipher::getRow(int position, int rails) {
    int cycle = 2 * rails - 2;
    int posInCycle = position % cycle;
    
    if (posInCycle < rails) {
        return posInCycle;
    } else {
        return 2 * rails - 2 - posInCycle;
    }
}

bool RailFenceCipher::isValidKey(int rails) {
    return (rails >= 2);
}

string RailFenceCipher::encrypt(const string& text, int rails) {
    if (!isValidKey(rails) || text.empty()) return "";
    
    vector<string> railsData(rails);
    
    for (size_t i = 0; i < text.size(); i++) {
        int row = getRow(i, rails);
        railsData[row] += text[i];
    }
    
    string result;
    for (int i = 0; i < rails; i++) {
        result += railsData[i];
    }
    return result;
}

string RailFenceCipher::decrypt(const string& text, int rails) {
    if (!isValidKey(rails) || text.empty()) return "";
    
    int length = text.size();
    
    vector<int> railsSize(rails, 0);
    for (int i = 0; i < length; i++) {
        int row = getRow(i, rails);
        railsSize[row]++;
    }
    
    vector<string> railsData(rails);
    int pos = 0;
    for (int i = 0; i < rails; i++) {
        railsData[i] = text.substr(pos, railsSize[i]);
        pos += railsSize[i];
    }
    
    string result;
    vector<int> currentPos(rails, 0);
    for (int i = 0; i < length; i++) {
        int row = getRow(i, rails);
        result += railsData[row][currentPos[row]];
        currentPos[row]++;
    }
    
    return result;
}

bool RailFenceCipher::encryptFile(const string& inputFile, const string& outputFile, int rails) {
    if (!isValidKey(rails)) {
        cout << "Ошибка: ключ должен быть >= 2" << endl;
        return false;
    }
    
    ifstream in(inputFile);
    if (!in.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << inputFile << endl;
        return false;
    }
    
    string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();
    
    string encrypted = encrypt(content, rails);
    
    ofstream out(outputFile);
    if (!out.is_open()) {
        cout << "Ошибка: не удалось создать файл " << outputFile << endl;
        return false;
    }
    
    out << encrypted;
    out.close();
    
    cout << "Обработано символов: " << encrypted.size() << endl;
    return true;
}

bool RailFenceCipher::decryptFile(const string& inputFile, const string& outputFile, int rails) {
    if (!isValidKey(rails)) {
        cout << "Ошибка: ключ должен быть >= 2" << endl;
        return false;
    }
    
    ifstream in(inputFile);
    if (!in.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << inputFile << endl;
        return false;
    }
    
    string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();
    
    string decrypted = decrypt(content, rails);
    
    ofstream out(outputFile);
    if (!out.is_open()) {
        cout << "Ошибка: не удалось создать файл " << outputFile << endl;
        return false;
    }
    
    out << decrypted;
    out.close();
    
    cout << "Файл успешно расшифрован" << endl;
    return true;
}
