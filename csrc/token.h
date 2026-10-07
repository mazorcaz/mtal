// token.h

#ifndef MTAL_TOKEN_H
#define MTAL_TOKEN_H

#include <stdint.h>

#include "lexer.h"

#define TOKEN_INVALID 0
#define TOKEN_WORD 1
#define TOKEN_NUM 2
#define TOKEN_VAL 3

struct token_word {
	char* word; // owns
};

struct token_num {
	uint64_t num;
};

struct token {
	int type;
	union {
		struct token_word word;
		struct token_num num;
	} tokens;
};

void token_free(struct token* token);

// 0 on success
int token_parse_word(struct token* token, struct lexer* lexer);
int token_parse_num(struct token* token, struct lexer* lexer);
int token_parse(struct token* token, struct lexer* lexer);

#endif
