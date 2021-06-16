#include <stdio.h>

int main() {
	int c;
	int count = 0;
	while ((c = getc(stdin)) != EOF) {
		if (c == 'A' || c == 'a' || c == 'E' || c == 'e' || c == 'I' || c == 'i' || c == 'O' || c == 'o' || c == 'U' || c == 'u') {
			printf("%c", c);
			if (c >= 'a') {
				printf("%c", c - 32);
			} else {
				printf("%c", c + 32);
			}
			count++;
		}
		if (c == '\n') {
			if (count == 0){
				printf("%s\n", "...");
			} else {
				putc('\n', stdout);
			}
			count = 0;
		}
	}
	return 0;
}
