// bytebuf.h

#ifndef MTAL_BYTEBUF_H
#define MTAL_BYTEBUF_H

#include <stdint.h>
#include <stddef.h>

struct mt_bytebuf {
	size_t sz; // actual byte size of buffer
	size_t len; // length of used portion
	uint8_t* buf;
};

int mt_bytebuf_init(struct mt_bytebuf* buf); // 0 if success
void mt_bytebuf_free(struct mt_bytebuf* buf);

int mt_bytebuf_pushbuf(struct mt_bytebuf* buf, uint8_t* src, size_t len);

#endif
