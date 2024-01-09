#pragma once
#include "GameObject.h"
#include "SDL.h"
class PickUps : public GameObject
{
public:
	PickUps(SDL_Texture* texture);

	void Draw(SDL_Renderer* renderer) override;
	float MoveDown();
	void setSpawnX();
	void setSpawnY();

private:

};
