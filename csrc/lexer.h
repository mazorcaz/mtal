// lexer.h

#ifndef MTAL_LEXER_H
#define MTAL_LEXER_H

#include <stddef.h>

#include "token.h"
#include "ptrbuf.h"
#include "bytebuf.h"

#define LEXER_START 1
#define LEXER_DIGIT 2
#define LEXER_NEG 3
#define LEXER_IDENT 4

struct lexer {
	char* src; // does not own
	char* ptr;
	char* tokenptr;
	size_t line;
	int mode;

	struct ptrbuf tokens; // owns
	struct token* token; // current token
};

// 1 on success
int lexer_init(struct lexer* lexer, char* src);
void lexer_free(struct lexer* lexer);

int lexer_next(struct lexer* lexer, int* iseof);

#endif
