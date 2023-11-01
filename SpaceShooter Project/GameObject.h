#pragma once
#include "SDL.h"
class GameObject
{

public:
	GameObject(SDL_Texture* texture);
	GameObject();
	float m_x = 10; //x pos
	float m_y = 10; //y pos
	float m_w = 50; //width
	float m_h = 50; //height

	SDL_Texture* m_texture = nullptr;

	void Draw(SDL_Renderer* renderer);

};

