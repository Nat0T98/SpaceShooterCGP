#pragma once
#include "GameObject.h"
#include "SDL.h"
class Enemy : public GameObject
{
public:
	Enemy(SDL_Texture* texture);
	
	void Draw(SDL_Renderer* renderer) override ;
	float MoveDown();
	//void DestroyShip(GameObject);
	void setSpawnX();
	void setSpawnY();
private:

};
