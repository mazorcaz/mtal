// token.c

#include <ctype.h>
#include <stdlib.h>

#include "token.h"
#include "bytebuf.h"

void token_free(struct token* token)
{
	switch (token->type) {
	case TOKEN_IDENT:
		free(token->types.ident.string);
		token->types.ident.string = NULL;
		break;
	case TOKEN_NUM:
		break;
	default:
		return;
	}
	token->type = TOKEN_INVALID;
}
