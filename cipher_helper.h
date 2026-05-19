#ifndef CIPHER_HELPER_H
#define CIPHER_HELPER_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Очистка экрана
inline void clearScreen() {
    system("clear");
    // system("cls"); // для Windows
}

// Пауза
inline void waitForKey() {
    cout << "\nНажмите Enter для продолжения...";
    cin.ignore();
    cin.get();
}

// Чтение файла
inline string readFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) return "";
    return string((istreambuf_iterator<char>(file)), {});
}

// Запись файла
inline bool writeFile(const string& filename, const string& data) {
    ofstream file(filename, ios::binary);
    if (!file) return false;
    file.write(data.c_str(), data.size());
    return true;
}

// Вывод HEX
inline void printHex(const string& data) {
    for (unsigned char c : data) {
        cout << hex << setw(2) << setfill('0') << (int)c;
    }
    cout << dec << endl;
}

#endif