/*
 * circular_buffer.h
 *
 *  Created on: Jun 18, 2026
 *      Author: guiller
 */

#ifndef INC_CIRCULAR_BUFFER_H_
#define INC_CIRCULAR_BUFFER_H_

#include "main.h"
#include <stdint.h>
#include <stdlib.h>

struct circ_bbuf_t {
    uint16_t * const buffer;
    int head;
    int tail;
    const int maxlen;
};

unsigned int circ_stored_samples(struct circ_bbuf_t *c);

int circ_bbuf_push(struct circ_bbuf_t *c, uint16_t data);

int circ_bbuf_pop(struct circ_bbuf_t *c, uint16_t *data);

#endif /* INC_CIRCULAR_BUFFER_H_ */
