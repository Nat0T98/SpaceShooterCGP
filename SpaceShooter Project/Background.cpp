#include "Background.h"
Background::Background(SDL_Texture* texture)
{
	m_texture = texture;
	m_x = 0;
	m_y = 0;
	m_w = 750; //width
	m_h = 960; //height
}

void Background::Draw(SDL_Renderer* renderer)
{
	SDL_Rect dstRect{ m_x, m_y, m_w, m_h };
	SDL_RenderCopy(renderer, m_texture, NULL, &dstRect);
}

//float Background::MoveDown()
//{
//	m_y += backgroundSpeed;
//	return m_y;
//}


