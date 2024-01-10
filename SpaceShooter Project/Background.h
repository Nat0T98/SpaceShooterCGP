#pragma once
#include "GameObject.h"
#include "SDL.h"
class Background : public GameObject
{
public:
	Background(SDL_Texture* texture);
	void Draw(SDL_Renderer* renderer) override;
};
