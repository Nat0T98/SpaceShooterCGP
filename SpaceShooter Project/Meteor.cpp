#include "Meteor.h"
Meteor::Meteor(SDL_Texture* texture)
{
	m_texture = texture;
	m_x = 400; //x pos
	m_y = 200; //y pos
	m_w = 50; //width
	m_h = 50; //height
}

void Meteor::Draw(SDL_Renderer* renderer)
{
	SDL_Rect dstRect{ m_x, m_y, m_w, m_h };
	SDL_RenderCopy(renderer, m_texture, NULL, &dstRect);
}