#include "alixpress.hpp"
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {
    char filename[100] = "db.bin";
    
    if (argc > 1) {
        strncpy(filename, argv[1], 99);
        filename[99] = '\0';
    } else {
        cout <<  "Введите имя файла базы данных (по умолчанию: db.bin): ";
        char input[100];
        cin.getline(input, 100);
        if (strlen(input) > 0) {
            strncpy(filename, input, 99);
            filename[99] = '\0';
        }
    }
    
    cout <<  "Используется база данных: " <<  filename <<  "\n\n";
    
    AlixpressDB db(filename);
    db.run();
    
    return 0;
}
