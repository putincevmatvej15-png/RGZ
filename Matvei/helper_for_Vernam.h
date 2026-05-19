#ifndef VERNAM_H
#define VERNAM_H

#include <string>

using namespace std;

// Информация о шифре
string vernam_getName();
string vernam_getDescription();

// Генерация ключа
string vernam_generateKey(int length);

// Установка ключа
void vernam_setKey(const string& key);
string vernam_getKey();

// Шифрование/дешифрование
string vernam_encrypt(const string& data);
string vernam_decrypt(const string& data);

// Проверка ключа
bool vernam_isValidKey(const string& key, int dataLen = 0);

// Меню (для работы с этим шифром)
void vernam_menu();

#endif