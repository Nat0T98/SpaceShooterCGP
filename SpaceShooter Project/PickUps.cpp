#include "PickUps.h"

PickUps::PickUps(SDL_Texture* texture)
{
	m_texture = texture;
	setSpawnX();
	setSpawnY();
	m_w = 100; //width
	m_h = 100; //height
}

void PickUps::Draw(SDL_Renderer* renderer)
{
	SDL_Rect dstRect{ m_x, m_y, m_w, m_h };
	SDL_RenderCopy(renderer, m_texture, NULL, &dstRect);
}


float PickUps::MoveDown()
{
	m_y += meteorSpeed;
	return m_y;
}

void PickUps::setSpawnX()
{
	std::random_device x;
	std::uniform_int_distribution<int> dist(50, 700);
	m_x = dist(x);
}

void PickUps::setSpawnY()
{
	int negative = 700;
	std::random_device y;
	std::uniform_int_distribution<int> dist(0, 700);
	m_y = dist(y) - negative;

}
