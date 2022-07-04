#include "Selecter.h"

CSelecter::CSelecter()
{
	m_Sprite = new cSprite;
	m_Position.x = 0;
	m_Position.y = 0;
}

CSelecter::~CSelecter()
{
	if (m_Sprite)
	{
		delete m_Sprite;
		m_Sprite = nullptr;
	}
}

void CSelecter::Render()
{
	m_Sprite->SetPos(m_Position);
	m_Sprite->DrawRectOutline();
}

void CSelecter::SetPosition(const vec2& pos)
{
	m_Position = pos;
}

