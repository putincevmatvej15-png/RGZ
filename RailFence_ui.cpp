#include "railfence.h"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

void showRailMenu() {
    cout << "\n--- Rail Fence (Зигзаг) ---" << endl;
    cout << "  1. Шифровать текст" << endl;
    cout << "  2. Расшифровать текст" << endl;
    cout << "  3. Шифровать файл (только текст)" << endl;
    cout << "  4. Расшифровать файл (только текст)" << endl;
    cout << "  0. Назад" << endl;
    cout << "Выберите действие: ";
}

void railEncryptText(RailFenceCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string text;
    int key;
    
    cout << "\nВведите текст для шифрования: ";
    getline(cin, text);
    
    cout << "Введите ключ (" << cipher.getKeyHint() << "): ";
    cin >> key;
    
    if (!cipher.isValidKey(key)) {
        cout << "Ошибка: ключ должен быть >= 2" << endl;
        return;
    }
    
    string result = cipher.encrypt(text, key);
    
    cout << "\nЗашифрованный текст" << endl;
    cout << "Текст: " << result << endl;
    cout << "HEX: ";
    for (unsigned char c : result) {
        printf("%02X ", c);
    }
    cout << endl;
}

void railDecryptText(RailFenceCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string text;
    int key;
    
    cout << "\nВведите зашифрованный текст: ";
    getline(cin, text);
    
    cout << "Введите ключ (" << cipher.getKeyHint() << "): ";
    cin >> key;
    
    if (!cipher.isValidKey(key)) {
        cout << "Ошибка: ключ должен быть >= 2" << endl;
        return;
    }
    
    string result = cipher.decrypt(text, key);
    
    cout << "\nРасшифрованный текст" << endl;
    cout << result << endl;
}

void railEncryptFile(RailFenceCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string inputFile, outputFile;
    int key;
    
    cout << "\nВведите путь к файлу для шифрования: ";
    getline(cin, inputFile);
    
    cout << "Введите путь для сохранения результата: ";
    getline(cin, outputFile);
    
    cout << "Введите ключ (" << cipher.getKeyHint() << "): ";
    cin >> key;
    
    if (!cipher.isValidKey(key)) {
        cout << "Ошибка: ключ должен быть >= 2" << endl;
        return;
    }
    
    cout << "\nШифрование файла..." << endl;
    if (cipher.encryptFile(inputFile, outputFile, key)) {
        cout << "Результат сохранён в: " << outputFile << endl;
    }
}

void railDecryptFile(RailFenceCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string inputFile, outputFile;
    int key;
    
    cout << "\nВведите путь к зашифрованному файлу: ";
    getline(cin, inputFile);
    
    cout << "Введите путь для сохранения результата: ";
    getline(cin, outputFile);
    
    cout << "Введите ключ (" << cipher.getKeyHint() << "): ";
    cin >> key;
    
    if (!cipher.isValidKey(key)) {
        cout << "Ошибка: ключ должен быть >= 2" << endl;
        return;
    }
    
    cout << "\nДешифрование файла..." << endl;
    if (cipher.decryptFile(inputFile, outputFile, key)) {
        cout << "Результат сохранён в: " << outputFile << endl;
    }
}
