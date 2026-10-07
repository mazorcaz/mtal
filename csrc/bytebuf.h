// bytebuf.h

#ifndef MTAL_BYTEBUF_H
#define MTAL_BYTEBUF_H

#include <stdint.h>
#include <stddef.h>

struct bytebuf {
	size_t sz; // actual byte size of buffer
	size_t len; // length of used portion
	uint8_t* buf;
};

int bytebuf_init(struct bytebuf* buf); // 0 if success
void bytebuf_free(struct bytebuf* buf);

int bytebuf_pushbuf(struct bytebuf* buf, uint8_t* src, size_t len);
int bytebuf_push(struct bytebuf* buf, uint8_t src);

#endif
