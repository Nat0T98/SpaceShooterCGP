#pragma once
#include "SDL.h"
class GameObject
{

public:
	GameObject(SDL_Texture* texture);
	GameObject();
	float m_x = 100; //x pos
	float m_y = 100; //y pos
	float m_w = 40; //width
	float m_h = 40; //height

	SDL_Texture* m_texture = nullptr;

	virtual void Draw(SDL_Renderer* renderer);

	bool isAnimated = false;
	int animPixelHeight = 16;
	int animPixelWidth = 16;
	int animState = 0;
	int animFrames = 1;
	float timeInAnimationState = 0;
	float animationSpeed = 1;

};

