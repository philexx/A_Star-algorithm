#ifndef SPRITE_H
#define SPRITE_H
#include "Framework.h"
#include "Vector2D.h"

class cSprite
{
private:
	SDL_Renderer* m_Renderer;
	SDL_Texture* m_texture;
	SDL_Rect m_Rect;
	SDL_Rect m_sourceRect;
	Uint8 Red;
	Uint8 Green;
	Uint8 Blue;
	Uint8 Alpha;
private:
	int m_NumFrames;
	int m_FrameWidth;
	int m_RectWith;
	int m_RectHeight;
public:
	cSprite();
	~cSprite();
	void Load(const std::string& filename); //Load not animated sprites 
	void Load(const std::string& filename, int frameWidth, int frameHeight); // load animated sprites
	void Render();//Render not animated sprites
	void Render(float currentFrame); //Render animated sprites
	void RenderLine(int x1, int x2, int x3, int x4);
	void SetPos(const vec2& Position);
	void DrawRect();
	void DrawRectOutline();
	void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
public:
	SDL_Rect GetRect() { return m_Rect; }
};

#endif // !SPRITE_H
