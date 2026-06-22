/*
 * delay.c
 *
 *  Created on: Jun 20, 2026
 *      Author: guiller
 */

#include "delay.h"

float clampf(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void delayInit(struct DelayConfig* config, double delay_ms) {

    config->delay_samples = (unsigned int)(config->Fs * delay_ms / 1000);
    config->wetness = clampf(config->wetness, 0.0f, 1.0f);
    config->feedbackGain = clampf(config->feedbackGain, 0.0f, 0.8f);

}


uint16_t delayProcessor(struct circ_bbuf_t *circularBufferPtr, uint16_t input, uint16_t* feedback, struct DelayConfig* config) {

	uint16_t delayed_sample = 0;
	// Save the sample in the circular buffer
	circ_bbuf_push(circularBufferPtr, (input + config->feedbackGain*(*feedback))/2);
	// Get the delayed sample
	if (circ_stored_samples(circularBufferPtr) >= config->delay_samples) {
		circ_bbuf_pop(circularBufferPtr, &delayed_sample);
		*feedback = delayed_sample;
	}

	// Calculate the mixed signal
	uint16_t mixed = ((1-config->wetness)*input + config->wetness*delayed_sample);

	return mixed;
}

/*
uint16_t delayProcessor(struct circ_bbuf_t *circularBufferPtr, uint16_t input, uint16_t* feedback, struct DelayConfig* config) {

    uint16_t delayed_sample = input;
    int32_t mid = config->midpoint;
    int32_t in_s  = (int32_t)input    - mid;
    int32_t fb_s  = (int32_t)(*feedback) - mid;

    circ_bbuf_push(circularBufferPtr, (uint16_t)(mid + in_s + (int32_t)(config->feedbackGain * fb_s)));

    if (circ_stored_samples(circularBufferPtr) >= config->delay_samples) {
        circ_bbuf_pop(circularBufferPtr, &delayed_sample);
        *feedback = delayed_sample;
    }

    int32_t delayed_s = (int32_t)delayed_sample - mid;
    uint16_t mixed = (uint16_t)(mid + (int32_t)((1.0f - config->wetness) * in_s + config->wetness * delayed_s));

    return mixed;
}
*/

