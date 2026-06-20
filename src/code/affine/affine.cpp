#include <cstdint>
#include <cstddef>
#include <iostream>
#include "affine.h"

using namespace std;

uint8_t ModInverse(uint8_t a) {
    a = a % 256;
    for (int x = 1; x < 256; x++) {
        if ((a * x) % 256 == 1) {
            return static_cast<uint8_t>(x);
        }
    }
    return 1;
}

extern "C" void ProcessDataVerbose(uint8_t* data, size_t len, int key_a, int key_b, bool encrypt) {
    if (key_a % 2 == 0) key_a += 1;
    
    cout << "\n=== АФФИННЫЙ ШИФР - " << (encrypt ? "ШИФРОВАНИЕ" : "ДЕШИФРОВАНИЕ") << " ===\n";
    cout << "a = " << key_a << ", b = " << key_b << ", m = 256\n\n";
    
    if (encrypt) {
        cout << "Формула: c = (a*p + b) mod 256\n";
        cout << "№\tp\tc = (" << key_a << "*p+" << key_b << ") mod 256\tc\n";
        cout << "------------------------------------------------\n";
        for (size_t i = 0; i < len; i++) {
            uint8_t p = data[i];
            int calc = (key_a * p + key_b) % 256;
            uint8_t c = static_cast<uint8_t>(calc);
            cout << i << "\t" << (int)p << "\t" << key_a << "*" << (int)p << "+" << key_b << " = " << calc << "\t\t" << (int)c << endl;
            data[i] = c;
        }
    } else {
        uint8_t a_inv = ModInverse(static_cast<uint8_t>(key_a));
        cout << "Формула: p = a^-1*(c-b) mod 256\n";
        cout << "a^-1 = " << (int)a_inv << "\n";
        cout << "№\tc\tp = " << (int)a_inv << "*(c-" << key_b << ") mod 256\tp\n";
        cout << "------------------------------------------------\n";
        for (size_t i = 0; i < len; i++) {
            uint8_t c = data[i];
            int temp = (c - key_b) % 256;
            if (temp < 0) temp += 256;
            uint8_t p = static_cast<uint8_t>((a_inv * temp) % 256);
            cout << i << "\t" << (int)c << "\t" << (int)a_inv << "*(" << (int)c << "-" << key_b << ") mod 256 = " << (int)p << endl;
            data[i] = p;
        }
    }
    cout << "================================================\n";
}

extern "C" void ProcessData(uint8_t* data, size_t len, int key_a, int key_b, bool encrypt) {
    if (key_a % 2 == 0) key_a += 1;
    
    if (encrypt) {
        for (size_t i = 0; i < len; i++) {
            data[i] = static_cast<uint8_t>((key_a * data[i] + key_b) % 256);
        }
    } else {
        uint8_t a_inv = ModInverse(static_cast<uint8_t>(key_a));
        for (size_t i = 0; i < len; i++) {
            int temp = (data[i] - key_b) % 256;
            if (temp < 0) temp += 256;
            data[i] = static_cast<uint8_t>((a_inv * temp) % 256);
        }
    }
}
