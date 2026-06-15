#include "affine.h"
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Функция преобразования HEX-строки в массив байт
vector<unsigned char> hexToBytes(const string& hex);

void showAffineMenu() {
    cout << "\n--- Аффинный шифр ---" << endl;
    cout << "  1. Шифровать текст" << endl;
    cout << "  2. Расшифровать текст" << endl;
    cout << "  3. Шифровать файл" << endl;
    cout << "  4. Расшифровать файл" << endl;
    cout << "  0. Назад" << endl;
    cout << "Выберите действие: ";
}

void affineEncryptText() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string text;
    int key_a, key_b;
    
    cout << "\nВведите текст для шифрования: ";
    getline(cin, text);
    
    cout << "Введите ключ a (нечетное число, например 5): ";
    cin >> key_a;
    cout << "Введите ключ b (сдвиг, например 7): ";
    cin >> key_b;
    
    // Проверка ключа 'a' на нечетность (должен быть взаимно прост с 256)
    if (key_a % 2 == 0) {
        key_a = key_a * 2 + 1;
    }
    
    vector<uint8_t> data(text.begin(), text.end());
    ProcessData(data.data(), data.size(), key_a, key_b, true);
    
    // Выводим результат в HEX, чтобы избежать проблем с непечатными символами в консоли
    cout << "\nЗашифрованный текст (HEX формат): ";
    for (unsigned char c : data) {
        printf("%02X ", c);
    }
    cout << endl;
}

void affineDecryptText() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string hexInput;
    int key_a, key_b;
    
    cout << "\nВведите зашифрованный текст (HEX формат через пробел): ";
    getline(cin, hexInput);
    
    cout << "Введите ключ a (тот же, что при шифровании): ";
    cin >> key_a;
    cout << "Введите ключ b: ";
    cin >> key_b;
    
    if (key_a % 2 == 0) {
        key_a = key_a * 2 + 1;
    }
    
    // Переводим HEX-строку обратно в байты для дешифрования
    vector<uint8_t> data = hexToBytes(hexInput);
    
    if (data.empty()) {
        cout << "\nОшибка: некорректный HEX-ввод или пустая строка!" << endl;
        return;
    }

    ProcessData(data.data(), data.size(), key_a, key_b, false);
    
    string result(data.begin(), data.end());
    
    cout << "\nРасшифрованный текст:" << endl;
    cout << result << endl;
}

void affineEncryptFile() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string inputFile, outputFile;
    int key_a, key_b;
    
    cout << "\nВведите путь к файлу для шифрования: ";
    getline(cin, inputFile);
    
    cout << "Введите путь для сохранения результата: ";
    getline(cin, outputFile);
    
    cout << "Введите ключ a (нечетное число): ";
    cin >> key_a;
    cout << "Введите ключ b: ";
    cin >> key_b;
    
    ifstream in(inputFile, ios::binary);
    if (!in.is_open()) {
        cout << "Ошибка: не удалось открыть файл" << endl;
        return;
    }
    
    // Чтение всего файла в вектор байт
    vector<uint8_t> data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();
    
    if (key_a % 2 == 0) key_a = key_a * 2 + 1;
    ProcessData(data.data(), data.size(), key_a, key_b, true);
    
    ofstream out(outputFile, ios::binary);
    out.write(reinterpret_cast<const char*>(data.data()), data.size());
    out.close();
    
    cout << "Файл зашифрован. Результат: " << outputFile << endl;
}

void affineDecryptFile() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string inputFile, outputFile;
    int key_a, key_b;
    
    cout << "\nВведите путь к зашифрованному файлу: ";
    getline(cin, inputFile);
    
    cout << "Введите путь для сохранения результата: ";
    getline(cin, outputFile);
    
    cout << "Введите ключ a (тот же, что при шифровании): ";
    cin >> key_a;
    cout << "Введите ключ b: ";
    cin >> key_b;
    
    ifstream in(inputFile, ios::binary);
    if (!in.is_open()) {
        cout << "Ошибка: не удалось открыть файл" << endl;
        return;
    }
    
    vector<uint8_t> data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();
    
    if (key_a % 2 == 0) key_a = key_a * 2 + 1;
    ProcessData(data.data(), data.size(), key_a, key_b, false);
    
    ofstream out(outputFile, ios::binary);
    out.write(reinterpret_cast<const char*>(data.data()), data.size());
    out.close();
    
    cout << "Файл расшифрован. Результат: " << outputFile << endl;
}