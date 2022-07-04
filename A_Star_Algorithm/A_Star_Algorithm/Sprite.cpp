#include "Sprite.h"

cSprite::cSprite()
{
	m_Renderer = cFramerwork::Get()->GetRenderer();
	m_texture = nullptr;
	m_NumFrames = 0;
	m_FrameWidth = 0;
	Red = 0;
	Green = 0;
	Blue = 139;
	Alpha = 0;
	m_RectWith = 13;
	m_RectHeight = 13;
}

cSprite::~cSprite()
{
	if (m_Renderer != nullptr)
	{
		m_Renderer = nullptr;
	}
}

void cSprite::Load(const std::string& filename)
{
	SDL_Surface* surf = SDL_LoadBMP(filename.c_str());
	if (!surf)
	{
		std::cout << "Failed to laod Image: " << filename << std::endl;
	}
	else
	{
		SDL_CreateTextureFromSurface(m_Renderer, surf);

		m_Rect.w = surf->w;
		m_Rect.h = surf->h;

		SDL_FreeSurface(surf);
	}
}//Load NOT animated Sprites

void cSprite::Load(const std::string& filename, int frameWidth, int frameHeight)
{
	SDL_Surface* temp = SDL_LoadBMP(filename.c_str());
	if (!temp)
	{
		std::cout << "Failed to laod Image: " << filename << std::endl;
		//quit game
	}
	else
	{
		SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 84, 84, 84));
		m_texture = SDL_CreateTextureFromSurface(m_Renderer, temp);

		m_Rect.w = frameWidth;
		m_Rect.h = frameHeight;

		m_FrameWidth = frameWidth;
		m_sourceRect.w = frameWidth;
		m_sourceRect.h = frameHeight;

		m_NumFrames = temp->w / m_FrameWidth;
		SDL_FreeSurface(temp);
	}
}
void cSprite::Render()
{
	SDL_RenderCopy(m_Renderer, m_texture, NULL, &m_Rect);
}//Load Animated Sprites


void cSprite::Render(float currentFrame)
{
	int column = static_cast<int>(currentFrame) % m_NumFrames;

	m_sourceRect.x = column * m_FrameWidth;

	SDL_RenderCopy(m_Renderer, m_texture, &m_sourceRect, &m_Rect);
}//Render Animated Sprites

void cSprite::RenderLine(int x1, int x2, int x3, int x4)
{
	SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(m_Renderer, x1, x2, x3, x4);
}//Draw Line

void cSprite::SetPos(const vec2& Position)
{
	m_Rect.x = static_cast<int>(Position.x);
	m_Rect.y = static_cast<int>(Position.y);
}//Set Sprite Position

void cSprite::DrawRect()
{
	m_Rect.w = m_RectWith;
	m_Rect.h = m_RectHeight;
	SDL_SetRenderDrawColor(m_Renderer, Red, Green, Blue, Alpha);
	SDL_RenderFillRect(m_Renderer, &m_Rect);
}

void cSprite::DrawRectOutline()
{
	m_Rect.w = m_RectWith;
	m_Rect.h = m_RectHeight;
	SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(m_Renderer, &m_Rect);
}

void cSprite::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Red = r;
	Green = g;
	Blue = b;
	Alpha = a;
}
