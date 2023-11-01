#pragma once
#include "SDL.h"
class GameObject
{

public:
	GameObject(SDL_Texture* texture);

	float m_x = 200; //x pos
	float m_y = 200; //y pos
	float m_w = 50; //width
	float m_h = 50; //height

	SDL_Texture* m_texture = nullptr;

	void Draw(SDL_Renderer* renderer);

};

