// lexer.c

#include <ctype.h>

#include "lexer.h"

void lexer_init(struct lexer* lexer, char* src)
{
	lexer->src = src;
	lexer->ptr = src;
	lexer->line = 1;
}

char lexer_peek(struct lexer* lexer)
{
	return *lexer->ptr;
}

char lexer_next(struct lexer* lexer)
{
	char c = *lexer->ptr;
	if (c == 0) return 0;
	if (c == '\n') lexer->line++;
	lexer->ptr++;
	return c;
}

void lexer_skipspace(struct lexer* lexer)
{
	while (isspace(lexer_peek(lexer))) {
		lexer_next(lexer);
	}
}
