#include "affine.h"
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <fstream>

using namespace std;

extern vector<unsigned char> hexToBytes(const string& hex);

void showAffineMenu() {
    cout << "\n--- Аффинный шифр ---\n";
    cout << "  1. Шифровать текст\n";
    cout << "  2. Расшифровать текст\n";
    cout << "  3. Шифровать файл\n";
    cout << "  4. Расшифровать файл\n";
    cout << "  0. Назад\n";
    cout << "Выберите действие: ";
}

void affineEncryptText() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string text;
    int key_a, key_b;
    
    cout << "\nВведите текст: ";
    getline(cin, text);
    cout << "Введите ключ a (нечетное): ";
    cin >> key_a;
    cout << "Введите ключ b: ";
    cin >> key_b;
    
    if (key_a % 2 == 0) key_a += 1;
    
    vector<uint8_t> data(text.begin(), text.end());
    ProcessDataVerbose(data.data(), data.size(), key_a, key_b, true);
    
    cout << "\nРезультат (HEX): ";
    for (unsigned char c : data) printf("%02X ", c);
    cout << endl;
}

void affineDecryptText() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string hexInput;
    int key_a, key_b;
    
    cout << "\nВведите HEX через пробел: ";
    getline(cin, hexInput);
    cout << "Введите ключ a: ";
    cin >> key_a;
    cout << "Введите ключ b: ";
    cin >> key_b;
    
    if (key_a % 2 == 0) key_a += 1;
    
    vector<uint8_t> data = hexToBytes(hexInput);
    if (data.empty()) {
        cout << "Ошибка: неверный HEX\n";
        return;
    }
    
    ProcessDataVerbose(data.data(), data.size(), key_a, key_b, false);
    cout << "\nРезультат: " << string(data.begin(), data.end()) << endl;
}

void affineEncryptFile() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string inputFile, outputFile;
    int key_a, key_b;
    bool verbose;
    
    cout << "\nВведите файл: ";
    getline(cin, inputFile);
    cout << "Введите выходной файл: ";
    getline(cin, outputFile);
    cout << "Введите ключ a: ";
    cin >> key_a;
    cout << "Введите ключ b: ";
    cin >> key_b;
    cout << "Выводить ход решения? (1-да, 0-нет): ";
    cin >> verbose;
    
    if (key_a % 2 == 0) key_a += 1;
    
    ifstream in(inputFile, ios::binary);
    if (!in.is_open()) {
        cout << "Ошибка: не удалось открыть файл\n";
        return;
    }
    
    vector<uint8_t> data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();
    
    if (verbose) {
        ProcessDataVerbose(data.data(), data.size(), key_a, key_b, true);
    } else {
        ProcessData(data.data(), data.size(), key_a, key_b, true);
    }
    
    ofstream out(outputFile, ios::binary);
    out.write(reinterpret_cast<const char*>(data.data()), data.size());
    out.close();
    
    cout << "Файл зашифрован: " << outputFile << endl;
}

void affineDecryptFile() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string inputFile, outputFile;
    int key_a, key_b;
    bool verbose;
    
    cout << "\nВведите файл: ";
    getline(cin, inputFile);
    cout << "Введите выходной файл: ";
    getline(cin, outputFile);
    cout << "Введите ключ a: ";
    cin >> key_a;
    cout << "Введите ключ b: ";
    cin >> key_b;
    cout << "Выводить ход решения? (1-да, 0-нет): ";
    cin >> verbose;
    
    if (key_a % 2 == 0) key_a += 1;
    
    ifstream in(inputFile, ios::binary);
    if (!in.is_open()) {
        cout << "Ошибка: не удалось открыть файл\n";
        return;
    }
    
    vector<uint8_t> data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();
    
    if (verbose) {
        ProcessDataVerbose(data.data(), data.size(), key_a, key_b, false);
    } else {
        ProcessData(data.data(), data.size(), key_a, key_b, false);
    }
    
    ofstream out(outputFile, ios::binary);
    out.write(reinterpret_cast<const char*>(data.data()), data.size());
    out.close();
    
    cout << "Файл расшифрован: " << outputFile << endl;
}

void affineMenu() {
    int choice;
    do {
        showAffineMenu();
        cin >> choice;
        switch (choice) {
            case 1: affineEncryptText(); break;
            case 2: affineDecryptText(); break;
            case 3: affineEncryptFile(); break;
            case 4: affineDecryptFile(); break;
            case 0: cout << "Назад\n"; break;
            default: cout << "Неверный выбор\n";
        }
    } while (choice != 0);
}