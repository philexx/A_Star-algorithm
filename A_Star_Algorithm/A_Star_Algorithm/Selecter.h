#pragma once

#include "Sprite.h"
#include "Framework.h"
#include "Timer.h"

class CSelecter
{
public:
	CSelecter();
	~CSelecter();
private:
	vec2 m_Position;
	cSprite* m_Sprite;

public:
	void Render() const;
	void SetPosition(const vec2& pos);
public:
	SDL_Rect GetPosition() const { return m_Sprite->GetRect(); }
};