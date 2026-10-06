// ptrbuf.h

#ifndef MTAL_PTRBUF_H
#define MTAL_PTRBUF_H

#include <stdint.h>
#include <stddef.h>

struct mt_ptrbuf {
	size_t sz; // actual # of elements allocated in buffer
	size_t len; // how many elements used
	void** buf;
};

int mt_ptrbuf_init(struct mt_ptrbuf* buf); // 0 on success
void mt_ptrbuf_free(struct mt_ptrbuf* buf); // does NOT free entries

int mt_ptrbuf_append(struct mt_ptrbuf* buf, void* dat);

#endif
