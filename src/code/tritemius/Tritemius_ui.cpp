#include "tritemius.h"
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>  
#include <sstream>   
#include <vector>    
#include <cstdio>    
using namespace std;

void showTritemiusMenu() {
    cout << "\nШифр Тритемиуса" << endl;
    cout << "  1. Шифровать текст" << endl;
    cout << "  2. Расшифровать текст" << endl;
    cout << "  3. Шифровать файл" << endl;
    cout << "  4. Расшифровать файл" << endl;
    cout << "  0. Назад" << endl;
    cout << "Выберите действие: ";
}

void tritemiusEncryptText(TritemiusCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string text;
    cout << "\nВведите текст для шифрования: ";
    getline(cin, text);
    if (text.empty()) {
        cout << "Ошибка: текст не может быть пустым!" << endl;
        return;
    }
    string result = cipher.encrypt(text);
    cout << "\nЗашифрованные файлы" << endl;
    cout << "Текст: " << result << endl;
    cout << "HEX: ";

    cout << hex << setfill('0');
    for (unsigned char c : result) {
        cout << setw(2) << (int)c << " ";
    }
    cout << dec << endl;
}

void tritemiusDecryptText(TritemiusCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string input;
    cout << "\nВведите зашифрованный текст: ";
    getline(cin, input);
    
    if (input.empty()) {
        cout << "Ошибка: текст не может быть пустым!" << endl;
        return;
    }
    bool looksLikeHex = true;
    for (char c : input) {
        if (c == ' ') continue;
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))) {
            looksLikeHex = false;
            break;
        }
    }
    
    string textToDecrypt;
    
    if (looksLikeHex && input.find(' ') != string::npos) {
        vector<uint8_t> bytes;
        stringstream ss(input);
        string byte;
        while (ss >> byte) {
            if (byte.length() == 2) {
                bytes.push_back(static_cast<uint8_t>(stoi(byte, nullptr, 16)));
            }
        }
        textToDecrypt = string(bytes.begin(), bytes.end());
        cout << "(Распознано как HEX строка)" << endl;
    } else {
        textToDecrypt = input;
    }
    
    string result = cipher.decrypt(textToDecrypt);
    
    cout << "\n=== РАСШИФРОВАННЫЕ ДАННЫЕ ===" << endl;
    cout << "Текст: " << result << endl;
}

void tritemiusEncryptFile(TritemiusCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string inputFile, outputFile;
    cout << "\nВведите путь к файлу для шифрования: ";
    getline(cin, inputFile);
    cout << "Введите путь для сохранения результата: ";
    getline(cin, outputFile);
    
    if (cipher.encryptFile(inputFile, outputFile)) {
        cout << "Файл зашифрован: " << outputFile << endl;
    } else {
        cout << "Ошибка при шифровании файла" << endl;
    }
}

void tritemiusDecryptFile(TritemiusCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string inputFile, outputFile;
    cout << "\nВведите путь к зашифрованному файлу: ";
    getline(cin, inputFile);
    cout << "Введите путь для сохранения результата: ";
    getline(cin, outputFile);
    
    if (cipher.decryptFile(inputFile, outputFile)) {
        cout << "Файл расшифрован: " << outputFile << endl;
    } else {
        cout << "Ошибка при расшифровании файла" << endl;
    }
}
