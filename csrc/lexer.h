// lexer.h

#ifndef MTAL_LEXER_H
#define MTAL_LEXER_H

#include <stddef.h>

struct lexer {
	char* src; // does not own
	char* ptr;
	size_t line;
};

void lexer_init(struct lexer* lexer, char* src);

char lexer_peek(struct lexer* lexer);
char lexer_next(struct lexer* lexer);
void lexer_skipspace(struct lexer* lexer);

#endif
