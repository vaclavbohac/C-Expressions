/* Created by Vaclav Bohac <boh0012@vsb.cz>. */

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
	int sum, i, l, j, k;
	while (fgets(expr, sizeof(expr), stdin) != NULL) {
		l = strlen(expr) - 1;	
		if (expr[l] == '\n') {
			expr[l] == 0;
		}

		values_reset();
		for (o = sum = i = 0; i < l; i++) {
			c = expr[i];
			if (c == ' ') { /* Whitespace */
				continue;

			} else if (c == '+' || c == '-') { /* Operator */

				/* Incrementation and decrementation. */
				if (i + 1 <  l && expr[i + 1] == c) {

					/* Postfix */
					for (k = 1; i - k >= 0; k++) {
						if (expr[i - k] == ' ') {
							continue;	
						}

						if (expr[i - k] >= 'a' && expr[i - k] <= 'z') {
							values[toInt(expr[i - k]) - 1][0] += (c == '+' ? 1 : -1);
						}

						break;
					}

					/* Prefix */
					for (k = 2; i + k < l; k++) {
						if (expr[i + k] == ' ') {
							continue;	
						}

						if (expr[i + k] >= 'a' && expr[i + k] <= 'z') {
							values[toInt(expr[i + k]) - 1][0] += (c == '+' ? 1 : -1);
						}

						break;
					}
				}

				/* Forgotten operation fix (eg. a+--b) */
				if (i - 2 > 0 && expr[i - 1] == c) {
					for (k = 2; (i - k) > 0; k++) {
						if (expr[i - k] == ' ') {
							continue;
						}

						if (expr[i - k] == '+' || expr[i - k] == '-') {
							o = expr[i - k];
						} else {
							o = c;
						}

						break;
					}
				} else {
					o = c;
				}

			} else { /* Value */
				values[toInt(c) - 1][1] = 1;
				sum += (o == 0 || o == '+' ? 1 : -1) * values[toInt(c) - 1][0];
			}
		}

		printf("Expression: %s    value = %d\n", expr, sum);
		for (j = 0; j <= VAL_SIZE; j++) {
			if (values[j][1]) {
				printf("    %c = %d\n", j + 'a', values[j][0]);
			}
		}
	}
	return EXIT_SUCCESS;
}
