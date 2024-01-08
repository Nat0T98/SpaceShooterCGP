#include <iostream>
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
private:
	int	_width;
	int	_height;
	int	_x;
	int	_y;
	SDL_Texture* _texture;

public:
	
	GameObject(SDL_Texture* texture);
	GameObject();

	int MaxEnCount = 100;
	int MaxMetCount = 20;
	

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

	int				getWidth(void);
	int				getHeight(void);
	int				getX(void);
	int				getY(void);
	SDL_Texture* getTexture(void);

	void			setWidth(int width);
	void			setHeight(int height);
	void			setX(int x);
	void			setY(int y);
	
};


