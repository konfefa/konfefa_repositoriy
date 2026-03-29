#include "alixpress.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <limits>

using namespace std;

int readInt(const char* prompt, int minVal, int maxVal) {
    int value;
    char input[100];
    
    while (true) {
        cout <<   prompt;
        cin.getline(input, 100);
        
        if (sscanf(input, "%d", &value) == 1) {
            if (value >= minVal && value <= maxVal) {
                return value;
            } else {
                cout <<   "Ошибка: число должно быть от " <<   minVal <<   " до " <<   maxVal <<   "\n";
            }
        } else {
            cout <<   "Ошибка: введите целое число\n";
        }
    }
}

double readDouble(const char* prompt, double minVal) {
    double value;
    char input[100];
    
    while (true) {
        cout <<   prompt;
        cin.getline(input, 100);
        
        if (sscanf(input, "%lf", &value) == 1) {
            if (value >= minVal) {
                return value;
            } else {
                cout <<   "Ошибка: число должно быть >= " <<   minVal <<   "\n";
            }
        } else {
            cout <<   "Ошибка: введите число\n";
        }
    }
}

void readString(const char* prompt, char* buffer, int maxLen) {
    cout <<   prompt;
    cin.getline(buffer, maxLen);
}

MyVector::MyVector() : size(0), capacity(10) {
    data = new Item[capacity];
}

MyVector::~MyVector() {
    delete[] data;
}

void MyVector::push_back(const Item& item) {
    if (size >= capacity) {
        capacity *= 2;
        Item* newData = new Item[capacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    data[size++] = item;
}

void MyVector::remove_at(int index) {
    if (index < 0 || index >= size) return;
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

Item& MyVector::operator[](int index) {
    return data[index];
}

const Item& MyVector::operator[](int index) const {
    return data[index];
}

int MyVector::get_size() const {
    return size;
}

void MyVector::clear() {
    size = 0;
}

AlixpressDB::AlixpressDB(const char* fname) : nextId(1) {
    strncpy(filename, fname, 99);
    filename[99] = '\0';
    loadFromFile();
    for (int i = 0; i < items.get_size(); i++) {
        if (items[i].id >= nextId) {
            nextId = items[i].id + 1;
        }
    }
}

AlixpressDB::~AlixpressDB() {
    saveToFile();
}

void AlixpressDB::saveToFile() {
    ofstream file(filename, ios::binary);
    if (!file) {
        cout <<   "Ошибка сохранения в файл " <<   filename <<   "\n";
        return;
    }
    
    int size = items.get_size();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    
    for (int i = 0; i < size; i++) {
        const Item& item = items[i];
        file.write(reinterpret_cast<const char*>(&item.id), sizeof(item.id));
        file.write(reinterpret_cast<const char*>(&item.price), sizeof(item.price));
        file.write(reinterpret_cast<const char*>(&item.rating), sizeof(item.rating));
        file.write(reinterpret_cast<const char*>(&item.stock), sizeof(item.stock));
        file.write(item.name, MAX_NAME_LEN);
        file.write(item.category, MAX_CAT_LEN);
    }
    
    file.close();
}

void AlixpressDB::loadFromFile() {
    ifstream file(filename, ios::binary);
    if (!file) {
        cout <<   "Файл " <<   filename <<   " не найден. Создана новая база.\n";
        return;
    }
    
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    items.clear();
    
    for (int i = 0; i < size; i++) {
        Item item;
        file.read(reinterpret_cast<char*>(&item.id), sizeof(item.id));
        file.read(reinterpret_cast<char*>(&item.price), sizeof(item.price));
        file.read(reinterpret_cast<char*>(&item.rating), sizeof(item.rating));
        file.read(reinterpret_cast<char*>(&item.stock), sizeof(item.stock));
        file.read(item.name, MAX_NAME_LEN);
	file.read(item.category, MAX_CAT_LEN);
	        items.push_back(item);
    }
    
    file.close();
}

int AlixpressDB::findIndexById(int id) const {
    for (int i = 0; i < items.get_size(); i++) {
        if (items[i].id == id) {
            return i;
        }
    }
    return -1;
}

void AlixpressDB::showAll() const {
    cout <<   "\nВсего товаров: " <<   items.get_size() <<   "\n";
    cout <<   string(80, '-') <<   "\n";
    
    for (int i = 0; i < items.get_size(); i++) {
        const Item& item = items[i];
        cout <<   item.id <<   ". "
             <<   item.name <<   " | $"
             <<   fixed <<   setprecision(2) <<   item.price
             <<   " | " <<   item.rating <<   "/5"
             <<   " | " <<   item.category
             <<   " | Склад: " <<   item.stock <<   "\n";
    }
    cout <<   string(80, '-') <<   "\n";
}

void AlixpressDB::findByName(const char* name) const {
    bool found = false;
    for (int i = 0; i < items.get_size(); i++) {
        const Item& item = items[i];
        if (strstr(item.name, name) != nullptr) {
            cout <<   item.id <<   ". " <<   item.name <<   " | $" <<   fixed <<   setprecision(2) <<   item.price <<   "\n";
            found = true;
        }
    }
    if (!found) cout <<   "Товары не найдены\n";
}

void AlixpressDB::findByPrice(double min, double max) const {
    bool found = false;
    for (int i = 0; i < items.get_size(); i++) {
        const Item& item = items[i];
        if (item.price >= min && item.price <= max) {
            cout <<   item.id <<   ". " <<   item.name <<   " | $" <<   fixed <<   setprecision(2) <<   item.price <<   "\n";
            found = true;
        }
    }
    if (!found) cout <<   "Товары не найдены\n";
}

void AlixpressDB::findByCategory(const char* category) const {
    bool found = false;
    for (int i = 0; i < items.get_size(); i++) {
        const Item& item = items[i];
        if (strcmp(item.category, category) == 0) {
            cout <<   item.id <<   ". " <<   item.name <<   " | $" <<   fixed <<   setprecision(2) <<   item.price <<   "\n";
            found = true;
        }
    }
    if (!found) cout <<   "Товары не найдены\n";
}

void AlixpressDB::addNew() {
    Item newItem;
    newItem.id = nextId++;
    
    readString("Название: ", newItem.name, MAX_NAME_LEN);
    newItem.price = readDouble("Цена: ", 0.0);
    newItem.rating = readInt("Рейтинг (1-5): ", 1, 5);
    readString("Категория: ", newItem.category, MAX_CAT_LEN);
    newItem.stock = readInt("Количество на складе: ", 0, 10000);
    
    items.push_back(newItem);
    saveToFile();
    cout <<   "Товар добавлен! ID: " <<   newItem.id <<   "\n";
}

void AlixpressDB::deleteItem() {
    showAll();
    int id = readInt("ID товара для удаления: ", 1, 10000);
    
    int index = findIndexById(id);
    if (index != -1) {
        items.remove_at(index);
        saveToFile();
        cout <<   "Товар удалён\n";
    } else {
        cout <<   "Товар с ID " <<   id <<   " не найден\n";
    }
}

void AlixpressDB::editItem() {
    showAll();
    int id = readInt("ID товара для редактирования: ", 1, 10000);
    
    int index = findIndexById(id);
    if (index == -1) {
        cout <<   "Товар с ID " <<   id <<   " не найден\n";
        return;
    }
    
    Item& item = items[index];
    char tmp[100];
    
    readString("Название (Enter - оставить): ", tmp, 100);
    if (strlen(tmp) > 0) strcpy(item.name, tmp);
    
    double price = readDouble("Цена (0 - оставить): ", 0.0);
    if (price > 0) item.price = price;
    
    int rating = readInt("Рейтинг (0 - оставить): ", 0, 5);
    if (rating >= 1 && rating <= 5) item.rating = rating;
    
    readString("Категория (Enter - оставить): ", tmp, 100);
    if (strlen(tmp) > 0) strcpy(item.category, tmp);
    
    int stock = readInt("Склад (-1 - оставить): ", -1, 10000);
    if (stock >= 0) item.stock = stock;
    
    saveToFile();
    cout <<   "Изменения сохранены\n";
}

void AlixpressDB::run() {
    int choice;
    char searchStr[100];
    double minPrice, maxPrice;
    char category[50];
    
    do {
        cout <<   "\n╔══════════════════════════════════╗\n";
        cout <<   "║УПРАВЛЕНИЕ ТОВАРАМИ               ║\n";
        cout <<   "╠══════════════════════════════════╣\n";
        cout <<   "║ 1. Все товары                    ║\n";
        cout <<   "║ 2. Поиск по названию             ║\n";
        cout <<   "║ 3. Поиск по цене                 ║\n";
        cout <<   "║ 4. Поиск по категории            ║\n";
        cout <<   "║ 5. Добавить товар                ║\n";
        cout <<   "║ 6. Удалить товар                 ║\n";
        cout <<   "║ 7. Редактировать товар           ║\n";
        cout <<   "║ 8. Выход                         ║\n";
        cout <<   "╚══════════════════════════════════╝\n";
        cout <<   "Выбор: ";
        
        cin >>   choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                showAll();
                break;
            case 2:
                cout <<   "Название: ";
                cin.getline(searchStr, 100);
                findByName(searchStr);
                break;
            case 3:
                minPrice = readDouble("Цена от: ", 0.0);
                maxPrice = readDouble("Цена до: ", minPrice);
                findByPrice(minPrice, maxPrice);
                break;
            case 4:
                cout <<   "Категория: ";
                cin.getline(category, 50);
                findByCategory(category);
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
                cout <<   "Выход...\n";
                break;
            default:
                cout <<   "Неверный выбор\n";
        }
    } while (choice != 8);
}
