#pragma once
#include <iostream>
#include <cstdlib> 
#include <ctime>   
#include <random>
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

	//Object Speeds
	const float enemySpeed = 15;
	const float meteorSpeed = 10;
	const float cometSpeed = 20;
	const float backgroundSpeed = 1;
	
	//Object Specific Values
	const int enemyDamage = 2;
	const int meteorDamage = 3;
	const int cometDamage = 1;
	int HpPickUpVal = 1;
	int enemiesRemaining = 10;
	int Win = 0;

	//Object Size and Pos
	float m_x; //x pos
	float m_y; //y pos
	float m_w; //width
	float m_h; //height

	
	//for animations
	bool isAnimated = false;
	int animPixelHeight = 16;
	int animPixelWidth = 16;
	int animState = 0;
	int animFrames = 1;
	float timeInAnimationState = 0;
	float animationSpeed = 1;

	//Functions
	SDL_Texture* m_texture = nullptr;
	virtual void Draw(SDL_Renderer* renderer);	
		
	void resetEnPos();
	void resetMetPos();
	void resetCometPos();
	void resetPickUpPos();
	void randXpos();
	void randYpos();
	void randMetWidth();
	void randMetHeight();
	void randCometWidth();
	void randCometHeight();	
};


