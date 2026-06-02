#include "helper_for_Vernam.h"
#include "cipher_helper.h"
#include <random>

using namespace std;

static string currentKey;

string vernam_getName() {
    return "Вернам";
}

string vernam_getDescription() {
    return "Абсолютно стойкий шифр на основе XOR (одноразовый блокнот)";
}

string vernam_generateKey(int length) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 255);
    
    string key;
    for (int i = 0; i < length; i++) {
        key += static_cast<char>(dis(gen));
    }
    return key;
}

void vernam_setKey(const string& key) {
    currentKey = key;
}

string vernam_getKey() {
    return currentKey;
}

string vernam_encrypt(const string& data) {
    if (currentKey.length() < data.length()) {
        return "";
    }
    string result;
    for (size_t i = 0; i < data.length(); i++) {
        result += data[i] ^ currentKey[i];
    }
    return result;
}

string vernam_decrypt(const string& data) {
    return vernam_encrypt(data);
}

bool vernam_isValidKey(const string& key, int dataLen) {
    if (key.empty()) return false;
    if (dataLen > 0 && key.length() < dataLen) return false;
    return true;
}

void vernam_menu() {
    string key;
    int choice;
    
    while (true) {
        clearScreen();
        cout << "========================================\n";
        cout << "        ШИФР ВЕРНАМА\n";
        cout << "========================================\n";
        cout << "1. Шифрование текста\n";
        cout << "2. Дешифрование текста\n";
        cout << "3. Шифрование файла\n";
        cout << "4. Дешифрование файла\n";
        cout << "5. Сгенерировать ключ\n";
        cout << "0. Назад\n";
        cout << "========================================\n";
        cout << "Выбор: ";
        cin >> choice;
        cin.ignore();
        
        if (choice == 0) break;
        
        if (choice == 5) {
            int len;
            cout << "Введите длину ключа: ";
            cin >> len;
            cin.ignore();
            key = vernam_generateKey(len);
            vernam_setKey(key);
            cout << "\nСгенерированный ключ (HEX): ";
            printHex(key);
            waitForKey();
            continue;
        }
        
        if (choice >= 1 && choice <= 4) {
            cout << "Введите ключ: ";
            string keyInput;
            getline(cin, keyInput);
            key = keyInput;
            vernam_setKey(key);
        }
        
        if (choice == 1) {
            cout << "Введите текст: ";
            string text;
            getline(cin, text);
            if (key.length() < text.length()) {
                cout << "Ошибка: ключ слишком короткий\n";
                waitForKey();
                continue;
            }
            cout << "\nЗашифрованный текст (HEX): ";
            printHex(vernam_encrypt(text));
            waitForKey();
        }
        else if (choice == 2) {
            cout << "Введите HEX строку: ";
            string hexStr;
            getline(cin, hexStr);
            string cipher;
            for (size_t i = 0; i < hexStr.length(); i += 2) {
                string byteStr = hexStr.substr(i, 2);
                char byte = (char)strtol(byteStr.c_str(), nullptr, 16);
                cipher += byte;
            }
            cout << "\nРасшифрованный текст: " << vernam_decrypt(cipher) << endl;
            waitForKey();
        }
        else if (choice == 3) {
            string inputFile, outputFile;
            cout << "Входной файл: ";
            getline(cin, inputFile);
            cout << "Выходной файл: ";
            getline(cin, outputFile);
            string data = readFile(inputFile);
            if (data.empty()) {
                cout << "Ошибка чтения файла\n";
                waitForKey();
                continue;
            }
            if (key.length() < data.length()) {
                cout << "Ошибка: ключ слишком короткий\n";
                waitForKey();
                continue;
            }
            if (writeFile(outputFile, vernam_encrypt(data))) {
                cout << "Файл зашифрован\n";
            }
            waitForKey();
        }
        else if (choice == 4) {
            string inputFile, outputFile;
            cout << "Входной файл: ";
            getline(cin, inputFile);
            cout << "Выходной файл: ";
            getline(cin, outputFile);
            string data = readFile(inputFile);
            if (data.empty()) {
                cout << "Ошибка чтения файла\n";
                waitForKey();
                continue;
            }
            if (writeFile(outputFile, vernam_decrypt(data))) {
                cout << "Файл расшифрован\n";
            }
            waitForKey();
        }
    }
}