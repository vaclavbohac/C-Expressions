all: c-expressions

BIN = c-expressions

CFLAGS += -lm -O2 -pipe -ansi -DONLINE_JUDGE

c-expressions: c-expressions.c
	gcc $(CFLAGS) -o $(BIN) $<

clean:
	-rm $(BIN)

test: c-expressions
	./$(BIN) < in.txt > out.txt
	diff expected.txt out.txt > result.diff
