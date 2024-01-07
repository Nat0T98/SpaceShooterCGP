#include "Enemy.h"

Enemy::Enemy(SDL_Texture* texture)
{
	m_texture = texture;
	m_x = 200; //x pos
	m_y = 200; //y pos
	m_w = 50; //width
	m_h = 50; //height
}

void Enemy::Draw(SDL_Renderer* renderer)
{
	SDL_Rect dstRect{ m_x, m_y, m_w, m_h };
	SDL_RenderCopy(renderer, m_texture, NULL, &dstRect);
}

//void Enemy::DestroyShip(GameObject)
//{
//	delete ;
//}
//#include "Enemy.class.hpp"
//
//Enemy::Enemy(int x) {
//	setWidth(ENEMY_WIDTH);
//	setHeight(ENEMY_HEIGHT);
//	setX(x);
//	setY(-ENEMY_HEIGHT - 1);
//}
//
//Enemy::~Enemy(void) {
//}
//
//void	Enemy::moveDown(void) {
//	setY(getY() + 3);
//}


