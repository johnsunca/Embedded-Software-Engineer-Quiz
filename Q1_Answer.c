/*
	== Answer to Q1 ==
*/
#include <stdio.h>

int main() {
	int m, n, count = 0;
	printf("Input: ");
	scanf("%d%d", &m, &n);

	printf("Output: ");
	while(m >= 1 && n >= 1) {
		if (count != 0) 
			putchar(',');
		if (m > n) {
			printf("%dx%d", n, n);
			m = m - n;
			count++;
		} else if (m < n) {
			printf("%dx%d", m, m);
			n = n - m;
			count++;
		} else {
			printf("%dx%d", n, n);			
			return;
		}
	}
}

