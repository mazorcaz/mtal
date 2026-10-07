// ptrbuf.c

#include "ptrbuf.h"

#include <stdio.h>
#include <stdlib.h>

int ptrbuf_init(struct ptrbuf* buf)
{
	buf->len = 0;
	buf->sz = 16;
	buf->buf = malloc(buf->sz * sizeof(void*));
	if (!buf->buf) {
		printf("ptrbuf_init: malloc failed\n");
		return -1;
	}
	return 0;
}

void ptrbuf_free(struct ptrbuf* buf)
{
	free(buf->buf);
	buf->buf = NULL;
}

int ptrbuf_push(struct ptrbuf* buf, void* dat) {
	if (buf->len >= buf->sz) {
		do {
			buf->sz <<= 1;
		} while (buf->len >= buf->sz);

		void** newbuf = realloc(buf->buf, buf->sz * sizeof(void*));
		if (!newbuf) {
			printf("ptrbuf_push: malloc failed\n");
			return -1;
		}
		buf->buf = newbuf;
	}
	buf->buf[buf->len++] = dat;
	return 0;
}
		
