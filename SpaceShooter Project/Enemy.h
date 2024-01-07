#pragma once
#include "GameObject.h"
#include "SDL.h"
class Enemy : public GameObject
{
public:
	Enemy(SDL_Texture* texture);
	
	void Draw(SDL_Renderer* renderer) override ;
	//void DestroyShip(GameObject);

};
//#ifndef ENEMY_CLASS_HPP
//#define ENEMY_CLASS_HPP
//
//#include "AUnit.class.hpp"
//#include "SpaceShooter.hpp"
//
//class Enemy : public AUnit {
//
//public:
//	Enemy(int x);
//	~Enemy(void);
//
//	virtual void moveDown(void);
//};
//
//#endif