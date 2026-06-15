#include "vernam.h"
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <sstream>   
#include <vector>
using namespace std;

void showVernamMenu() {
    cout << "\nВернам" << endl;
    cout << "  1. Шифровать текст" << endl;
    cout << "  2. Расшифровать текст" << endl;
    cout << "  3. Шифровать файл" << endl;
    cout << "  4. Расшифровать файл" << endl;
    cout << "  0. Назад" << endl;
    cout << "Выберите действие: ";
}

void vernamEncryptText(VernamCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string text, key;
    cout << "\nВведите текст для шифрования: ";
    getline(cin, text);
    cout << "Введите ключ (строка): ";
    getline(cin, key);
    
    if (!cipher.isValidKey(key)) {
        cout << "Ошибка: ключ не может быть пустым" << endl;
        return;
    }
    
    if (text.empty()) {
        cout << "Ошибка: текст не может быть пустым" << endl;
        return;
    }
    
    string result = cipher.encrypt(text, key);
    cout << "\nЗашифрованные данные" << endl;
    cout << "Текст: " << result << endl;
    cout << "HEX: ";
    cout << hex << setfill('0');
    for (unsigned char c : result) {
        cout << setw(2) << (int)c << " ";
    }
    cout << dec << endl;
}

void vernamDecryptText(VernamCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string input, key;
    cout << "\nВведите зашифрованный текст: ";
    getline(cin, input);
    
    cout << "Введите ключ (тот же, что при шифровании): ";
    getline(cin, key);
    
    if (!cipher.isValidKey(key)) {
        cout << "Ошибка: ключ не может быть пустым!" << endl;
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
    
    string result = cipher.decrypt(textToDecrypt, key);
    
    cout << "\n=== РАСШИФРОВАННЫЕ ДАННЫЕ ===" << endl;
    cout << "Текст: " << result << endl;
}

void vernamEncryptFile(VernamCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string inputFile, outputFile, key;
    cout << "\nВведите путь к файлу для шифрования: ";
    getline(cin, inputFile);
    cout << "Введите путь для сохранения результата: ";
    getline(cin, outputFile);
    cout << "Введите ключ (строка): ";
    getline(cin, key);
    
    if (cipher.encryptFile(inputFile, outputFile, key)) {
        cout << "Файл зашифрован: " << outputFile << endl;
    } else {
        cout << "Ошибка при шифровании файла" << endl;
    }
}

void vernamDecryptFile(VernamCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string inputFile, outputFile, key;
    cout << "\nВведите путь к зашифрованному файлу: ";
    getline(cin, inputFile);
    cout << "Введите путь для сохранения результата: ";
    getline(cin, outputFile);
    cout << "Введите ключ (тот же, что при шифровании): ";
    getline(cin, key);
    if (cipher.decryptFile(inputFile, outputFile, key)) {
        cout << "Файл расшифрован: " << outputFile << endl;
    } else {
        cout << "Ошибка при расшифровании файла" << endl;
    }
}
