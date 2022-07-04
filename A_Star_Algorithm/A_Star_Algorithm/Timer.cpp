#include "Timer.h"

cTimer::cTimer()
{
	m_lastTime = SDL_GetTicks() / 1000.0f;
	m_currentTime = 0;
	m_deltaTime = 0;
}

void cTimer::Update()
{
	m_currentTime = SDL_GetTicks() / 1000.0f;
	m_deltaTime = m_currentTime - m_lastTime;
	m_lastTime = m_currentTime;
}
