#pragma once
#include"Macro.h"
class CTimer
{
private:
	CTimer();
	~CTimer();
public:
	static CTimer *timer;
	static CTimer *create();
	static void destroy();

public:
	unsigned long getTickCount();
	unsigned long getTickDelta();
public:
	unsigned long curTimeShut;
	unsigned long preTimeShut;
	unsigned long timeDelta;
	unsigned long startTime;
	bool isPause;
public:
	void pause();
	void resume();
public:
	bool canGo(int delta);
};

