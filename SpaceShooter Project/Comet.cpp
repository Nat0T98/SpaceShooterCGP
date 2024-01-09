#include "Comet.h"

Comet::Comet(SDL_Texture* texture)
{
	m_texture = texture;
	setSpawnX();
	setSpawnY();
	m_w = 25; //width
	m_h = 25; //height
}

void Comet::Draw(SDL_Renderer* renderer)
{
	SDL_Rect dstRect{ m_x, m_y, m_w, m_h };
	SDL_RenderCopy(renderer, m_texture, NULL, &dstRect);
}

float Comet::MoveDown()
{
	m_y += cometSpeed;
	return m_y;
}

void Comet::setSpawnX()
{
	std::random_device x;
	std::uniform_int_distribution<int> dist(50, 700);
	m_x = dist(x);
}

void Comet::setSpawnY()
{
	int negative = 700;
	std::random_device y;
	std::uniform_int_distribution<int> dist(0, 700);
	m_y = dist(y) - negative;

}