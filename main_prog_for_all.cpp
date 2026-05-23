#include "cipher_helper.h"
#include "helper_for_Vernam.h"
#include "helper_for_Tritemius.h"

// Здесь ваши коллеги добавят свои шифры:
// #include "caesar.h"
// #include "vigenere.h"

int main() {
    setlocale(LC_ALL, "Russian");
    
    while (true) {
        clearScreen();
        cout << "========================================\n";
        cout << "     КРИПТОГРАФИЧЕСКАЯ СИСТЕМА\n";
        cout << "========================================\n";
        cout << "  Доступные шифры:\n";
        cout << "    1. " << vernam_getName() << " - " << vernam_getDescription() << "\n";
        cout << "    2. " << trithemius_getName() << " - " << trithemius_getDescription() << "\n";
        
        // Коллеги добавят свои строки:
        // cout << "    3. " << caesar_getName() << " - " << caesar_getDescription() << "\n";
        
        cout << "    0. Выход\n";
        cout << "========================================\n";
        cout << "Выберите шифр: ";
        
        int choice;
        cin >> choice;
        
        if (choice == 0) {
            cout << "До свидания!\n";
            break;
        }
        
        if (choice == 1) {
            vernam_menu();
        } else if (choice == 2) {
            trithemius_menu();
        }
        // Коллеги добавят свои условия:
        // else if (choice == 3) {
        //     caesar_menu();
        // }
        else {
            cout << "Неверный выбор!\n";
            waitForKey();
        }
    }
    
    return 0;
}