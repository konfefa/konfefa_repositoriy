#include "alixpress.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char filename[100] = "db.bin"; 
    
    if (argc > 1) {
        strncpy(filename, argv[1], sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0';
    } else {
        printf("Введите имя файла базы данных (по умолчанию: db.bin): ");
        char input[100];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        
        if (strlen(input) > 0) {
            strncpy(filename, input, sizeof(filename) - 1);
            filename[sizeof(filename) - 1] = '\0';
        }
    }
    
    printf("Используется база данных: %s\n", filename);
    
    Arr *db = create_arr(10);
    load(db, filename);
    
    int ch;
    char s[100];
    float min, max;
    char cat[50];
    
    do {
        menu();
        if (scanf("%d", &ch) != 1) {
            printf("Ошибка ввода!\n");
            while (getchar() != '\n');
            continue;
        }
        
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
            case 5: add_new(db, filename); break;      
            case 6: delete_item(db, filename); break;
            case 7: edit_item(db, filename); break;
            case 8:
                save(db, filename); 
                printf("Выход\n");
                break;
            default: printf("Нет\n");
        }
        while (getchar() != '\n'); 
    } while (ch != 8);
    
    free_arr(db);
    return 0;
}
