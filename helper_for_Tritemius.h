#ifndef TRITHEMIUS_H
#define TRITHEMIUS_H

#include <string>

using namespace std;

// Информация о шифре
string trithemius_getName();
string trithemius_getDescription();

// Генерация ключа
int trithemius_generateKey();

// Установка ключа
void trithemius_setKey(int shift);
int trithemius_getKey();

// Шифрование/дешифрование
string trithemius_encrypt(const string& data);
string trithemius_decrypt(const string& data);

// Проверка ключа
bool trithemius_isValidKey(int shift);

// Меню (для работы с этим шифром)
void trithemius_menu();

#endif