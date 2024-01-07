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

//#ifndef AUNIT_CLASS_HPP
//#define AUNIT_CLASS_HPP
//
//#include "SpaceShooter.hpp"
//
//class AUnit {
//
//private:
//	int				_width;
//	int				_height;
//	int				_x;
//	int				_y;
//	SDL_Texture* _texture;
//
//public:
//	AUnit(void);
//	~AUnit(void);
//
//	int				getWidth(void);
//	int				getHeight(void);
//	int				getX(void);
//	int				getY(void);
//	SDL_Texture* getTexture(void);
//
//	void			setWidth(int width);
//	void			setHeight(int height);
//	void			setX(int x);
//	void			setY(int y);
//
//	bool			load(std::string path, t_settings& settings);
//	void			free(void);
//	void			render(t_settings& settings);
//
//	virtual void	moveDown(void) = 0;
//	virtual void	moveRight(void);
//	virtual void	moveLeft(void);
//	virtual void	moveUp(void);
//
//};
//
//#endif






//class Background {
//
//private:
//	Enemy* _enemies[ENEMY_MAX_QUANTITY];
//	Meteor* _meteors[METEOR_MAX_QUANTITY];
//	Star* _stars[STAR_MAX_QUANTITY];
//	SDL_Texture* _texture;
//
//public:
//	Background(void);
//	~Background(void);
//
//	void	free(void);
//	void	clean(void);
//	void	loadGameOver(std::string, t_settings&);
//	void	drawInfoBox(Player&, t_settings&, unsigned long);
//
//	void	makeStar(t_settings&);
//	void	makeMeteor(t_settings&);
//	void	makeEnemy(t_settings&);
//
//	void	displayStar(t_settings&);
//	void	displayMeteor(t_settings&, bool);
//	void	displayEnemy(t_settings&, bool);
//
//	bool	hitEnemy(Player& player);
//	bool	hitMeteor(Player& player);
//
//	void	killEnemy(Player& player);
//	void	killMeteor(Player& player);
//
//
//};
