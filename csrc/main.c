#include <stdio.h>
#include <stdlib.h>

#include "bytebuf.h"
#include "ptrbuf.h"
#include "lexer.h"
#include "token.h"

int main(int argc, char** argv) {
	struct bytebuf src;
	if (!bytebuf_init(&src)) return -1;

	while (1) {
		int c;
		if ((c = getchar()) == EOF) break;
		if (!bytebuf_push(&src, c)) return -1;
	}

	struct lexer lexer;
	if (!lexer_init(&lexer, src.buf)) return -1;

	while (1) {
		int eof;
		if (!lexer_next(&lexer, &eof)) goto exit_lexer;
		if (eof) break;
	}
	printf("main: escaped loop, parsed %d\n", lexer.tokens.len);

	for (int i=0; i<lexer.tokens.len; i++) {
		struct token* token = lexer.tokens.buf[i];
		if (token->type == TOKEN_IDENT) {
			printf("IDENT '%s'\n", token->types.ident.string);
		} else if (token->type == TOKEN_NUM) {
			printf("NUM %i\n", token->types.num.num);
		} else {
			printf("UNKNOWN (%i)\n", token->type);
		}
	}

exit_lexer:
	lexer_free(&lexer);
	bytebuf_free(&src);
	return 0;
}
