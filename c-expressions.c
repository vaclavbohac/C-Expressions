#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define toInt(i) (i - 'a' + 1)

#define BUF_SIZE 111
#define VAL_SIZE 'z' - 'a' + 1

int values[VAL_SIZE][2];

void values_reset() {
	int i;
	for (i = 0; i < VAL_SIZE; i++) {
		values[i][0] = i + 1;
		values[i][1] = 0;
	}
}

int main(void) {
	char o, c, expr[BUF_SIZE];
	int sum, i, l, j;
	while (fgets(expr, sizeof(expr), stdin) != NULL) {
		l = strlen(expr) - 1;	
		if (expr[l] == '\n') {
			expr[l] == 0;
		}

		values_reset();
		for (o = '+', sum = i = 0; i < l; i++) {
			c = expr[i];
			if (c == ' ') {
				continue;
			}

			if (c == '+' || c == '-') {
				o = c;
				continue;
			}

			values[toInt(c) - 1][1] = 1;
			if (sum == 0) {
				sum = values[toInt(c) - 1][0];
			} else {
				sum += (o == '+' ? 1 : -1) * values[toInt(c) - 1][0];
			}
		}

		printf("Expression: %s\tvalue = %d\n", expr, sum);
		for (j = 0; j <= VAL_SIZE; j++) {
			if (values[j][1])
				printf("\t%c = %d\n", j + 'a', values[j][0]);
		}
	}
	return EXIT_SUCCESS;
}
