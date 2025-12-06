#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 10000;
    }
}

void copy(int s[], int d[], int n) {
    for (int i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

void bubble(int a[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (a[j] > a[j+1]) {
                int t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
        }
    }
}

void insert(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int k = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > k) {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = k;
    }
}

void gnome(int a[], int n) {
    int i = 0;
    while (i < n) {
        if (i == 0) i++;
        if (a[i] >= a[i-1]) {
            i++;
        } else {
            int t = a[i];
            a[i] = a[i-1];
            a[i-1] = t;
            i--;
        }
    }
}

int check(int a[], int n) {
    for (int i = 0; i < n-1; i++) {
        if (a[i] > a[i+1]) return 0;
    }
    return 1;
}

int main() {
    srand(time(NULL));
    
    int sz[] = {10, 1000, 10000, 100000};
    int ns = 4;
    
    printf("Размер | Пузырек | Вставки | Слизняк |\n");
    
    for (int s = 0; s < ns; s++) {
        int n = sz[s];
        
        int *m = malloc(n * sizeof(int));
        if (!m) {
            printf("Ошибка памяти!\n");
            return 1;
        }
        
        fill(m, n);
        
        int *a1 = malloc(n * sizeof(int));
        int *a2 = malloc(n * sizeof(int));
        int *a3 = malloc(n * sizeof(int));
        
        if (!a1  !a2  !a3) {
            printf("Ошибка памяти!\n");
            free(m);
            free(a1);
            free(a2);
            free(a3);
            return 1;
        }
        
        double t1, t2, t3;
        
        copy(m, a1, n);
        clock_t st1 = clock();
        bubble(a1, n);
        t1 = (double)(clock() - st1) / CLOCKS_PER_SEC;
        
        copy(m, a2, n);
        clock_t st2 = clock();
        insert(a2, n);
        t2 = (double)(clock() - st2) / CLOCKS_PER_SEC;
        
        copy(m, a3, n);
        clock_t st3 = clock();
        gnome(a3, n);
        t3 = (double)(clock() - st3) / CLOCKS_PER_SEC;
        
        if (!check(a1, n)  !check(a2, n)  !check(a3, n)) {
            printf("Ошибка для %d!\n", n);
        }
        
        if (n == 10) {
            printf("%6d | %7.6f | %7.6f | %7.6f |\n", n, t1, t2, t3);
        } else if (n == 1000) {
            printf("%6d | %7.4f | %7.4f | %7.4f |\n", n, t1, t2, t3);
        } else {
            printf("%6d | %7.3f | %7.3f | %7.3f |\n", n, t1, t2, t3);
        }
        
        free(m);
        free(a1);
        free(a2);
        free(a3);
    }
    
    printf("\nВыводы:\n");
    printf("1. Для маленьких массивов разница незначительна\n");
    printf("2. Для больших массивов сортировка вставками обычно быстрее\n");
    printf("3. Пузырьковая сортировка самая медленная для больших данных\n");
    
    return 0;
}
