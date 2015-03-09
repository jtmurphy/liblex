/* 
 * This is the example lexer. It's unlicensed.
 * You can compile this by making with: `make example'
 * 
 * The example looks for string of digits or lower case characters and 
 * identifies them if found. It ignores strings starting with a `#' and
 * ending with a newline. For example:
 *
 * 	$ ./example
 * 	hello world 123 #comment
 * 	 -> word: "hello"
 *	 -> word: "world"
 * 	 -> number: 123
 *
 * NOTE: The lexer provided has a buffer 10 characters long.  This is a 
 * extremelly silly value and a proper value should be something on the order
 * of a page (4K). The reason it's so small is to show what happens if you 
 * try to fill this buffer with a token that is too long. You can try this
 * yourself by providing a token longer than 10 characters.
 */

#include "lex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error(Lex * l, char * msg)
{
	fprintf(stderr, "Error:%d: %s\n", Llineno(l), msg);
	exit(1);
}

void emit(Lex * l, char * type)
{
	char s[11];
	Ltok(l, s);
	fprintf(stderr, " -> %s: \"%s\"\n", type, s);
}


/* Lexer state machine */

typedef void * (*Lstate)(Lex *);

#define DIGIT	"0123456789"
#define ALPHA	"abcdefghijklmnopqrstuvwxyz"
#define WHITE	" \t\r\n"

void * start(Lex *);
void * number(Lex *);
void * word(Lex *); 
void * comment(Lex *);

void *
start(Lex * l)
{
	char c;
	Lignore(l, WHITE);
	c = Linput(l);
	if (c == EOF)
		return NULL;
	else if (c == '#')
		return comment;
	else if (strchr(DIGIT, c) != NULL)
		return number;
	else if (strchr(ALPHA, c) != NULL)
		return word;
	else 
		error(l, "Unknown character.");
	return NULL;
}

void *
number(Lex * l)
{
	Laccept(l, DIGIT);
	emit(l, "number");
	return start;
}

void *
word(Lex * l)
{
	Laccept(l, ALPHA);
	emit(l, "word");
	return start;
}

void *
comment(Lex * l)
{
	while (Linput(l) != '\n')
		Ldiscard(l);
	Ldiscard(l);
	return start;
}

int
main(int argc, char * argv[])
{
	char buf[10]; /* silly size: try 4096 */
	Lex lexer;
	Linit(&lexer, 0, buf, 10, error);
	
	Lstate state;
	state = start;
	while (state != NULL)
		state = state(&lexer);
}
