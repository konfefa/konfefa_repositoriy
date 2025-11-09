#include <stdio.h>
#include <stdlib.h>

void add_expense(char* filename) {
        FILE* f = fopen(filename, "a");
        char date[20], cat[50], sum[20], desc[100];

        printf("Дата: "); fgets(date, 20, stdin);
        printf("Категория: "); fgets(cat, 50, stdin);
        printf("Сумма: "); fgets(sum, 20, stdin);
        printf("Описание: "); fgets(desc, 100, stdin);

        fprintf(f, "%s|%s|%s|%s", date, cat, sum, desc);
        fclose(f);
        printf("Добавлено!\n");
}

void view_expenses(char* filename) {
        FILE* f = fopen(filename, "r");
        if (!f) return;

        char line[256];
        while (fgets(line, 256, f)) {
                printf("%s", line);
        }
        fclose(f);
}

int main(int argc, char* argv[]) {
        if (argc != 2) return 1;

        int choice;
        while (1) {
                printf("1-Добавить 2-Просмотреть 3-Выход: ");
                scanf("%d", &choice);
                getchar();

                if (choice == 1) add_expense(argv[1]);
                else if (choice == 2) view_expenses(argv[1]);
                else if (choice == 3) break;
        }
        return 0;
}
