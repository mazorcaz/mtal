// bytebuf.c

#include "bytebuf.h"

#include <stdio.h>
#include <stdlib.h>

int mt_bytebuf_init(struct mt_bytebuf* buf)
{
	buf->len = 0;
	buf->sz = 16;
	buf->buf = malloc(buf->sz);
	if (!buf->buf) {
		printf("mt_bytebuf_init: malloc failed\n");
		return -1;
	}
	return 0;
}

void mt_bytebuf_free(struct mt_bytebuf* buf)
{
	free(buf->buf);
	buf->buf = NULL;
}

int mt_bytebuf_pushbuf(struct mt_bytebuf* buf, uint8_t* src, size_t len)
{
	size_t newlen = buf->len + len;
	if (buf->sz < newlen) {
		do {
			buf->sz <<= 1;
		} while (buf->sz < newlen);

		uint8_t* newbuf = realloc(buf->buf, buf->sz);
		if (!newbuf) {
			printf("mt_bytebuf_pushbuf: malloc failed\n");
			return -1;
		}
		buf->buf = newbuf;
	}
	for (size_t i=0; i<len; i++) {
		buf->buf[buf->len++] = src[i];
	}
	return 0;
}
