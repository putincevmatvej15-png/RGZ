#include "xor.h"
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <sstream>
using namespace std;

extern vector<unsigned char> hexToBytes(const string& hex);
extern string bytesToString(const vector<unsigned char>& bytes);

void showXORMenu() {
    cout << "\n--- XOR (Гаммирование) ---" << endl;
    cout << "  1. Шифровать текст" << endl;
    cout << "  2. Расшифровать текст" << endl;
    cout << "  3. Шифровать файл" << endl;
    cout << "  4. Расшифровать файл" << endl;
    cout << "  0. Назад" << endl;
    cout << "Выберите действие: ";
}

void xorEncryptText(XORCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string text, key;
    
    cout << "\nВведите текст для шифрования: ";
    getline(cin, text);
    
    cout << "Введите ключ (" << cipher.getKeyHint() << "): ";
    getline(cin, key);
    
    if (!cipher.isValidKey(key)) {
        cout << "Ошибка неверный ключ" << endl;
        return;
    }
    
    string result = cipher.encrypt(text, key);
    
    cout << "\nЗашифрованнй текст" << endl;
    cout << "Текст: " << result << endl;
    cout << "HEX: ";
    for (unsigned char c : result) {
        printf("%02X ", c);
    }
    cout << endl;
}

void xorDecryptText(XORCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string text, key;
    
    cout << "\nВведите зашифрованный текст (можно HEX): ";
    getline(cin, text);
    
    bool looksLikeHex = true;
    for (char c : text) {
        if (!(c == ' ' || (c >= '0' && c <= '9') || 
              (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))) {
            looksLikeHex = false;
            break;
        }
    }
    
    if (looksLikeHex && text.find(' ') != string::npos) {
        vector<unsigned char> bytes = hexToBytes(text);
        text = bytesToString(bytes);
        cout << "(Распознано как HEX строка)" << endl;
    }
    
    cout << "Введите ключ (" << cipher.getKeyHint() << "): ";
    getline(cin, key);
    
    if (!cipher.isValidKey(key)) {
        cout << "Ошибка: неверный ключ" << endl;
        return;
    }
    
    string result = cipher.decrypt(text, key);
    
    cout << "\nРасшифрованный текст" << endl;
    cout << result << endl;
}

void xorEncryptFile(XORCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string inputFile, outputFile, key;
    
    cout << "\nВведите путь к файлу для шифрования: ";
    getline(cin, inputFile);
    
    cout << "Введите путь для сохранения результата: ";
    getline(cin, outputFile);
    
    cout << "Введите ключ (" << cipher.getKeyHint() << "): ";
    getline(cin, key);
    
    if (!cipher.isValidKey(key)) {
        cout << "Ошибка: неверный ключ" << endl;
        return;
    }
    
    cout << "\nШифрование файла..." << endl;
    if (cipher.encryptFile(inputFile, outputFile, key)) {
        cout << "Результат сохранён в: " << outputFile << endl;
    }
}

void xorDecryptFile(XORCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string inputFile, outputFile, key;
    
    cout << "\nВведите путь к зашифрованному файлу: ";
    getline(cin, inputFile);
    
    cout << "Введите путь для сохранения результата: ";
    getline(cin, outputFile);
    
    cout << "Введите ключ (" << cipher.getKeyHint() << "): ";
    getline(cin, key);
    
    if (!cipher.isValidKey(key)) {
        cout << "Ошибка: неверный ключ" << endl;
        return;
    }
    
    cout << "\nДешифрование файла..." << endl;
    if (cipher.decryptFile(inputFile, outputFile, key)) {
        cout << "Результат сохранён в: " << outputFile << endl;
    }
}
