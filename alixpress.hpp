#ifndef ALIXPRESS_HPP
#define ALIXPRESS_HPP

#include <string>
#include <vector>

struct Item {
    int id;
    std::string name;
    double price;
    int rating;
    std::string category;
    int stock;
};

class AlixpressDB {
private:
    std::vector<Item> items;
    std::string filename;
    int nextId;
    
    void saveToFile();
    void loadFromFile();
    int findIndexById(int id) const;
    
public:
    AlixpressDB(const std::string& filename = "db.bin");
    ~AlixpressDB();
    
    void showAll() const;
    void findByName(const std::string& name) const;
    void findByPrice(double min, double max) const;
    void findByCategory(const std::string& category) const;
    void addNew();
    void deleteItem();
    void editItem();
    
    void run();
};

int readInt(const std::string& prompt, int minVal, int maxVal);
double readDouble(const std::string& prompt, double minVal);
std::string readString(const std::string& prompt);

#endif
