CC	= cc
CFLAGS	= -Wall

default: liblex.a

liblex.a: lex.o
	ar rcs $@ $<

lex.o: lex.h lex.c

example: liblex.a example.o
	$(CC) -L. -llex example.o -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o example liblex.a




