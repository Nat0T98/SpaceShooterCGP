#include "Enemy.h"

Enemy::Enemy(SDL_Texture* texture)
{
	m_texture = texture;
	setSpawnX();
	setSpawnY();
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

void Enemy::setSpawnX()
{
	std::random_device x;
	std::uniform_int_distribution<int> dist(50, 700);
	m_x = dist(x);
}

void Enemy::setSpawnY()
{
	int negative = 500;
	std::random_device y;
	std::uniform_int_distribution<int> dist(0, 500);
	m_y = dist(y) - negative;

}




