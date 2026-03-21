#include "alixpress.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

int readInt(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка: введите целое число\n";
        } else if (value >= minVal && value <= maxVal) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "Ошибка: число должно быть от " << minVal << " до " << maxVal << "\n";
        }
    }
}

double readDouble(const string& prompt, double minVal) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка: введите число\n";
        } else if (value >= minVal) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "Ошибка: число должно быть >= " << minVal << "\n";
        }
    }
}

string readString(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

AlixpressDB::AlixpressDB(const string& fname) : filename(fname), nextId(1) {
    loadFromFile();
    for (const auto& item : items) {
        if (item.id >= nextId) {
            nextId = item.id + 1;
        }
    }
}

AlixpressDB::~AlixpressDB() {
    saveToFile();
}

void AlixpressDB::saveToFile() {
    ofstream file(filename, ios::binary);
    if (!file) {
        cout << "Ошибка сохранения в файл " << filename << "\n";
        return;
    }
    
    size_t size = items.size();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    
    for (const auto& item : items) {
        file.write(reinterpret_cast<const char*>(&item.id), sizeof(item.id));
        file.write(reinterpret_cast<const char*>(&item.price), sizeof(item.price));
        file.write(reinterpret_cast<const char*>(&item.rating), sizeof(item.rating));
        file.write(reinterpret_cast<const char*>(&item.stock), sizeof(item.stock));
        
        size_t len = item.name.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(item.name.c_str(), len);
        
        len = item.category.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(item.category.c_str(), len);
    }
    
    file.close();
}

void AlixpressDB::loadFromFile() {
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Файл " << filename << " не найден. Создана новая база.\n";
        return;
    }
    
    size_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    items.clear();
    items.reserve(size);
    
    for (size_t i = 0; i < size; i++) {
        Item item;
        
        file.read(reinterpret_cast<char*>(&item.id), sizeof(item.id));
        file.read(reinterpret_cast<char*>(&item.price), sizeof(item.price));
        file.read(reinterpret_cast<char*>(&item.rating), sizeof(item.rating));
        file.read(reinterpret_cast<char*>(&item.stock), sizeof(item.stock));
        
        size_t len;
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        item.name.resize(len);
        file.read(&item.name[0], len);
        
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        item.category.resize(len);
        file.read(&item.category[0], len);
        
        items.push_back(item);
    }
    
    file.close();
}

int AlixpressDB::findIndexById(int id) const {
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].id == id) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void AlixpressDB::showAll() const {
    cout << "\nВсего товаров: " << items.size() << "\n";
    cout << string(80, '-') << "\n";
    
    for (const auto& item : items) {
        cout << item.id << ". "
             << item.name << " | $"
             << fixed << setprecision(2) << item.price
             << " | " << item.rating << "/5"
             << " | " << item.category
             << " | Склад: " << item.stock << "\n";
    }
    cout << string(80, '-') << "\n";
}

void AlixpressDB::findByName(const string& name) const {
    bool found = false;
    for (const auto& item : items) {
        if (item.name.find(name) != string::npos) {
            cout << item.id << ". " << item.name << " | $" << fixed << setprecision(2) << item.price << "\n";
            found = true;
        }
    }
    if (!found) cout << "Товары не найдены\n";
}

void AlixpressDB::findByPrice(double min, double max) const {
    bool found = false;
    for (const auto& item : items) {
        if (item.price >= min && item.price <= max) {
            cout << item.id << ". " << item.name << " | $" << fixed << setprecision(2) << item.price << "\n";
            found = true;
        }
    }
    if (!found) cout << "Товары не найдены\n";
}

void AlixpressDB::findByCategory(const string& category) const {
    bool found = false;
    for (const auto& item : items) {
        if (item.category == category) {
            cout << item.id << ". " << item.name << " | $" << fixed << setprecision(2) << item.price << "\n";
            found = true;
        }
    }
    if (!found) cout << "Товары не найдены\n";
}

void AlixpressDB::addNew() {
    Item newItem;
    newItem.id = nextId++;
    
    newItem.name = readString("Название: ");
    newItem.price = readDouble("Цена: ", 0.0);
    newItem.rating = readInt("Рейтинг (1-5): ", 1, 5);
    newItem.category = readString("Категория: ");
    newItem.stock = readInt("Количество на складе: ", 0, 10000);
    
    items.push_back(newItem);
    saveToFile();
    cout << "Товар добавлен! ID: " << newItem.id << "\n";
}

void AlixpressDB::deleteItem() {
    showAll();
    int id = readInt("ID товара для удаления: ", 1, 10000);
    
    int index = findIndexById(id);
    if (index != -1) {
        items.erase(items.begin() + index);
        saveToFile();
        cout << "Товар удалён\n";
    } else {
        cout << "Товар с ID " << id << " не найден\n";
    }
}

void AlixpressDB::editItem() {
    showAll();
    int id = readInt("ID товара для редактирования: ", 1, 10000);
    
    int index = findIndexById(id);
    if (index == -1) {
        cout << "Товар с ID " << id << " не найден\n";
        return;
    }
    
    Item& item = items[index];
    
    string tmp = readString("Название (Enter - оставить): ");
    if (!tmp.empty()) item.name = tmp;
    
    double price = readDouble("Цена (0 - оставить): ", 0.0);
    if (price > 0) item.price = price;
    
    int rating = readInt("Рейтинг (0 - оставить): ", 0, 5);
    if (rating >= 1 && rating <= 5) item.rating = rating;
    
    tmp = readString("Категория (Enter - оставить): ");
    if (!tmp.empty()) item.category = tmp;
    
    int stock = readInt("Склад (-1 - оставить): ", -1, 10000);
    if (stock >= 0) item.stock = stock;
    
    saveToFile();
    cout << "Изменения сохранены\n";
}

static void showMenu() {
    cout << "\n╔══════════════════════════════════╗\n";
    cout << "║         УПРАВЛЕНИЕ ТОВАРАМИ       ║\n";
    cout << "╠══════════════════════════════════╣\n";
    cout << "║ 1. Все товары                    ║\n";
    cout << "║ 2. Поиск по названию             ║\n";
    cout << "║ 3. Поиск по цене                 ║\n";
    cout << "║ 4. Поиск по категории            ║\n";
    cout << "║ 5. Добавить товар                ║\n";
    cout << "║ 6. Удалить товар                 ║\n";
    cout << "║ 7. Редактировать товар           ║\n";
    cout << "║ 8. Выход                         ║\n";
    cout << "╚══════════════════════════════════╝\n";
    cout << "Выбор: ";
}

void AlixpressDB::run() {
    int choice;
    string searchStr;
    double minPrice, maxPrice;
    
    do {
        showMenu();
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода!\n";
            continue;
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                showAll();
                break;
            case 2:
                searchStr = readString("Название: ");
                findByName(searchStr);
                break;
            case 3:
                minPrice = readDouble("Цена от: ", 0.0);
                maxPrice = readDouble("Цена до: ", minPrice);
                findByPrice(minPrice, maxPrice);
                break;
            case 4:
                searchStr = readString("Категория: ");
                findByCategory(searchStr);
                break;
            case 5:
                addNew();
                break;
            case 6:
                deleteItem();
                break;
            case 7:
                editItem();
                break;
            case 8:
                cout << "Выход...\n";
                break;
            default:
                cout << "Неверный выбор\n";
        }
    } while (choice != 8);
}
