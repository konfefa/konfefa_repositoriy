#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[1], "r");
    int N, M;
    fscanf(f, "%d %d", &N, &M);

    int **a = (int** )malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        a[i] = (int *)malloc(M * sizeof(int));
        for (int j = 0; j < M; j++) {
            fscanf(f, "%d", &a[i][j]);
        }
	if (argc != 2) {
        	fprintf(stderr, "Ошибка: Не указано имя файла.\n");
        	exit(EXIT_FAILURE);
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
    printf("Сумма отриц.  элементов на побочной диагонали: %d\n", sum);

    int max = a[0][1];
    int maxRow = 0;
    for (int i = 1; i < N; i++) {
        if (a[i][1] > max) {
            max = a[i][1];
            maxRow = i;
        }
    }
    printf("макс элемент второго столбца: %d, Тндекс строки: %d\n", max, maxRow);

    a[maxRow][1] = sum;

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
