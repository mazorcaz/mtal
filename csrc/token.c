// token.c

#include <ctype.h>
#include <stdlib.h>

#include "token.h"
#include "bytebuf.h"

void token_free(struct token* token)
{
	switch (token->type) {
	case TOKEN_WORD:
		free(token->tokens.word.word);
		token->tokens.word.word = NULL;
		break;
	case TOKEN_NUM:
		break;
	default:
		return;
	}
	token->type = TOKEN_INVALID;
}

int token_parse_word(struct token* token, struct lexer* lexer)
{
	struct lexer new = *lexer;
	lexer_skipspace(&new);

	char c = lexer_peek(&new);

	if (!isalpha(c) && c != '_')
		return -1;

	token->type = TOKEN_WORD;
	struct token_word* word = &token->tokens.word;
	
	struct bytebuf buf;
	if (bytebuf_init(&buf))
		return -1;
	
	while (1) {
		c = lexer_peek(&new);
		if (!isalnum(c) && c != '_')
			break;
		lexer_next(&new);
		if (bytebuf_push(&buf, c))
			return -1;
	}

	word->word = buf.buf;
	*lexer = new;
	return 0;
}

int token_parse(struct token* token, struct lexer* lexer)
{
	if (token_parse_word(token, lexer)) {
		return -1;
	}
	
	return 0;
}
