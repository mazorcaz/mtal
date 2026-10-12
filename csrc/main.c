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
		if (!lexer_next(&lexer, &eof)) goto exit;
		if (eof) break;
	}
	printf("main: escaped loop, parsed %d\n", lexer.tokens.len);

	for (int i=0; i<lexer.tokens.len; i++) {
		struct token* token = lexer.tokens.buf[i];
		printf("%i\n", token->type);
		token_free(token);
		free(token);
	}

exit:
	lexer_free(&lexer);
	bytebuf_free(&src);
	return 0;
}
