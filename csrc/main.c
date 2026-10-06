#include <stdio.h>
#include <stdlib.h>

#include "bytebuf.h"
#include "ptrbuf.h"

int main(int argc, char** argv) {
	struct mt_ptrbuf lines;
	if (mt_ptrbuf_init(&lines)) {
		printf("main: mt_ptrbuf_init failed\n");
		return -1;
	}

	char charbuf[256];
	struct mt_bytebuf* line;
	while (1) {
		if (fgets(charbuf, sizeof(charbuf), stdin) == NULL) {
			break;
		}

		line = malloc(sizeof(struct mt_bytebuf));
		if (!line) {
			printf("main: malloc failed\n");
			return -1;
		}
		if (mt_bytebuf_init(line)) {
			printf("main: mt_bytebuf_init failed\n");
			return -1;
		}

		do {
			
		}

	}
	return 0;
}
