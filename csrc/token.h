// token.h

#ifndef MTAL_TOKEN_H
#define MTAL_TOKEN_H

#include <stdint.h>

#include "lexer.h"

#define TOKEN_INVALID 0
#define TOKEN_IDENT 1
#define TOKEN_NUM 2
#define TOKEN_VAL 3

struct token_ident {
	char* string; // owns
};

struct token_num {
	uint64_t num;
};

struct token {
	int type;
	union {
		struct token_ident ident;
		struct token_num num;
	} types;
};

void token_free(struct token* token);

#endif
