#ifndef SHINE_H
#define SHINE_H

#include <pthread.h>

#define USPF 14000
#define HUSPF (USPF / 2)

typedef struct alphalight {
	unsigned int 	high_time, low_time;
} alphalight;
typedef alphalight* AlphaLight;

void setupAlphaLight();

AlphaLight alphaLight(unsigned int port);
void unAlphaLight(AlphaLight alp);

void enableAlpha(AlphaLight alp);
void disableAlpha(AlphaLight alp);

#endif