#include "Laser.h"

Laser::Laser(SDL_Texture* texture)
{
	m_texture = texture;
	m_x = 300;
	m_y = 700;
	m_w = 30; //width
	m_h = 30; //height
}

void Laser::Draw(SDL_Renderer* renderer)
{
	SDL_Rect dstRect{ m_x, m_y, m_w, m_h };
	SDL_RenderCopy(renderer, m_texture, NULL, &dstRect);
}

float Laser::Move()
{
	m_y -= speed;
	return m_y;
}


