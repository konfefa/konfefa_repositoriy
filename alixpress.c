#include "alixpress.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void save(Arr *a) {
    FILE *f = fopen(FILE_NAME, "wb");
    if (!f) return;
    fwrite(&a->size, sizeof(int), 1, f);
    fwrite(a->data, sizeof(Item), a->size, f);
    fclose(f);
}

void load(Arr *a) {
    FILE *f = fopen(FILE_NAME, "rb");
    if (!f) return;
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

void add_new(Arr *a) {
    Item new;
    new.id = next_id++;
    printf("Название: ");
    scanf(" %[^\n]", new.name);
    printf("Цена: ");
    scanf("%f", &new.price);
    printf("Рейтинг 1-5: ");
    scanf("%d", &new.rating);
    printf("Категория: ");
    scanf(" %[^\n]", new.cat);
    printf("Склад: ");
    scanf("%d", &new.stock);
    add_item(a, new);
    save(a);
    printf("Добавлено\n");
}

void delete_item(Arr *a) {
    show_all(a);
    printf("ID для удаления: ");
    int id;
    scanf("%d", &id);
    for (int i = 0; i < a->size; i++) {
        Item *it = get_item(a, i);
        if (it->id == id) {
            remove_item(a, i);
            save(a);
            printf("Удалено\n");
            return;
        }
    }
    printf("Не найден\n");
}

void edit_item(Arr *a) {
    show_all(a);
    printf("ID для правки: ");
    int id;
    scanf("%d", &id);
    for (int i = 0; i < a->size; i++) {
        Item *it = get_item(a, i);
        if (it->id == id) {
            char tmp[100];
            printf("Название (пусто=оставить): ");
            getchar();
            fgets(tmp, 100, stdin);
            tmp[strcspn(tmp, "\n")] = 0;
            if (strlen(tmp) > 0) strcpy(it->name, tmp);
            printf("Цена (0=оставить): ");
            float p;
            scanf("%f", &p);
            if (p > 0) it->price = p;
            printf("Рейтинг (0=оставить): ");
            int r;
            scanf("%d", &r);
            if (r >= 1 && r <= 5) it->rating = r;
            printf("Категория (пусто=оставить): ");
            getchar();
            fgets(tmp, 50, stdin);
            tmp[strcspn(tmp, "\n")] = 0;
            if (strlen(tmp) > 0) strcpy(it->cat, tmp);
            printf("Склад (-1=оставить): ");
            int s;
            scanf("%d", &s);
            if (s >= 0) it->stock = s;
            save(a);
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
