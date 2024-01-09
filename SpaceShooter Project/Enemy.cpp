#include "Enemy.h"

Enemy::Enemy(SDL_Texture* texture)
{
	m_texture = texture;
	setSpawn();
	m_w = 50; //width
	m_h = 50; //height
}

void Enemy::Draw(SDL_Renderer* renderer)
{
	SDL_Rect dstRect{ m_x, m_y, m_w, m_h };
	SDL_RenderCopy(renderer, m_texture, NULL, &dstRect);
}

float Enemy::MoveDown()
{
	m_y += enemySpeed;
	return m_y;
}

void Enemy::setSpawn()
{
	std::random_device x;
	std::uniform_int_distribution<int> dist(50, 700);
	m_x = dist(x);
}




