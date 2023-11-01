#pragma once
#include "GameObject.h"
#include "SDL.h"
class Ship : public GameObject
{
public:
	Ship(SDL_Texture* texture);

	float KeyMoveUp();
	float KeyMoveDown();
	float KeyMoveLeft();
	float KeyMoveRight();
	//float MouseMovement();

	
private:
	float speed = 10;
};

