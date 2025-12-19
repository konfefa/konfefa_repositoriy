#include "alixpress.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int read_int(const char* prompt, int min_val, int max_val) {
    int value;
    char input[100];
    
    while (1) {
        printf("%s", prompt);
        fgets(input, sizeof(input), stdin);
        
        if (sscanf(input, "%d", &value) == 1) {
            if (value >= min_val && value <= max_val) {
                return value;
            } else {
                printf("Ошибка: число должно быть от %d до %d\n", min_val, max_val);
            }
        } else {
            printf("Ошибка: введите целое число\n");
        }
    }
}


float read_float(const char* prompt, float min_val) {
    float value;
    char input[100];
    
    while (1) {
        printf("%s", prompt);
        fgets(input, sizeof(input), stdin);
        
        if (sscanf(input, "%f", &value) == 1) {
            if (value >= min_val) {
                return value;
            } else {
                printf("Ошибка: число должно быть >= %.2f\n", min_val);
            }
        } else {
            printf("Ошибка: введите число\n");
        }
    }
}

void read_string(const char* prompt, char* buffer, int max_len) {
    printf("%s", prompt);
    fgets(buffer, max_len, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

Arr* create_arr(int cap) {
    Arr *a = malloc(sizeof(Arr));
    a->data = malloc(cap * sizeof(Item));
    a->size = 0;
    a->cap = cap;
    return a;
}

void free_arr(Arr *a) {
    free(a->data);
    free(a);
}

void add_item(Arr *a, Item i) {
    if (a->size >= a->cap) {
        a->cap *= 2;
        a->data = realloc(a->data, a->cap * sizeof(Item));
    }
    a->data[a->size++] = i;
}

void remove_item(Arr *a, int idx) {
    if (idx < 0 || idx >= a->size) return;
    for (int i = idx; i < a->size - 1; i++) {
        a->data[i] = a->data[i + 1];
    }
    a->size--;
}

Item* get_item(Arr *a, int idx) {
    if (idx < 0 || idx >= a->size) return NULL;
    return &a->data[idx];
}

void save(Arr *a, const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (!f) {
        printf("Ошибка сохранения в файл %s\n", filename);
        return;
    }
    fwrite(&a->size, sizeof(int), 1, f);
    fwrite(a->data, sizeof(Item), a->size, f);
    fclose(f);
}

void load(Arr *a, const char *filename) {  
    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("Файл %s не найден. Создана новая база.\n", filename);
        return;
    }
    int s;
    fread(&s, sizeof(int), 1, f);
    for (int i = 0; i < s; i++) {
        Item it;
        fread(&it, sizeof(Item), 1, f);
        add_item(a, it);
    }
    fclose(f);
}

void show_all(Arr *a) {
    printf("\nВсего: %d\n", a->size);
    for (int i = 0; i < a->size; i++) {
        Item *it = get_item(a, i);
        printf("%d. %s | $%.2f | %d/5 | %s | %d\n",
               it->id, it->name, it->price, it->rating, it->cat, it->stock);
    }
}

void find_name(Arr *a, char *name) {
    int f = 0;
    for (int i = 0; i < a->size; i++) {
        Item *it = get_item(a, i);
        if (strstr(it->name, name)) {
            printf("%d. %s | $%.2f\n", it->id, it->name, it->price);
            f = 1;
        }
    }
    if (!f) printf("Нет\n");
}

void find_price(Arr *a, float min, float max) {
    int f = 0;
    for (int i = 0; i < a->size; i++) {
        Item *it = get_item(a, i);
        if (it->price >= min && it->price <= max) {
            printf("%d. %s | $%.2f\n", it->id, it->name, it->price);
            f = 1;
        }
    }
    if (!f) printf("Нет\n");
}

void find_cat(Arr *a, char *cat) {
    int f = 0;
    for (int i = 0; i < a->size; i++) {
        Item *it = get_item(a, i);
        if (strcmp(it->cat, cat) == 0) {
            printf("%d. %s | $%.2f\n", it->id, it->name, it->price);
            f = 1;
        }
    }
    if (!f) printf("Нет\n");
}

static int next_id = 1;

void add_new(Arr *a, const char *filename) {  
    Item new;
    new.id = next_id++;
    
    read_string("Название: ", new.name, sizeof(new.name));
    new.price = read_float("Цена: ", 0.0);
    new.rating = read_int("Рейтинг 1-5: ", 1, 5);
    read_string("Категория: ", new.cat, sizeof(new.cat));
    new.stock = read_int("Склад: ", 0, 10000);
    
    add_item(a, new);
    save(a, filename);  
    printf("Добавлено\n");
}

void delete_item(Arr *a, const char *filename) { 
    show_all(a);
    int id = read_int("ID для удаления: ", 1, 10000);
    
    for (int i = 0; i < a->size; i++) {
        Item *it = get_item(a, i);
        if (it->id == id) {
            remove_item(a, i);
            save(a, filename);  
            printf("Удалено\n");
            return;
        }
    }
    printf("Не найден\n");
}

void edit_item(Arr *a, const char *filename) { 
    show_all(a);
    int id = read_int("ID для правки: ", 1, 10000);
    
    for (int i = 0; i < a->size; i++) {
        Item *it = get_item(a, i);
        if (it->id == id) {
            char tmp[100];
            
            read_string("Название (пусто=оставить): ", tmp, sizeof(tmp));
            if (strlen(tmp) > 0) strcpy(it->name, tmp);
            
            float p = read_float("Цена (0=оставить): ", 0.0);
            if (p > 0) it->price = p;
            
            int r = read_int("Рейтинг (0=оставить): ", 0, 5);
            if (r >= 1 && r <= 5) it->rating = r;
            
            read_string("Категория (пусто=оставить): ", tmp, sizeof(tmp));
            if (strlen(tmp) > 0) strcpy(it->cat, tmp);
            
            int s = read_int("Склад (-1=оставить): ", -1, 10000);
            if (s >= 0) it->stock = s;
            
            save(a, filename); 
            printf("Сохранено\n");
            return;
        }
    }
    printf("Не найден\n");
}

void menu() {
    printf("\n1. Все товары\n");
    printf("2. Поиск по названию\n");
    printf("3. Поиск по цене\n");
    printf("4. Поиск по категории\n");
    printf("5. Добавить\n");
    printf("6. Удалить\n");
    printf("7. Править\n");
    printf("8. Выход\n");
    printf("Выбор: ");
}
