#include "Framework.h"
#include <iostream>

void cFramerwork::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL couldn't initialize" << std::endl;
	}

	m_window = SDL_CreateWindow("A* Algorithm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, 0);
	if (!m_window)
	{
		std::cout << "SDL couldn't create window.. SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	m_Renderer = SDL_CreateRenderer(m_window, -1, 0);
	if (!m_Renderer)
	{
		std::cout << "SDL couldn't create renderer.. SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	m_keyboard = SDL_GetKeyboardState(nullptr);

	gameRunning = true;
}

void cFramerwork::Update()
{
	cTimer::Get()->Update();
	SDL_PumpEvents();
}

void cFramerwork::Render() const
{
	SDL_RenderPresent(m_Renderer);
}

void cFramerwork::Clear() const
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_Renderer);
}

void cFramerwork::Terminate()
{
	if (m_window)
	{
		m_window = nullptr;
	}
	if (m_Renderer)
	{
		m_Renderer = nullptr;
	}
	gameRunning = false;
}

bool cFramerwork::Keyboard(int id) const
{
	return m_keyboard[id] ? true : false;
}

