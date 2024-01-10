#pragma once
#include "GameObject.h"
#include "SDL.h"
class Comet : public GameObject
{
public:
	Comet(SDL_Texture* texture);
	void Draw(SDL_Renderer* renderer) override;

	float MoveDown();
	void setSpawnX();
	void setSpawnY();
};