#ifndef ALIXPRESS_H
#define ALIXPRESS_H

typedef struct {
    int id;
    char name[100];
    float price;
    int rating;
    char cat[50];
    int stock;
} Item;

typedef struct {
    Item *data;
    int size;
    int cap;
} Arr;

Arr* create_arr(int cap);
void free_arr(Arr *a);
void add_item(Arr *a, Item i);
void remove_item(Arr *a, int idx);
Item* get_item(Arr *a, int idx);
void save(Arr *a, const char *filename);  // изменено
void load(Arr *a, const char *filename);  // изменено
void show_all(Arr *a);
void find_name(Arr *a, char *name);
void find_price(Arr *a, float min, float max);
void find_cat(Arr *a, char *cat);
void add_new(Arr *a, const char *filename);  // изменено
void delete_item(Arr *a, const char *filename);  // изменено
void edit_item(Arr *a, const char *filename);  // изменено
void menu();

// Вспомогательные функции для валидации
int read_int(const char* prompt, int min_val, int max_val);
float read_float(const char* prompt, float min_val);
void read_string(const char* prompt, char* buffer, int max_len);

#endif
