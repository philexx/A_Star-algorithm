#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>
#include "Singleton.h"

class cTimer : public tSingleton<cTimer>
{
private:
	float m_lastTime;
	float m_currentTime;
	float m_deltaTime;
public:
	cTimer();
	void Update();
public:
	float DeltaTimer() { return m_deltaTime; }
};
#endif // !TIMER_H
