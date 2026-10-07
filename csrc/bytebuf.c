// bytebuf.c

#include "bytebuf.h"

#include <stdio.h>
#include <stdlib.h>

int bytebuf_init(struct bytebuf* buf)
{
	buf->len = 0;
	buf->sz = 16;
	buf->buf = malloc(buf->sz);
	if (!buf->buf) {
		printf("bytebuf_init: malloc failed\n");
		return -1;
	}
	return 0;
}

void bytebuf_free(struct bytebuf* buf)
{
	free(buf->buf);
	buf->buf = NULL;
}

int bytebuf_pushbuf(struct bytebuf* buf, uint8_t* src, size_t len)
{
	size_t newlen = buf->len + len;
	if (buf->sz < newlen) {
		do {
			buf->sz <<= 1;
		} while (buf->sz < newlen);

		uint8_t* newbuf = realloc(buf->buf, buf->sz);
		if (!newbuf) {
			printf("bytebuf_pushbuf: malloc failed\n");
			return -1;
		}
		buf->buf = newbuf;
	}
	for (size_t i=0; i<len; i++) {
		buf->buf[buf->len++] = src[i];
	}
	return 0;
}

int bytebuf_push(struct bytebuf* buf, uint8_t src)
{
	if (buf->len >= buf->sz) {
		do {
			buf->sz <<= 1;
		} while (buf->len >= buf->sz);

		uint8_t* newbuf = realloc(buf->buf, buf->sz);
		if (!newbuf) {
			printf("bytebuf_push: malloc failed\n");
			return -1;
		}
		buf->buf = newbuf;
	}
	buf->buf[buf->len++] = src;
	return 0;
}
