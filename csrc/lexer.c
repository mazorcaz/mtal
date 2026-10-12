// lexer.c

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "lexer.h"

int lexer_init(struct lexer* lexer, char* src)
{
	lexer->src = src;
	lexer->ptr = src;
	lexer->tokenptr = src;
	lexer->line = 1;
	lexer->mode = LEXER_START;

	if (!ptrbuf_init(&lexer->tokens)) return 0;
	
	lexer->token = malloc(sizeof(struct token));
	if (!lexer->token) return 0;

	return 1;
}

void lexer_free(struct lexer* lexer)
{
	for (int i=0; i<lexer->tokens.len; i++) {
		token_free(lexer->tokens.buf[i]);
		free(lexer->tokens.buf[i]);
	}
	ptrbuf_free(&lexer->tokens);
	free(lexer->token);
}

int lexer_next(struct lexer* lexer, int* iseof)
{
	char c = *lexer->ptr;
	if (c == 0) {
		*iseof = 1;
		return 1;
	}
	if (c == '\n') lexer->line++;
	*iseof = 0;

	switch (lexer->mode) {
	case LEXER_START:
		if (isspace(c)) {
			goto inc;
		} else if (isdigit(c)) {
			lexer->mode = LEXER_DIGIT;
			goto tokenstart;
		} else if (isalpha(c) || c == '_') {
			lexer->mode = LEXER_IDENT;
			goto tokenstart;
		} else { printf("Invalid character '%c'\n", c);
			return 0;
		}
	case LEXER_DIGIT:
		if (isdigit(c)) {
			goto inc;
		} else {
			lexer->token->type = TOKEN_NUM;
			goto tokenend;
		}
	case LEXER_IDENT:
		if (isalnum(c) || c == '_') {
			goto inc;
		} else {
			size_t toklen = lexer->ptr - lexer->tokenptr;
			char* str = malloc(toklen + 1);
			if (!str) return 0;
			memcpy(str, lexer->tokenptr, toklen);
			str[toklen] = 0;
			lexer->token->types.ident.string = str;
			lexer->token->type = TOKEN_IDENT;
			goto tokenend;
		}
	}
	return 0;

tokenend:
	// push token
	if (!ptrbuf_push(&lexer->tokens, lexer->token)) return 0;

	// make new token
	lexer->token = malloc(sizeof(struct token));
	if (!lexer->token) return 0;

	// prepare for next token
	lexer->mode = LEXER_START;
	return 1;

tokenstart:
	lexer->tokenptr = lexer->ptr;
inc:
	lexer->ptr++;
	return 1;
}
