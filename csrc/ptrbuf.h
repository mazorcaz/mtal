// ptrbuf.h

#ifndef MTAL_PTRBUF_H
#define MTAL_PTRBUF_H

#include <stdint.h>
#include <stddef.h>

struct ptrbuf {
	size_t sz; // actual # of elements allocated in buffer
	size_t len; // how many elements used
	void** buf;
};

int ptrbuf_init(struct ptrbuf* buf); // 0 on success
void ptrbuf_free(struct ptrbuf* buf); // does NOT free entries

int ptrbuf_push(struct ptrbuf* buf, void* dat);

#endif
