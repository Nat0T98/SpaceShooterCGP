#include <iostream>
#include <cstdlib> 
#include <ctime>   
#include <random>
#pragma once
#include <string>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>

class GameObject
{
public:
	
	GameObject(SDL_Texture* texture);
	GameObject();

	int MaxEnCount = 10;
	int MaxMetCount = 10;
	float enemySpeed = 12;
	float meteorSpeed = 7;
	float m_x; //x pos
	float m_y; //y pos
	float m_w; //width
	float m_h; //height
	

	bool isAnimated = false;
	int animPixelHeight = 16;
	int animPixelWidth = 16;
	int animState = 0;
	int animFrames = 1;
	float timeInAnimationState = 0;
	float animationSpeed = 1;

	SDL_Texture* m_texture = nullptr;
	virtual void Draw(SDL_Renderer* renderer);	
	SDL_Texture* getTexture(void);

	int	getX(void);
	int	getY(void);		
	void setX(float x);
	void setY(float y);
	void resetEnPos();
	void resetMetPos();
	void randXpos();
	void randYpos();
	void randMetWidth();
	void randMetHeight();
	
};


