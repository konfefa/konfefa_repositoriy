#ifndef ALIXPRESS_H
#define ALIXPRESS_H

#define FILE_NAME "db.bin"

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
void save(Arr *a);
void load(Arr *a);
void show_all(Arr *a);
void find_name(Arr *a, char *name);
void find_price(Arr *a, float min, float max);
void find_cat(Arr *a, char *cat);
void add_new(Arr *a);
void delete_item(Arr *a);
void edit_item(Arr *a);
void menu();

#endif
