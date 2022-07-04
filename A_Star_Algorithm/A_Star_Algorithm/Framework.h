#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#define SCREENWIDTH 810
#define SCREENHEIGHT 600


#include <iostream>
#include "Timer.h"
#include "Vector2D.h"
class cFramerwork : public tSingleton<cFramerwork>
{
private:
	int m_width;
	int m_Height;
	bool gameRunning;
private:
	SDL_Window* m_window;
	SDL_Renderer* m_Renderer;
	const Uint8* m_keyboard;
public:
	void Init();
	void Update();
	void Render();
	void Clear();
	void Terminate();
	bool Keyboard(int id);

public:
	SDL_Renderer* GetRenderer();
};


#endif // !FRAMEWORK_H
