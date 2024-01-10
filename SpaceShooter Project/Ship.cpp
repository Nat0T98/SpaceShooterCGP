#include "Ship.h"

Ship::Ship(SDL_Texture* texture)
{
	health = maxHealth;
	m_texture = texture;	
	m_x = 800; //x pos
	m_y = 300; //y pos
	m_w = 60; //width
	m_h = 60; //height
}

void Ship::Draw(SDL_Renderer* renderer)
{
	SDL_Rect srcRect;
	if (isAnimated)
	{
		int currentFrameIndex = (int)(timeInAnimationState * animationSpeed) % animFrames;
		srcRect = { currentFrameIndex * animPixelWidth, animState * animPixelHeight, animPixelWidth, animPixelHeight };
	}
	
	SDL_Rect dstRect{ m_x - m_w / 2, m_y - m_h / 2, m_w, m_h };
	
	SDL_RenderCopy(renderer, m_texture, isAnimated ? &srcRect : NULL, &dstRect);	
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

void Ship::ShipBounds()
{
	if (m_x > 750)
		m_x = 700;
	if (m_x < 0)
		m_x = 50;

	if (m_y > 960)
		m_y = 900;
	if (m_y < 0)
		m_y = 50;
}

bool Ship::dead()
{
	if (health <= minHealth)
	{
		health = minHealth;
	}
	return isDead = true;
}

int Ship::getHealth()
{
	return health;
}




