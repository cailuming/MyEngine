#include "CTimer.h"

CTimer::CTimer()
{
	memset(this, 0, sizeof(*this));
	startTime = ::GetTickCount64();
}

CTimer::~CTimer()
{
}

CTimer *CTimer::timer=0;

CTimer *CTimer::create() {
	if (nullptr==timer) {
		timer = new CTimer();
	}
	
	return timer;
};

void CTimer::destroy() {

};

unsigned long CTimer::getTickCount() {
	curTimeShut = ::GetTickCount64();
	return curTimeShut-startTime;
};

unsigned long CTimer::getTickDelta() {
	 
	return timeDelta;
}

bool CTimer::canGo(int delta) {

	curTimeShut = ::GetTickCount64();
	timeDelta = curTimeShut - preTimeShut;
	if (timeDelta >= delta&&!isPause) {
	 
		preTimeShut = curTimeShut;
		return true;
	}

	return false;
};

void CTimer::pause() {
	isPause = true;
}

void CTimer::resume() {
	isPause = false;
};
