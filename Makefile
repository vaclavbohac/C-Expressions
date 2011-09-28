all: c-expressions

BIN = c-expressions

CFLAGS += -lm -lcrypt -O2 -pipe -ansi -DONLINE_JUDGE

c-expressions: c-expressions.c
	gcc $(CFLAGS) -o $(BIN) $<

clean:
	-rm $(BIN)

test: c-expressions
	./$(BIN) < in.txt > out.txt
	diff -b expected.txt out.txt > result.diff
