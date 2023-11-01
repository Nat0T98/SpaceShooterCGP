#include "Ship.h"

Ship::Ship(SDL_Texture* texture)
{
	m_texture = texture;
}

float Ship::KeyMoveUp()
{
	m_y-= speed;
	return m_y;
}

float Ship::KeyMoveDown()
{
	m_y+= speed;
	return m_y;
}

float Ship::KeyMoveLeft()
{
	m_x-= speed;
	return m_x;
}

float Ship::KeyMoveRight()
{
	m_x+= speed;
	return m_x;

}



