#include "railfence.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>
using namespace std;

wstring_convert<codecvt_utf8<wchar_t>> converter;

int RailFenceCipher::getRow(int position, int rails) {
    int cycle = 2 * rails - 2;
    int posInCycle = position % cycle;
    if (posInCycle < rails) return posInCycle;
    else return 2 * rails - 2 - posInCycle;
}

bool RailFenceCipher::isValidKey(int rails) {
    return (rails >= 2);
}

//шифрование
string RailFenceCipher::encrypt(const string& text, int rails) {
    if (!isValidKey(rails) || text.empty()) return "";

    //ппреобразуем UTF 8 в wstring каждый символ
    wstring wideText = converter.from_bytes(text);

    vector<wstring> railsData(rails);
    for (size_t i = 0; i < wideText.size(); i++) {
        int row = getRow(i, rails);
        railsData[row] += wideText[i];
    }

    wstring result;
    for (int i = 0; i < rails; i++) {
        result += railsData[i];
    }

    // Преобразуем обратно
    return converter.to_bytes(result);
}

//рассшифровка
string RailFenceCipher::decrypt(const string& text, int rails) {
    if (!isValidKey(rails) || text.empty()) return "";

    //преобразуем UTF 8 в wstring
    wstring wideText = converter.from_bytes(text);

    int length = wideText.size();
    int cycle = 2 * rails - 2;

    // Шаг 1 паттерн движения
    vector<int> pattern(length);
    for (int i = 0; i < length; i++) {
        int posInCycle = i % cycle;
        pattern[i] = (posInCycle < rails) ? posInCycle : cycle - posInCycle;
    }

    //Шаг 2 считаем символы в каждом рельсе
    vector<int> count(rails, 0);
    for (int i = 0; i < length; i++) {
        count[pattern[i]]++;
    }

    // Шаг 3: заполняем рельсы
    vector<wstring> railsData(rails);
    int pos = 0;
    for (int i = 0; i < rails; i++) {
        railsData[i] = wideText.substr(pos, count[i]);
        pos += count[i];
    }

    // Шаг 4: восстанавливаем порядок
    wstring result;
    vector<int> idx(rails, 0);
    for (int i = 0; i < length; i++) {
        int row = pattern[i];
        result += railsData[row][idx[row]];
        idx[row]++;
    }

    // преобразуем обратно wstring в UTF 8
    return converter.to_bytes(result);
}

// Шифрование файла
bool RailFenceCipher::encryptFile(const string& inputFile, const string& outputFile, int rails) {
    if (!isValidKey(rails)) {
        cout << "Ошибка: ключ должен быть >= 2" << endl;
        return false;
    }

    ifstream in(inputFile);
    if (!in.is_open()) {
        cout << "Ошибка: не удалось открыть файл" << endl;
        return false;
    }

    string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    string encrypted = encrypt(content, rails);

    ofstream out(outputFile);
    if (!out.is_open()) {
        cout << "Ошибка: не удалось создать файл" << endl;
        return false;
    }

    out << encrypted;
    out.close();
    return true;
}

// Дешифрование файла
bool RailFenceCipher::decryptFile(const string& inputFile, const string& outputFile, int rails) {
    if (!isValidKey(rails)) {
        cout << "Ошибка: ключ должен быть >= 2!" << endl;
        return false;
    }

    ifstream in(inputFile);
    if (!in.is_open()) {
        cout << "Ошибка: не удалось открыть файл" << endl;
        return false;
    }

    string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    string decrypted = decrypt(content, rails);

    ofstream out(outputFile);
    if (!out.is_open()) {
        cout << "Ошибка: не удалось создать файл" << endl;
        return false;
    }

    out << decrypted;
    out.close();
    return true;
}