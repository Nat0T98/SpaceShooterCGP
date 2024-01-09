#include "GameObject.h"

GameObject::GameObject(SDL_Texture* texture)
{
	m_texture = texture;
}

GameObject::GameObject()
{
}

void GameObject::Draw(SDL_Renderer* renderer)
{
	SDL_Rect srcRect;
	if (isAnimated)
	{
		int currentFrameIndex = (int)(timeInAnimationState * animationSpeed) % animFrames;
		srcRect = { currentFrameIndex * animPixelWidth, animState * animPixelHeight, animPixelWidth, animPixelHeight };
	}
	SDL_Rect dstRect{ m_x, m_y, m_w, m_h };
	SDL_RenderCopy(renderer, m_texture, isAnimated ? &srcRect : NULL, &dstRect);

}



SDL_Texture* GameObject::getTexture(void)
{
	return m_texture;
}

int	GameObject::getX(void) 
{
	return m_x;
}

int	GameObject::getY(void)
{
	return m_y;
}

void GameObject::setX(float x) 
{
	m_x = x;
}

void GameObject::setY(float y) 
{
	m_y = -50;
}

void GameObject::randXpos()
{
	std::random_device rx;
	std::uniform_int_distribution<int> dist(50, 700);
	m_x = dist(rx);
}

void GameObject::randYpos()
{
	int negative = 500;
	std::random_device ry;
	std::uniform_int_distribution<int> dist(0, 500);
	m_y = dist(ry) - negative;

}
void GameObject::resetEnPos()
{
	if (m_y >= 950)
	{
		randXpos();
		randYpos();		
	};
		
}

void GameObject::randMetWidth()
{
	std::random_device w;
	std::uniform_int_distribution<int> dist(50, 200);
	m_w = dist(w);
}

void GameObject::randMetHeight()
{
	std::random_device h;
	std::uniform_int_distribution<int> dist(50, 200);
	m_h = dist(h);
}

void GameObject::resetMetPos()
{
	if (m_y >= 950)
	{
		randXpos();
		randYpos();
		randMetHeight();
		randMetWidth();
	};
}

