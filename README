Liblex
------

This is a simple library to make writing a lexer easier. It provides an
interface to easily read and unread characters from a file descriptor.

To build liblex, simply make:

	$ make

An example lexer is provided and can be found in `example.c`. It simply 
reads from `stdin` and will print any series of numbers or lower-case
words it finds. You can build the example with:

	$ make example

Read `example.c` for more information.


Why not use `lex`?
------------------

There is really not a strong reason not to use `lex`. It will probably save 
you a fair amount of debugging time, and your resulting lexer will probably
be faster.

However that being said, `liblex` has proven to be a simple and efficient 
library; it does the job in a few lines of code. `lex` is notorious
for creating large programs that span thousands of lines. The example
lexer given here is less than 100 lines. 
