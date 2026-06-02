#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include <vector>
#include "xor.h"
#include "railfence.h"
using namespace std;

bool login() {
    string password;
    const string Password = "zahar";  //пароль
    
    cout << endl;
    cout << "Добро пожаловать" << endl;
    cout << "Введите пароль: ";
    cin >> password;
    
    if (password == Password) {
        cout << "\nВы вошли" << endl;
        return true;
    } else {
        cout << "\nОшибка: неверный пароль" << endl;
        return false;
    }
}

enum MainMenu {
    EXIT_MAIN = 0,
    CHOOSE_XOR = 1,
    CHOOSE_RAIL = 2
};

enum XORMenu {
    XOR_BACK = 0,
    XOR_ENCRYPT_TEXT = 1,
    XOR_DECRYPT_TEXT = 2,
    XOR_ENCRYPT_FILE = 3,
    XOR_DECRYPT_FILE = 4
};

enum RailMenu {
    RAIL_BACK = 0,
    RAIL_ENCRYPT_TEXT = 1,
    RAIL_DECRYPT_TEXT = 2,
    RAIL_ENCRYPT_FILE = 3,
    RAIL_DECRYPT_FILE = 4
};

//hex

vector<unsigned char> hexToBytes(const string& hex) {
    vector<unsigned char> bytes;
    stringstream ss(hex);
    string byte;
    
    while (ss >> byte) {
        if (byte.length() == 2) {
            unsigned char c = (unsigned char)stoi(byte, nullptr, 16);
            bytes.push_back(c);
        }
    }
    return bytes;
}

string bytesToString(const vector<unsigned char>& bytes) {
    return string(bytes.begin(), bytes.end());
}

// xor

void showXORMenu() {
    cout << "\n--- XOR (Гаммирование) ---" << endl;
    cout << "  " << XOR_ENCRYPT_TEXT << ". Шифровать текст" << endl;
    cout << "  " << XOR_DECRYPT_TEXT << ". Расшифровать текст" << endl;
    cout << "  " << XOR_ENCRYPT_FILE << ". Шифровать файл" << endl;
    cout << "  " << XOR_DECRYPT_FILE << ". Расшифровать файл" << endl;
    cout << "  " << XOR_BACK << ". Назад" << endl;
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
        cout << "Ошибка: неверный ключ" << endl;
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

void xorDecryptText(XORCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string text, key;
    
    cout << "\nВведите зашифрованный текст можно HEX: ";
    getline(cin, text);
    
    // Проверяем hex ли это 
    bool looksLikeHex = true;
    for (char c : text) {
        if (!(c == ' ' || (c >= '0' && c <= '9') || 
              (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))) {
            looksLikeHex = false;
            break;
        }
    }
    
    //Если hex обрабатываем
    if (looksLikeHex && text.find(' ') != string::npos) {
        vector<unsigned char> bytes = hexToBytes(text);
        text = bytesToString(bytes);
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
    
    cout << "\nВведите файл для шифрования: ";
    getline(cin, inputFile);
    
    cout << "Введите в какой файл сохранить результат: ";
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
    
    cout << "\nВведите зашифрованный файл: ";
    getline(cin, inputFile);
    
    cout << "Введите в какой файл сохранить результат: ";
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

// railf

void showRailMenu() {
    cout << "\n--- Rail Fence (Зигзаг) ---" << endl;
    cout << "  " << RAIL_ENCRYPT_TEXT << ". Шифровать текст" << endl;
    cout << "  " << RAIL_DECRYPT_TEXT << ". Расшифровать текст" << endl;
    cout << "  " << RAIL_ENCRYPT_FILE << ". Шифровать файл (только текст)" << endl;
    cout << "  " << RAIL_DECRYPT_FILE << ". Расшифровать файл (только текст)" << endl;
    cout << "  " << RAIL_BACK << ". Назад" << endl;
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
    cout << result << endl;
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
    
    cout << "\nВведите файл для шифрования: ";
    getline(cin, inputFile);
    
    cout << "Введите в какой файл сохранить результат: ";
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
    
    cout << "\nВведите зашифрованный файл: ";
    getline(cin, inputFile);
    
    cout << "Введите в какой файл сохранить результат: ";
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

//Основное меню

void showMainMenu() {
    cout << endl;
    cout << "Программа для шиифрования файлов" << endl;
    cout << "Выберите шифр: " << endl;
    cout << "  " << CHOOSE_XOR << ". XOR (Гаммирование)" << endl;
    cout << "  " << CHOOSE_RAIL << ". Rail Fence (Зигзаг)" << endl;
    cout << "  " << EXIT_MAIN << ". Выход" << endl;
}

int main() {
    //пароль
    if (!login()) {
        cout << "Доступ запрещён. Программа завершает работу" << endl;
        return 1;
    }
    
    XORCipher xorCipher;
    RailFenceCipher railCipher;
    
    int cipherChoice, actionChoice;
    
    do {
        showMainMenu();
        cin >> cipherChoice;
        
        if (cipherChoice == EXIT_MAIN) {
            break;
        }
        
        if (cipherChoice == CHOOSE_XOR) {
            do {
                showXORMenu();
                cin >> actionChoice;
                
                switch (actionChoice) {
                    case XOR_ENCRYPT_TEXT:
                        xorEncryptText(xorCipher);
                        break;
                    case XOR_DECRYPT_TEXT:
                        xorDecryptText(xorCipher);
                        break;
                    case XOR_ENCRYPT_FILE:
                        xorEncryptFile(xorCipher);
                        break;
                    case XOR_DECRYPT_FILE:
                        xorDecryptFile(xorCipher);
                        break;
                    case XOR_BACK:
                        break;
                    default:
                        cout << "Неверный выбор" << endl;
                }
            } while (actionChoice != XOR_BACK);
            
        } else if (cipherChoice == CHOOSE_RAIL) {
            do {
                showRailMenu();
                cin >> actionChoice;
                
                switch (actionChoice) {
                    case RAIL_ENCRYPT_TEXT:
                        railEncryptText(railCipher);
                        break;
                    case RAIL_DECRYPT_TEXT:
                        railDecryptText(railCipher);
                        break;
                    case RAIL_ENCRYPT_FILE:
                        railEncryptFile(railCipher);
                        break;
                    case RAIL_DECRYPT_FILE:
                        railDecryptFile(railCipher);
                        break;
                    case RAIL_BACK:
                        break;
                    default:
                        cout << "Неверный выбор" << endl;
                }
            } while (actionChoice != RAIL_BACK);
            
        } else {
            cout << "Неверный выбор шифра" << endl;
        }
        
    } while (cipherChoice != EXIT_MAIN);
    
    cout << "\nПока" << endl;
    return 0;
}
