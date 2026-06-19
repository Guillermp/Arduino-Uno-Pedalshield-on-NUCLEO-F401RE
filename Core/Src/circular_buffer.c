/*
 * circular_buffer.c
 *
 *  Created on: Jun 18, 2026
 *      Author: guiller
 */

#include "circular_buffer.h"

unsigned int circ_stored_samples(struct circ_bbuf_t *c){
	if (c->head >= c->tail) {
		return c->head - c->tail;
	}
	else {
		return c->head + c->maxlen - c->tail;
	}

}

int circ_bbuf_push(struct circ_bbuf_t *c, uint16_t data)
{
    int next;

    next = c->head + 1;  // next is where head will point to after this write.
    if (next >= c->maxlen)
        next = 0;

    if (next == c->tail)  // if the head + 1 == tail, circular buffer is full
        return -1;

    c->buffer[c->head] = data;  // Load data and then move
    c->head = next;             // head to next data offset.
    return 0;  // return success to indicate successful push.
}

int circ_bbuf_pop(struct circ_bbuf_t *c, uint16_t *data, unsigned int delay_samples)
{
    int next;

    if (c->head == c->tail || circ_stored_samples(c) < delay_samples)  // if the head == tail, we don't have any data
        return -1;

    next = c->tail + 1;  // next is where tail will point to after this read.
    if(next >= c->maxlen)
        next = 0;

    *data = c->buffer[c->tail];  // Read data and then move
    c->tail = next;              // tail to next offset.
    return 0;  // return success to indicate successful push.
}


