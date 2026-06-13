#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <cstdint>
using namespace std;

//заголовки шифров
#include "xor.h"
#include "railfence.h"
#include "affine.h"
#include "tritemius.h"
#include "rc4.h"
#include "vernam.h"

//функциии шифрования/дешифр

void showXORMenu();
void xorEncryptText(XORCipher&);
void xorDecryptText(XORCipher&);
void xorEncryptFile(XORCipher&);
void xorDecryptFile(XORCipher&);

void showRailMenu();
void railEncryptText(RailFenceCipher&);
void railDecryptText(RailFenceCipher&);
void railEncryptFile(RailFenceCipher&);
void railDecryptFile(RailFenceCipher&);

void showAffineMenu();
void affineEncryptText();
void affineDecryptText();
void affineEncryptFile();
void affineDecryptFile();

void showTritemiusMenu();
void tritemiusEncryptText(TritemiusCipher&);
void tritemiusDecryptText(TritemiusCipher&);
void tritemiusEncryptFile(TritemiusCipher&);
void tritemiusDecryptFile(TritemiusCipher&);

void showRC4Menu();
void rc4EncryptText(RC4Cipher&);
void rc4DecryptText(RC4Cipher&);
void rc4EncryptFile(RC4Cipher&);
void rc4DecryptFile(RC4Cipher&);

void showVernamMenu();
void vernamEncryptText(VernamCipher&);
void vernamDecryptText(VernamCipher&);
void vernamEncryptFile(VernamCipher&);
void vernamDecryptFile(VernamCipher&);

//Hex

vector<unsigned char> hexToBytes(const string& hex) {
    vector<unsigned char> bytes;
    stringstream ss(hex);
    string byte;
    while (ss >> byte) {
        if (byte.length() == 2) {
            bytes.push_back(static_cast<unsigned char>(stoi(byte, nullptr, 16)));
        }
    }
    return bytes;
}

string bytesToString(const vector<unsigned char>& bytes) {
    return string(bytes.begin(), bytes.end());
}

//Логин

bool login() {
    string password;
    const string CORRECT_PASSWORD = "rgr";
    
    cout << "========================================" << endl;
    cout << "Добро пожаловать в программу!" << endl;
    cout << "========================================" << endl;
    cout << "Введите пароль: ";
    cin >> password;
    
    if (password == CORRECT_PASSWORD) {
        cout << "\nВы вошли!" << endl;
        return true;
    }
    cout << "\nОшибка: неверный пароль" << endl;
    return false;
}

//Enum classs

enum class MainMenu : int {
    EXIT = 0, XOR = 1, RAIL_FENCE = 2, AFFINE = 3,
    TRITEMIUS = 4, RC4 = 5, VERNAM = 6
};
enum class CipherAction : int {
    EXIT = 0, ENCRYPT_TEXT = 1, DECRYPT_TEXT = 2,
    ENCRYPT_FILE = 3, DECRYPT_FILE = 4
};

//Основное меню

void showMainMenu() {
    cout << "\n========================================" << endl;
    cout << "Программа для шифр/дешифр" << endl;
    cout << "========================================" << endl;
    cout << "  Выберите шифр:" << endl;
    cout << "  " << static_cast<int>(MainMenu::XOR) << ". XOR (Гаммирование)" << endl;
    cout << "  " << static_cast<int>(MainMenu::RAIL_FENCE) << ". Rail Fence (Зигзаг)" << endl;
    cout << "  " << static_cast<int>(MainMenu::AFFINE) << ". Аффинный шифр" << endl;
    cout << "  " << static_cast<int>(MainMenu::TRITEMIUS) << ". Шифр Тритемиуса" << endl;
    cout << "  " << static_cast<int>(MainMenu::RC4) << ". RC4" << endl;
    cout << "  " << static_cast<int>(MainMenu::VERNAM) << ". Вернам" << endl;
    cout << "  " << static_cast<int>(MainMenu::EXIT) << ". Выход" << endl;
}

int main() {
    if (!login()) {
        return 1;
    }
    
    XORCipher xorCipher;
    RailFenceCipher railCipher;
    TritemiusCipher tritemiusCipher;
    RC4Cipher rc4Cipher;
    VernamCipher vernamCipher;
    
    int cipherChoiceInt, actionChoiceInt;
    
    do {
        showMainMenu();
        cin >> cipherChoiceInt;
        MainMenu cipherChoice = static_cast<MainMenu>(cipherChoiceInt);
        
        if (cipherChoice == MainMenu::EXIT) {
            break;
        }
        
        if (cipherChoice == MainMenu::XOR) {
            do {
                showXORMenu();
                cin >> actionChoiceInt;
                CipherAction action = static_cast<CipherAction>(actionChoiceInt);
                switch (action) {
                    case CipherAction::ENCRYPT_TEXT: xorEncryptText(xorCipher); break;
                    case CipherAction::DECRYPT_TEXT: xorDecryptText(xorCipher); break;
                    case CipherAction::ENCRYPT_FILE: xorEncryptFile(xorCipher); break;
                    case CipherAction::DECRYPT_FILE: xorDecryptFile(xorCipher); break;
                    default: break;
                }
            } while (actionChoiceInt != static_cast<int>(CipherAction::EXIT));
        }
        else if (cipherChoice == MainMenu::RAIL_FENCE) {
            do {
                showRailMenu();
                cin >> actionChoiceInt;
                CipherAction action = static_cast<CipherAction>(actionChoiceInt);
                switch (action) {
                    case CipherAction::ENCRYPT_TEXT: railEncryptText(railCipher); break;
                    case CipherAction::DECRYPT_TEXT: railDecryptText(railCipher); break;
                    case CipherAction::ENCRYPT_FILE: railEncryptFile(railCipher); break;
                    case CipherAction::DECRYPT_FILE: railDecryptFile(railCipher); break;
                    default: break;
                }
            } while (actionChoiceInt != static_cast<int>(CipherAction::EXIT));
        }
        else if (cipherChoice == MainMenu::AFFINE) {
            do {
                showAffineMenu();
                cin >> actionChoiceInt;
                CipherAction action = static_cast<CipherAction>(actionChoiceInt);
                switch (action) {
                    case CipherAction::ENCRYPT_TEXT: affineEncryptText(); break;
                    case CipherAction::DECRYPT_TEXT: affineDecryptText(); break;
                    case CipherAction::ENCRYPT_FILE: affineEncryptFile(); break;
                    case CipherAction::DECRYPT_FILE: affineDecryptFile(); break;
                    default: break;
                }
            } while (actionChoiceInt != static_cast<int>(CipherAction::EXIT));
        }
        else if (cipherChoice == MainMenu::TRITEMIUS) {
            do {
                showTritemiusMenu();
                cin >> actionChoiceInt;
                CipherAction action = static_cast<CipherAction>(actionChoiceInt);
                switch (action) {
                    case CipherAction::ENCRYPT_TEXT: tritemiusEncryptText(tritemiusCipher); break;
                    case CipherAction::DECRYPT_TEXT: tritemiusDecryptText(tritemiusCipher); break;
                    case CipherAction::ENCRYPT_FILE: tritemiusEncryptFile(tritemiusCipher); break;
                    case CipherAction::DECRYPT_FILE: tritemiusDecryptFile(tritemiusCipher); break;
                    default: break;
                }
            } while (actionChoiceInt != static_cast<int>(CipherAction::EXIT));
        }
        else if (cipherChoice == MainMenu::RC4) {
            do {
                showRC4Menu();
                cin >> actionChoiceInt;
                CipherAction action = static_cast<CipherAction>(actionChoiceInt);
                switch (action) {
                    case CipherAction::ENCRYPT_TEXT: rc4EncryptText(rc4Cipher); break;
                    case CipherAction::DECRYPT_TEXT: rc4DecryptText(rc4Cipher); break;
                    case CipherAction::ENCRYPT_FILE: rc4EncryptFile(rc4Cipher); break;
                    case CipherAction::DECRYPT_FILE: rc4DecryptFile(rc4Cipher); break;
                    default: break;
                }
            } while (actionChoiceInt != static_cast<int>(CipherAction::EXIT));
        }
        else if (cipherChoice == MainMenu::VERNAM) {
            do {
                showVernamMenu();
                cin >> actionChoiceInt;
                CipherAction action = static_cast<CipherAction>(actionChoiceInt);
                switch (action) {
                    case CipherAction::ENCRYPT_TEXT: vernamEncryptText(vernamCipher); break;
                    case CipherAction::DECRYPT_TEXT: vernamDecryptText(vernamCipher); break;
                    case CipherAction::ENCRYPT_FILE: vernamEncryptFile(vernamCipher); break;
                    case CipherAction::DECRYPT_FILE: vernamDecryptFile(vernamCipher); break;
                    default: break;
                }
            } while (actionChoiceInt != static_cast<int>(CipherAction::EXIT));
        }
        else {
            cout << "Неверный выбор" << endl;
        }
        
    } while (true);
    
    cout << "\nДо встречи!" << endl;
    return 0;
}
