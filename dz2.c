#include <stdio.h>

int gcd(int a, int b) {
	 if (b == 0)
		return a;
	return gcd(b, a % b);
}

int lcm(int a, int b) {
	return (a * b) / gcd(a, b);
}

int main() {
	int N, M;
	printf("Введите два натуральных числа N и M: ");

	if (scanf("%d %d", &N, &M) != 2) {
		printf("Ошибка: нужно ввести два числа!\n");
		return 1;
	}

	if (N <= 0 || M <= 0) {
		printf("Ошибка: числа должны быть натуральными (больше 0)!\n");
		return 1;
	}

	int result = lcm(N, M);
	printf("N=%d, M=%d\n", N, M);
	printf("НОК=%d\n", result);

	return 0;
}
