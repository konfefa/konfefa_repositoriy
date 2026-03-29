#ifndef ALIXPRESS_HPP
#define ALIXPRESS_HPP

const int MAX_NAME_LEN = 100;
const int MAX_CAT_LEN = 50;

struct Item {
    int id;
    char name[MAX_NAME_LEN];
    double price;
    int rating;
    char category[MAX_CAT_LEN];
    int stock;
};

class MyVector {
private:
    Item* data;
    int size;
    int capacity;
    
public:
    MyVector();
    ~MyVector();
    void push_back(const Item& item);
    void remove_at(int index);
    Item& operator[](int index);
    const Item& operator[](int index) const;
    int get_size() const;
    void clear();
};

class AlixpressDB {
private:
    MyVector items;
    char filename[100];
    int nextId;
    
    void saveToFile();
    void loadFromFile();
    int findIndexById(int id) const;
    
public:
    AlixpressDB(const char* fname);
    ~AlixpressDB();
    
    void showAll() const;
    void findByName(const char* name) const;
    void findByPrice(double min, double max) const;
    void findByCategory(const char* category) const;
    void addNew();
    void deleteItem();
    void editItem();
    void run();
};

int readInt(const char* prompt, int minVal, int maxVal);
double readDouble(const char* prompt, double minVal);
void readString(const char* prompt, char* buffer, int maxLen);

#endif
