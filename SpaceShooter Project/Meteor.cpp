#include "Meteor.h"
Meteor::Meteor(SDL_Texture* texture)
{
	m_texture = texture;
	setSpawnX();
	setSpawnY();
	m_w = 125; //width
	m_h = 125; //height
}

void Meteor::Draw(SDL_Renderer* renderer)
{
	SDL_Rect dstRect{ m_x, m_y, m_w, m_h };
	SDL_RenderCopy(renderer, m_texture, NULL, &dstRect);
}

float Meteor::MoveDown()
{
	m_y += meteorSpeed;
	return m_y;
}

void Meteor::setSpawnX()
{
	std::random_device x;
	std::uniform_int_distribution<int> dist(50, 700);
	m_x = dist(x);
}

void Meteor::setSpawnY()
{
	int negative = 960;
	std::random_device y;
	std::uniform_int_distribution<int> dist(0, 960);
	m_y = dist(y) - negative;

}
