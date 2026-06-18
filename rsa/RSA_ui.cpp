#include "rsa.h"
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cmath>

using namespace std;

// Функция преобразования HEX-строки в массив 16-битных чисел
vector<uint16_t> hexToUint16(const string& hex) {
    vector<uint16_t> nums;
    stringstream ss(hex);
    string word;
    while (ss >> word) {
        if (word.length() <= 4) {
            nums.push_back(static_cast<uint16_t>(stoul(word, nullptr, 16)));
        }
    }
    return nums;
}

// Проверка числа на простоту
bool isPrime(uint32_t n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (uint32_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Расширенный алгоритм Евклида для поиска НОД и коэффициентов
int64_t ExtendedGCD(int64_t a, int64_t b, int64_t& x, int64_t& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int64_t x1, y1;
    int64_t gcd = ExtendedGCD(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

// Поиск модульной инверсии (a^-1 mod m)
int64_t ModInverse(int64_t a, int64_t m) {
    int64_t x, y;
    int64_t gcd = ExtendedGCD(a, m, x, y);
    if (gcd != 1) {
        return -1;
    }
    return (x % m + m) % m;
}

// Поиск НОД
uint64_t GCD(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Генерация ключей RSA
bool generateRSAKeys(uint32_t p, uint32_t q, uint32_t& e, uint32_t& d, uint32_t& n) {
    if (!isPrime(p) || !isPrime(q)) {
        cout << "Ошибка: p и q должны быть простыми числами!" << endl;
        return false;
    }
    
    n = p * q;
    uint64_t phi = (uint64_t)(p - 1) * (q - 1);
    
    // Выбор e
    e = 65537;
    if (e >= phi) {
        e = 3;
    }
    
    while (GCD(e, phi) != 1) {
        e += 2;
    }
    
    // Вычисление d
    int64_t d_temp = ModInverse(e, phi);
    if (d_temp == -1) {
        cout << "Ошибка: не удалось вычислить ключ d!" << endl;
        return false;
    }
    d = static_cast<uint32_t>(d_temp);
    
    return true;
}

void showRSAMenu() {
    cout << "\n--- RSA шифр ---" << endl;
    cout << "  1. Шифровать текст" << endl;
    cout << "  2. Расшифровать текст" << endl;
    cout << "  3. Шифровать файл" << endl;
    cout << "  4. Расшифровать файл" << endl;
    cout << "  0. Назад" << endl;
    cout << "Выберите действие: ";
}

void rsaEncryptText() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string text;
    uint32_t p, q, e, d, n;
    
    cout << "\nВведите текст для шифрования: ";
    getline(cin, text);
    
    cout << "Введите простое число p (например, 61): ";
    cin >> p;
    cout << "Введите простое число q (например, 53): ";
    cin >> q;
    
    if (!generateRSAKeys(p, q, e, d, n)) {
        return;
    }
    
    cout << "Сгенерированные ключи:" << endl;
    cout << "  n = " << n << endl;
    cout << "  e = " << e << " (открытый ключ)" << endl;
    cout << "  d = " << d << " (закрытый ключ)" << endl;
    
    vector<uint8_t> data(text.begin(), text.end());
    vector<uint16_t> encrypted(data.size());
    
    RSA_Encrypt(data.data(), data.size(), encrypted.data(), e, n);
    
    cout << "\nЗашифрованный текст (HEX формат): ";
    for (uint16_t c : encrypted) {
        cout << hex << setw(4) << setfill('0') << uppercase << c << " ";
    }
    cout << dec << endl;
    cout << "\nСохраните значения p=" << p << " и q=" << q << " для расшифрования!" << endl;
}

void rsaDecryptText() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string hexInput;
    uint32_t p, q, e, d, n;
    
    cout << "\nВведите зашифрованный текст (HEX формат через пробел): ";
    getline(cin, hexInput);
    
    cout << "Введите простое число p (которое использовалось при шифровании): ";
    cin >> p;
    cout << "Введите простое число q: ";
    cin >> q;
    
    if (!generateRSAKeys(p, q, e, d, n)) {
        return;
    }
    
    vector<uint16_t> data = hexToUint16(hexInput);
    if (data.empty()) {
        cout << "\nОшибка: некорректный HEX-ввод или пустая строка!" << endl;
        return;
    }
    
    vector<uint8_t> decrypted(data.size());
    RSA_Decrypt(data.data(), data.size(), decrypted.data(), d, n);
    
    string result(decrypted.begin(), decrypted.end());
    cout << "\nРасшифрованный текст:" << endl;
    cout << result << endl;
}

void rsaEncryptFile() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string inputFile, outputFile;
    uint32_t p, q, e, d, n;
    
    cout << "\nВведите путь к файлу для шифрования: ";
    getline(cin, inputFile);
    cout << "Введите путь для сохранения результата: ";
    getline(cin, outputFile);
    
    cout << "Введите простое число p (например, 61): ";
    cin >> p;
    cout << "Введите простое число q (например, 53): ";
    cin >> q;
    
    if (!generateRSAKeys(p, q, e, d, n)) {
        return;
    }
    
    cout << "Сгенерированные ключи:" << endl;
    cout << "  n = " << n << endl;
    cout << "  e = " << e << " (открытый ключ)" << endl;
    cout << "  d = " << d << " (закрытый ключ)" << endl;
    
    ifstream in(inputFile, ios::binary);
    if (!in.is_open()) {
        cout << "Ошибка: не удалось открыть файл" << endl;
        return;
    }
    
    vector<uint8_t> data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();
    
    vector<uint16_t> encrypted(data.size());
    RSA_Encrypt(data.data(), data.size(), encrypted.data(), e, n);
    
    ofstream out(outputFile, ios::binary);
    out.write(reinterpret_cast<const char*>(encrypted.data()), encrypted.size() * sizeof(uint16_t));
    out.close();
    
    cout << "Файл зашифрован. Результат: " << outputFile << endl;
    cout << "Сохраните значения p=" << p << " и q=" << q << " для расшифрования!" << endl;
}

void rsaDecryptFile() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string inputFile, outputFile;
    uint32_t p, q, e, d, n;
    
    cout << "\nВведите путь к зашифрованному файлу: ";
    getline(cin, inputFile);
    cout << "Введите путь для сохранения результата: ";
    getline(cin, outputFile);
    
    cout << "Введите простое число p (которое использовалось при шифровании): ";
    cin >> p;
    cout << "Введите простое число q: ";
    cin >> q;
    
    if (!generateRSAKeys(p, q, e, d, n)) {
        return;
    }
    
    ifstream in(inputFile, ios::binary);
    if (!in.is_open()) {
        cout << "Ошибка: не удалось открыть файл" << endl;
        return;
    }
    
    vector<char> buffer((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();
    
    if (buffer.size() % sizeof(uint16_t) != 0) {
        cout << "Ошибка: некорректный размер зашифрованного файла" << endl;
        return;
    }
    
    size_t count = buffer.size() / sizeof(uint16_t);
    vector<uint16_t> encrypted(count);
    memcpy(encrypted.data(), buffer.data(), buffer.size());
    
    vector<uint8_t> decrypted(count);
    RSA_Decrypt(encrypted.data(), count, decrypted.data(), d, n);
    
    ofstream out(outputFile, ios::binary);
    out.write(reinterpret_cast<const char*>(decrypted.data()), decrypted.size());
    out.close();
    
    cout << "Файл расшифрован. Результат: " << outputFile << endl;
}