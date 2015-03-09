/*
 *  The MIT License (MIT)
 * 
 * Copyright (c) 2015 John Murphy
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 */
 
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
	int fd;		/* File descriptor to read from */
	Lerror errfunc;	/* Function called on fatal error. */
};

void Linit(Lex *, int, char *, int, Lerror);	/* Creates a new Lexer. */
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