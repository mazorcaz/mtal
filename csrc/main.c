#include <stdio.h>
#include <stdlib.h>

#include "bytebuf.h"
#include "ptrbuf.h"
#include "lexer.h"
#include "token.h"

int main(int argc, char** argv) {
	struct bytebuf src;
	if (bytebuf_init(&src)) return -1;

	while (1) {
		int c;
		if ((c = getchar()) == EOF) break;
		if (bytebuf_push(&src, c)) return -1;
	}

	struct lexer lexer;
	lexer_init(&lexer, src.buf);

	struct ptrbuf tokens;
	if (ptrbuf_init(&tokens)) return -1;

	while (1) {
		struct token* token = malloc(sizeof(struct token));
		if (!token) {
			printf("main: malloc failed\n");
			return -1;
		}
		if (token_parse(token, &lexer)) {
			free(token);
			break;
		}
		if (ptrbuf_push(&tokens, token)) return -1;
	}
	printf("main: escaped loop, parsed %d\n", tokens.len);

	for (int i=0; i<tokens.len; i++) {
		struct token* token = tokens.buf[i];
		printf("%s\n", token->tokens.word.word);
		token_free(token);
		free(token);
	}

	ptrbuf_free(&tokens);
	bytebuf_free(&src);
	return 0;
}
