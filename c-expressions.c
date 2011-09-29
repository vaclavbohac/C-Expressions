/* Created by Vaclav Bohac <boh0012@vsb.cz>. */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 111

int values['z'][3];

void values_reset() {
	int i;
	for (i = 0; i < 'z' - 'a' + 1; i++) {
		values[i][0] = i + 1;
		values[i][1] = i + 1;
		values[i][2] = 0;
	}
}

int strip_whitespace(char *str) {
	char tmp[BUF_SIZE];
	int i, j, l;

	for (i = j = 0, l = strlen(str); i < l; i++) {
		if (!isspace(str[i])) {
			tmp[j++] = str[i];	
			tmp[j] = 0;
		}
	}

	strncpy(str, tmp, j);
	str[j] = 0;

	return j;
}

int main(void) {
	char input[BUF_SIZE], expr[BUF_SIZE];
	int i, j, length_input, length_expr,
	    operation, result;

	while (fgets(input, sizeof(input), stdin) != NULL) {

		/* Reset table of values */
		values_reset();

		/* Get rid of trailing newline. */
		length_input = strlen(input);
		if (input[length_input - 1] == '\n') {
			input[--length_input] = 0;
		}

		expr[0] = 0; /* Clear buffer.  */

		/* Copy input to expr. */
		strcpy(expr, input);

		/* Get rid of whitespace. */
		length_expr = strip_whitespace(expr);

		/** Get rid of prefixes. */
		for (i = 0; i < length_expr; i++) {
			if (isalpha(expr[i]) || isspace(expr[i])) {
				continue;
			}

			if (i + 2 < length_expr && expr[i] == expr[i + 1] && isalpha(expr[i + 2])) {
				j = expr[i + 2] - 'a';
				values[j][0] = values[j][1] += expr[i] == '+' ? 1 : -1;

				/* Replace prefix operators with spaces. */
				expr[i] = ' ';
				expr[i + 1] = ' ';
			}
		}

		/* Get rid of whitespace. */
		length_expr = strip_whitespace(expr);

		/* Get rid of postfixes. */
		for (i = 1; i < length_expr; i++) {
			if (isalpha(expr[i]) || isspace(expr[i])) {
				continue;
			}

			if (i + 1 < length_expr && expr[i] == expr[i + 1]) {
				values[expr[i - 1] - 'a'][1] += expr[i] == '+' ? 1 : -1;

				/* Replace postfix operators with spaces. */
				expr[i] = ' ';
				expr[i + 1] = ' ';
			}
		}

		/* Get rid of whitespace. */
		length_expr = strip_whitespace(expr);

		/* Solve expression. */
		for (i = result = operation = 0; i < length_expr; i++) {
			if (isalpha(expr[i])) {
				values[expr[i] - 'a'][2] = 1;
				result += values[expr[i] - 'a'][0] * (operation == 0 || operation == '+' ? 1 : -1);

			} else {
				operation = expr[i];
			}
		}


		printf("Expression: %s\n    value = %d\n", input, result);
		for (i = 0; i < 'z'; i++) {
			if (values[i][2]) {
				printf("    %c = %d\n", 'a' + i, values[i][1]);
			}
		}
	}

	return EXIT_SUCCESS;
}
