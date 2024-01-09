#pragma once
#include "GameObject.h"
#include "SDL.h"
class Ship : public GameObject
{
public:
	
	bool isDead;
	int health;
	const int maxHealth = 100;
	const int minHealth = 0;

	Ship(SDL_Texture* texture);

	void Draw(SDL_Renderer* renderer) override;

	float KeyMoveUp();
	float KeyMoveDown();
	float KeyMoveLeft();
	float KeyMoveRight();
	void ShipBounds();
	bool dead();
	int getHealth();

private:
	float speed = 10;
	
};
