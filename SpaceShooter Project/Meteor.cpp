#include "Meteor.h"
Meteor::Meteor(SDL_Texture* texture)
{
	m_texture = texture;
	setSpawn();
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

void Meteor::setSpawn()
{
	std::random_device x;
	std::uniform_int_distribution<int> dist(50, 700);
	m_x = dist(x);
}
