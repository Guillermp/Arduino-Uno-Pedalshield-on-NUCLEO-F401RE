/*
 * delay.h
 *
 *  Created on: Jun 20, 2026
 *      Author: guiller
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#include "circular_buffer.h"

struct DelayConfig {
	unsigned int Fs;
	unsigned int delay_samples;
	float feedbackGain;
	float wetness; // wet to dry ratio (0-1)
	uint16_t midpoint; // value of the adc for the idel signal

};

float clampf(float value, float min, float max);

void delayInit(struct DelayConfig* config, double delay_ms);

uint16_t delayProcessor(struct circ_bbuf_t *circularBufferPtr, uint16_t input, uint16_t* feedback, struct DelayConfig* config);

#endif /* INC_DELAY_H_ */
