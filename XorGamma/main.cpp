#include "xor.h"
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

void showMenu() {
    cout << "   XOR Шифр Гаммирование" << endl;
    cout << "  1. Шифровать текст результат в файл" << endl;
    cout << "  2. Расшифровать текст из файла" << endl;
    cout << "  3. Расшифровать текст по HEX" << endl;
    cout << "  4. Шифровать файл" << endl;
    cout << "  5. Расшифровать файл" << endl;
    cout << "  0. Выход" << endl;
    cout << "Выберите действие: ";
}

// Преобразование HEX строки в байты
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

//Преобразование байтов в строку
string bytesToString(const vector<unsigned char>& bytes) {
    return string(bytes.begin(), bytes.end());
}

void encryptTextToFile(XORCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string text, key, filename;
    
    cout << "\nВведите текст для шифрования ";
    getline(cin, text);
    
    cout << "Введите ключ целое число ";
    getline(cin, key);
    
    if (!cipher.isValidKey(key)) {
        cout << "Ошибка ключ должен быть целым числом" << endl;
        return;
    }
    
    string result = cipher.encrypt(text, key);
    
    cout << "\nВведите имя файла для сохранения (например secret.txt) ";
    getline(cin, filename);
    
    ofstream file(filename, ios::binary);
    if (file.is_open()) {
        file.write(result.c_str(), result.size());
        file.close();
        cout << "\nЗашифрованный текст сохранён в файл " << filename << endl;
        cout << "\nHEX представление (можно использовать для расшифровки)" << endl;
        for (unsigned char c : result) {
            printf("%02X ", c);
        }
        cout << endl;
    } else {
        cout << "Ошибка не удалось сохранить файл" << endl;
    }
}

void decryptTextFromFile(XORCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string filename, key;
    
    cout << "\nВведите имя файла с зашифрованным текстом ";
    getline(cin, filename);
    
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cout << "Ошибка не удалось открыть файл " << filename << endl;
        return;
    }
    
    string encrypted((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    
    cout << "Введите ключ тот же что использовался при шифровании ";
    getline(cin, key);
    
    if (!cipher.isValidKey(key)) {
        cout << "Ошибка ключ должен быть целым числом " << endl;
        return;
    }
    
    string decrypted = cipher.decrypt(encrypted, key);
    
    cout << "\nРасшифрованный текст" << endl;
    cout << decrypted << endl;
}

void decryptTextFromHex(XORCipher& cipher) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string hexString, key;
    
    cout << "\nВведите HEX строку (например F4 C0 16 47 E7) ";
    getline(cin, hexString);
    
    cout << "Введите ключ (тот же что использовался при шифровании) ";
    getline(cin, key);
    
    if (!cipher.isValidKey(key)) {
        cout << "Ошибка ключ должен быть целым числом" << endl;
        return;
    }
    
    vector<unsigned char> encryptedBytes = hexToBytes(hexString);
    string encrypted = bytesToString(encryptedBytes);
    
    string decrypted = cipher.decrypt(encrypted, key);
    
    cout << "\nРасшифрованный тест" << endl;
    cout << decrypted << endl;
}

void processFile(XORCipher& cipher, bool encryptMode) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string inputFile, outputFile, key;
    
    if (encryptMode) {
        cout << "\nВведите путь к файлу который нужно зашифровать ";
    } else {
        cout << "\nВведите путь к зашифрованному файлу ";
    }
    getline(cin, inputFile);
    
    cout << "Введите путь для сохранения результата ";
    getline(cin, outputFile);
    
    cout << "Введите ключ (целое число) ";
    getline(cin, key);
    
    if (!cipher.isValidKey(key)) {
        cout << "Ошибка ключ должен быть целым числом " << endl;
        return;
    }
    
    bool success;
    if (encryptMode) {
        cout << "\nШифрование файла..." << endl;
        success = cipher.encryptFile(inputFile, outputFile, key);
    } else {
        cout << "\nРасшифрование файла..." << endl;
        success = cipher.decryptFile(inputFile, outputFile, key);
    }
    
    if (success) {
        cout << "Готово. Результат сохранён в  " << outputFile << endl;
    }
}

int main() {
    XORCipher cipher;
    int choice;
    cout << "   XOR Шифровка" << endl;
    cout << "\n Как пользоваться " << endl;
    cout << "   1. Выберите пункт 1 введите текст и ключ" << endl;
    cout << "   2. Программа сохранит результат в файл" << endl;
    cout << "   3. Для расшифровки выберите пункт 2 (из файла) или 3 (по HEX)" << endl;
   
    do {
        showMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                encryptTextToFile(cipher);
                break;
            case 2:
                decryptTextFromFile(cipher);
                break;
            case 3:
                decryptTextFromHex(cipher);
                break;
            case 4:
                processFile(cipher, true);
                break;
            case 5:
                processFile(cipher, false);
                break;
            case 0:
                cout << "До свидания" << endl;
                break;
            default:
                cout << "Неверный выбор" << endl;
        }
    } while (choice != 0);
    
    return 0;
}
