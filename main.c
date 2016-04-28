#include <math.h>
#include "alphalight.h"
#include <pthread.h>
#include <stdio.h>

#define PI 3.1415926

double speed = 0.05;

void loop(AlphaLight flp, double t) {
	while (t < PI * 2) {
		flp -> high_time = HUSPF * (cos(t) + 1);
		flp -> low_time = USPF - flp -> high_time;
		t = t +	speed;
		usleep(10000);
	}
}

void main(int argc, char **argv) {
	setupAlphaLight();
	AlphaLight 	flp16 = alphaLight(16),
				flp20 = alphaLight(20),
				flp21 = alphaLight(21);
	enableAlpha(flp16);
	enableAlpha(flp20);
	enableAlpha(flp21);
	while(1) {
		loop(flp16, 0);
		loop(flp20, 0);
		loop(flp21, 0);
	}
}

