#ifndef __LIBLEX_H__
#define __LIBLEX_H__

typedef struct Lex Lex;
typedef void (*Lerror)(Lex *, char *);

struct Lex {  
	char *tokstart;	/* Start of current token. */
	int toklen;	/* Length of current token. */
	char *buf;	/* Input stream (supplied by user). */
	int buflen;	/* Length of meaningful data in buf. */
	int size;	/* Size of Lex->buf in memory. */
	int lineno; 	/* Current line number. */
	Lerror errfunc;	/* Function called on fatal error. */
};


void Linit(Lex *, char *, int, Lerror);	/* Creates a new Lexer. */
char Linput(Lex *);		/* Next char in input stream. */
char Lpeek(Lex *);		/* Next char without consuming. */
void Lunput(Lex *);		/* Places a char back on the input stream. */
void Ldiscard(Lex *);		/* Throws away current token in buffer */
void Laccept(Lex *, char *);	/* Linput() until char not in string. */
void Lignore(Lex *, char *);	/* Ldiscard() until char not in string. */
int Llineno(Lex *);		/* The current line number. */
int Ltoklen(Lex *);		/* Length of current token in buffer */
char *Ltok(Lex *, char *);	/* Fills buffer with copy of token */

#endif