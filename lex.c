/*
 * The MIT License (MIT)
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
 
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "lex.h"

static void Lfill(Lex *);
static void Lshift(Lex *);

void
Linit(Lex * l, int fd, char * buf, int size, Lerror errfunc)
{
	l->buf = l->tokstart = buf;
	l->buflen = l->toklen = 0;
	l->size = size;
	l->lineno = 1;
	l->fd = fd;
	l->errfunc = errfunc;	
}

static void
Lfill(Lex * l)
{
	int rd, i;
	rd = read(l->fd, (l->buf + l->buflen), (l->size - l->buflen));
	if (rd < 0) {
		l->errfunc(l, "Read error");
		return;
	}
	else if (rd == 0) {
		for (i = l->buflen; i < l->size; i++)
			l->buf[i] = EOF;
		l->buflen = l->size;
	}
	else {
		l->buflen += rd;
	}
}

static void
Lshift(Lex * l)
{
	int i, off;
	off = l->tokstart - l->buf;
	if (off == 0)
		return;
	for (i = 0; i < l->toklen; i++)
		l->buf[i] = l->tokstart[i];
	l->tokstart = l->buf;
	l->buflen -= off;
}

char 
Linput(Lex * l)
{
	char c;	
	int off;
	if (l->toklen == l->size) {
		l->errfunc(l, "Token length exceeds length of buffer");
		return EOF;
	}
	off = l->tokstart - l->buf;
	if ((l->toklen + off) == l->buflen) {
		Lshift(l);
		Lfill(l);
	}
	c = *(l->tokstart + l->toklen++);
	if (c == '\n')
		l->lineno++;
	return c;
}

void
Lunput(Lex * l)
{
	if (l->toklen <= 0) {
		l->toklen = 0;
		return;
	}	
	l->toklen--;
	if (*(l->tokstart + l->toklen) == '\n')
		l->lineno--;
}

char
Lpeek(Lex * l)
{
	char c;
	c = Linput(l);
	Lunput(l);
	return c;
}

void
Ldiscard(Lex * l)
{
	l->tokstart = l->tokstart + l->toklen;
	l->toklen = 0;
}

char *
Ltok(Lex * l, char * s)
{
	int i;
	for (i = 0; i < l->toklen; i++)
		s[i] = l->tokstart[i];
	s[l->toklen] = '\0';
	Ldiscard(l);
	return s;
}

void
Laccept(Lex * l, char * s)
{
	char c;
	c = Lpeek(l);
	while (strchr(s, c) != NULL) {
		Linput(l);
		c = Lpeek(l);
	}
}

void
Lignore(Lex * l, char * s)
{
	char c;
	c = Lpeek(l);
	while (strchr(s, c) != NULL) {
		Linput(l);
		Ldiscard(l);
		c = Lpeek(l);
	}
}

int
Ltoklen(Lex * l)
{
	return l->toklen;
}

int
Llineno(Lex * l)
{
	return l->lineno;
}
