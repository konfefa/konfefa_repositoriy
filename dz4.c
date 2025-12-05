#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Ошибка: Не указано имя файла.\n");
        fprintf(stderr, "Использование: %s <имя_файла>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "Ошибка: Не удалось открыть файл '%s'\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    int N, M;
    if (fscanf(f, "%d %d", &N, &M) != 2) {
        fprintf(stderr, "Ошибка: Не удалось прочитать размеры матрицы из файла\n");
        fclose(f);
        exit(EXIT_FAILURE);
    }

    if (N <= 0 || M <= 0) {
        fprintf(stderr, "Ошибка: Некорректные размеры матрицы: N=%d, M=%d\n", N, M);
        fclose(f);
        exit(EXIT_FAILURE);
    }

    int a = (int)malloc(N * sizeof(int *));
    if (a == NULL) {
        fprintf(stderr, "Ошибка: Не удалось выделить память для указателей на строки\n");
        fclose(f);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++) {
        a[i] = (int *)malloc(M * sizeof(int));
        if (a[i] == NULL) {
            fprintf(stderr, "Ошибка: Не удалось выделить память для строки %d\n", i);

            for (int k = 0; k < i; k++) {
                free(a[k]);
            }
            free(a);
            fclose(f);
            exit(EXIT_FAILURE);
        }
        
        for (int j = 0; j < M; j++) {
            if (fscanf(f, "%d", &a[i][j]) != 1) {
                fprintf(stderr, "Ошибка: Не удалось прочитать элемент [%d][%d] из файла\n", i, j);

                for (int k = 0; k <= i; k++) {
                    free(a[k]);
                }
                free(a);
                fclose(f);
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(f);

    int sum = 0;
    for (int i = 0; i < N; i++) {
        int j = M - 1 - i;
        if (j >= 0 && a[i][j] < 0) {
            sum += a[i][j];
        }
    }
    printf("Сумма отриц. элементов на побочной диагонали: %d\n", sum);

    int max, maxRow;
    if (M >= 2) {
        max = a[0][1];
        maxRow = 0;
        for (int i = 1; i < N; i++) {
            if (a[i][1] > max) {
                max = a[i][1];
                maxRow = i;
            }
        }
        printf("Макс элемент второго столбца: %d, Индекс строки: %d\n", max, maxRow);
        
        a[maxRow][1] = sum;
    } else {
        fprintf(stderr, "Предупреждение: Второй столбец отсутствует (M=%d)\n", M);
    }

    printf("Ответ:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
        free(a[i]);
    }
    free(a);

    return 0;
}
