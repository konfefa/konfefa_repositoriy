#include "alixpress.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    string filename = "db.bin";
    
    if (argc > 1) {
        filename = argv[1];
    } else {
        cout << "Введите имя файла базы данных (по умолчанию: db.bin): ";
        string input;
        getline(cin, input);
        if (!input.empty()) {
            filename = input;
        }
    }
    
    cout << "Используется база данных: " << filename << "\n\n";
    
    AlixpressDB db(filename);
    db.run();
    
    return 0;
}
