#include "alixpress.h"
#include <stdio.h>

int main() {
    Arr *db = create_arr(10);
    load(db);
    int ch;
    char s[100];
    float min, max;
    char cat[50];
    
    do {
        menu();
        scanf("%d", &ch);
        switch(ch) {
            case 1: show_all(db); break;
            case 2:
                printf("Название: ");
                scanf(" %[^\n]", s);
                find_name(db, s);
                break;
            case 3:
                printf("От: ");
                scanf("%f", &min);
                printf("До: ");
                scanf("%f", &max);
                find_price(db, min, max);
                break;
            case 4:
                printf("Категория: ");
                scanf(" %[^\n]", cat);
                find_cat(db, cat);
                break;
            case 5: add_new(db); break;
            case 6: delete_item(db); break;
            case 7: edit_item(db); break;
            case 8:
                save(db);
                printf("Выход\n");
                break;
            default: printf("Нет\n");
        }
    } while (ch != 8);
    
    free_arr(db);
    return 0;
}
