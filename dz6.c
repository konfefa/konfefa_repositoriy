#include "alixpress.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        strncpy(FILE_NAME, argv[1], sizeof(FILE_NAME) - 1);
        FILE_NAME[sizeof(FILE_NAME) - 1] = '\0';
    } else {
        printf("Введите имя файла базы данных (по умолчанию: db.bin): ");
        char input[100];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        
        if (strlen(input) > 0) {
            strncpy(FILE_NAME, input, sizeof(FILE_NAME) - 1);
            FILE_NAME[sizeof(FILE_NAME) - 1] = '\0';
        }
    }
    
    printf("Используется база данных: %s\n", FILE_NAME);
    
    Arr *db = create_arr(10);
    load(db);
    int ch;
    char s[100];
    float min, max;
    char cat[50];
    
    do {
        menu();
        scanf("%d", &ch);
        getchar();
        
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
