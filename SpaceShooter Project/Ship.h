#pragma once
#include "GameObject.h"
#include "SDL.h"
class Ship : public GameObject
{
public:
	Ship(SDL_Texture* texture);

	void Draw(SDL_Renderer* renderer) override;

	float KeyMoveUp();
	float KeyMoveDown();
	float KeyMoveLeft();
	float KeyMoveRight();
	
private:
	float speed = 10;
};
