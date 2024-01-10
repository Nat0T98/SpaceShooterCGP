#pragma once
#include "GameObject.h"
#include "ship.h"
#include "SDL.h"
class Laser : public GameObject
{
public:
	Laser(SDL_Texture* texture);

	void Draw(SDL_Renderer* renderer) override;
	
	void IsOffScreen();
	
	float Move();
	
private:
	float speed = 10;
};

