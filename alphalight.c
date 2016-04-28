#include <stdlib.h>
#include <wiringPi.h>
#include "alphalight.h"

typedef enum LoopFlag {
	LOOP_S, LOOP_E
} LoopFlag;

typedef struct alphaparam {
	alphalight		al;
	unsigned int	pin;
	LoopFlag 		loopflag;
	pthread_t		id;
} alphaparam;
typedef alphaparam* AlphaParam;

/*
 *	Step1 初始化pin参数
 *	Step2 设置pin mode为输出
 *	Step3 初始化pin高电平
 *
*/
AlphaLight alphaLight(unsigned int pin) {
	AlphaParam 	app 				= (AlphaParam)malloc(sizeof(alphaparam));
	AlphaLight	alp					= (AlphaLight)app;
				alp -> high_time	= USPF;
				alp -> low_time		= 0;
				app -> loopflag		= LOOP_E;
				app -> pin			= pin;
	pinMode(pin, OUTPUT);
	digitalWrite(pin, HIGH);
	return alp;
}

/*
 *	Step1 停止该pin线程
 *	Step2 释放资源
 *
*/
void unAlphaLight(AlphaLight alp) {
	AlphaParam app = (AlphaParam)alp;
	
	disableAlpha(alp);
	free(app);
}
/*
 *	loop
 *		Step1 设置pin低电平
 *		Step2 延迟
 *		Step3 设置pin高电平
 *		Step4 延迟
 *	#loop
 *
*/
void *alphaLoop(void *param) {
	AlphaParam app = (AlphaParam)param;
	AlphaLight alp = (AlphaLight)param;
	
	while (app -> loopflag == LOOP_S) {
		digitalWrite(app -> pin, LOW);
		usleep(alp -> low_time);
		digitalWrite(app -> pin, HIGH);
		usleep(alp -> high_time);
	}
}

/*
 *	Step1 确认该pin没有其他线程在运行
 *	Step2 设置启动alphaLoop线程标志
 *	Step3 启动新alphaLoop线程
 *
*/
void enableAlpha(AlphaLight alp) {
	AlphaParam app	= (AlphaParam)alp;
	
	disableAlpha(alp);
	app -> loopflag	= LOOP_S;
	pthread_create(&(app -> id), NULL, alphaLoop, app);
}

/*
 *	Step1 设置停止alphaLoop线程标志
 *	Step2 确认该pin线程已结束
 *
*/
void disableAlpha(AlphaLight alp) {
	AlphaParam app = (AlphaParam)alp;
	
	app -> loopflag = LOOP_E;
	pthread_join(app -> id, NULL);
}

//初始化设置
void setupAlphaLight() {
	wiringPiSetupGpio();
}
