#pragma once
#include "GameObject.h"
#include "SDL.h"
class Meteor : public GameObject
{	
public:
	Meteor(SDL_Texture* texture);

	void Draw(SDL_Renderer* renderer) override;
	float MoveDown();
	void setSpawn();
		//void DestroyShip(GameObject);
private:

};

