// ptrbuf.c

#include "ptrbuf.h"

#include <stdio.h>
#include <stdlib.h>

int mt_ptrbuf_init(struct mt_ptrbuf* buf)
{
	buf->len = 0;
	buf->sz = 16;
	buf->buf = malloc(buf->sz * sizeof(void*));
	if (!buf->buf) {
		printf("mt_ptrbuf_init: malloc failed\n");
		return -1;
	}
	return 0;
}

void mt_ptrbuf_free(struct mt_ptrbuf* buf)
{
	free(buf->buf);
	buf->buf = NULL;
}

int mt_ptrbuf_append(struct mt_ptrbuf* buf, void* dat) {
	if (buf->len >= buf->sz) {
		do {
			buf->sz <<= 1;
		} while (buf->len >= buf->sz);

		void** newbuf = realloc(buf->buf, buf->sz * sizeof(void*));
		if (!newbuf) {
			printf("mt_ptrbuf_appned: malloc failed\n");
			return -1;
		}
		buf->buf = newbuf;
	}
	buf->buf[buf->len++] = dat;
	return 0;
}
		
