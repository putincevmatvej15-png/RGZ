#include "helper_for_Tritemius.h"
#include "cipher_helper.h"
#include <random>
#include <cctype>

using namespace std;

static int currentShift = 3;

string trithemius_getName() {
    return "Тритемиус";
}

string trithemius_getDescription() {
    return "Прогрессивный шифр сдвига (смещение увеличивается с каждой позицией)";
}

int trithemius_generateKey() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 25);
    return dis(gen);
}

void trithemius_setKey(int shift) {
    currentShift = shift;
}

int trithemius_getKey() {
    return currentShift;
}

string trithemius_process(const string& text, bool encryptMode) {
    string result;
    for (size_t i = 0; i < text.length(); i++) {
        char c = text[i];
        
        if (isalpha(c) && isascii(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int offset = (c - base);
            int shiftAmount = (currentShift + i);
            
            int newOffset;
            if (encryptMode) {
                newOffset = (offset + shiftAmount) % 26;
            } else {
                newOffset = (offset - shiftAmount + 2600) % 26;
            }
            result += base + newOffset;
        } else {
            result += c;
        }
    }
    return result;
}

string trithemius_encrypt(const string& data) {
    return trithemius_process(data, true);
}

string trithemius_decrypt(const string& data) {
    return trithemius_process(data, false);
}

bool trithemius_isValidKey(int shift) {
    return (shift >= 1 && shift <= 25);
}

void trithemius_menu() {
    int shift;
    int choice;
    
    while (true) {
        clearScreen();
        cout << "========================================\n";
        cout << "        " << trithemius_getName() << "\n";
        cout << "  " << trithemius_getDescription() << "\n";
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
            shift = trithemius_generateKey();
            trithemius_setKey(shift);
            cout << "\nСгенерированный ключ (сдвиг): " << shift << endl;
            waitForKey();
            continue;
        }
        
        if (choice >= 1 && choice <= 4) {
            cout << "Введите ключ (число от 1 до 25): ";
            cin >> shift;
            cin.ignore();
            
            if (!trithemius_isValidKey(shift)) {
                cout << "Ошибка: ключ должен быть от 1 до 25\n";
                waitForKey();
                continue;
            }
            trithemius_setKey(shift);
        }
        
        if (choice == 1) {
            cout << "Введите текст (латиница): ";
            string text;
            getline(cin, text);
            
            string encrypted = trithemius_encrypt(text);
            cout << "\nЗашифрованный текст: " << encrypted << endl;
            waitForKey();
        }
        else if (choice == 2) {
            cout << "Введите текст: ";
            string text;
            getline(cin, text);
            
            string decrypted = trithemius_decrypt(text);
            cout << "\nРасшифрованный текст: " << decrypted << endl;
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
            
            string encrypted = trithemius_encrypt(data);
            if (writeFile(outputFile, encrypted)) {
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
            
            string decrypted = trithemius_decrypt(data);
            if (writeFile(outputFile, decrypted)) {
                cout << "Файл расшифрован\n";
            }
            waitForKey();
        }
    }
}