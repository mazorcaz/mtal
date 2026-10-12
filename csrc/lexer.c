// lexer.c

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

int lexer_init(struct lexer* lexer, char* src)
{
	lexer->src = src;
	lexer->ptr = src;
	lexer->line = 1;
	lexer->mode = LEXER_START;

	if (!ptrbuf_init(&lexer->tokens)) return 0;
	if (!bytebuf_init(&lexer->string)) return 0;
	
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
	bytebuf_free(&lexer->string);
	free(lexer->token);
}

int lexer_next(struct lexer* lexer, int* iseof)
{
	char c = *lexer->ptr;
	if (c == 0) {
		*iseof = 1;
		return 1;
	}
	if (c == '\n')
		lexer->line++;
	*iseof = 0;
	if (!bytebuf_push(&lexer->string, c));

	switch (lexer->mode) {
	case LEXER_START:
		if (isspace(c)) {
			goto inc;
		} else if (isdigit(c)) {
			lexer->mode = LEXER_DIGIT;
			goto inc;
		} else if (isalpha(c) || c == '_') {
			lexer->mode = LEXER_IDENT;
			goto inc;
		} else { printf("Invalid character '%c'\n", c);
			return 0;
		}
	case LEXER_DIGIT:
		if (isdigit(c)) {
			goto inc;
		} else {
			lexer->token->type = TOKEN_NUM;
			goto change;
		}
	case LEXER_IDENT:
		if (isalnum(c) || c == '_') {
			goto inc;
		} else {
			lexer->token->type = TOKEN_IDENT;
			lexer->token->types.ident.string = lexer->string.buf;
			if (!bytebuf_init(&lexer->string)) return 0;
			goto change;
		}
	}
	return 0;

change:
	lexer->mode = LEXER_START;
	if (!ptrbuf_push(&lexer->tokens, lexer->token)) return 0;
	lexer->token = malloc(sizeof(struct token));
	if (!lexer->token) return 0;
	lexer->string.len = 0;
	return 1;
inc:
	lexer->ptr++;
	return 1;
}
