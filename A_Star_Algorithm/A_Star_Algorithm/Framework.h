#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#define SCREENWIDTH 810
#define SCREENHEIGHT 600

#include "Timer.h"

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
	void Render() const;
	void Clear() const;
	void Terminate();
	bool Keyboard(int id) const;

public:
	inline SDL_Renderer* GetRenderer() const {return m_Renderer;}
};


#endif // !FRAMEWORK_H
