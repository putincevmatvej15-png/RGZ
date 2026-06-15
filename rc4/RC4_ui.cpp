#include "rc4.h"
#include <iostream>
#include <string>
#include <limits>
#include <vector>

using namespace std;

vector<unsigned char> hexToBytes(const string& hex);

void showRC4Menu() {
    cout << "\n--- RC4 ---" << endl;
    cout << "  1. Шифровать текст" << endl;
    cout << "  2. Расшифровать текст" << endl;
    cout << "  3. Шифровать файл" << endl;
    cout << "  4. Расшифровать файл" << endl;
    cout << "  0. Назад" << endl;
    cout << "Выберите действие: ";
}

void rc4EncryptText(RC4Cipher& cipher) {
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
    
    string result = cipher.encrypt(text, key);
    
    // Вывод в HEX-виде, чтобы спецсимволы не ломали вывод в консоль
    cout << "\nЗашифрованный текст (HEX формат): ";
    for (unsigned char c : result) {
        printf("%02X ", c);
    }
    cout << endl;
}

void rc4DecryptText(RC4Cipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string hexInput, key;
    
    cout << "\nВведите зашифрованный текст (HEX формат): ";
    getline(cin, hexInput);
    
    cout << "Введите ключ (тот же, что при шифровании): ";
    getline(cin, key);
    
    if (!cipher.isValidKey(key)) {
        cout << "Ошибка: ключ не может быть пустым!" << endl;
        return;
    }
    
    vector<unsigned char> cipherBytes = hexToBytes(hexInput);
    if (cipherBytes.empty()) {
        cout << "Ошибка: пустой или некорректный HEX-ввод!" << endl;
        return;
    }
    
    string cipherText(cipherBytes.begin(), cipherBytes.end());
    string result = cipher.decrypt(cipherText, key);
    
    cout << "\nРасшифрованный текст:" << endl;
    cout << result << endl;
}

void rc4EncryptFile(RC4Cipher& cipher) {
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

void rc4DecryptFile(RC4Cipher& cipher) {
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