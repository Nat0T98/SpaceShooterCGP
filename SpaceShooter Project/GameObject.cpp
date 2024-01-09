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

void GameObject::randX()
{
	//float minX = 50.0f;
	//float maxX = 700.0f;
	//
	//srand(time(0));
	//RandX = rand() % 700 + 1;
	////RandX = minX + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (maxX - minX)));	
	//m_x = RandX;
}

void GameObject::randY()
{
	//float minY = 0.0f;
	//float maxY = -200.0f;

	//srand(time(0));
	//RandY = rand() % -200 - 1;
	////RandY = minY + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (maxY - minY)));
	//m_y = RandY;
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

void GameObject::resetPos()
{
	if (m_y >= 950)
	{
		m_y = -50;
		std::random_device x;
		std::uniform_int_distribution<int> dist(50, 700);
		m_x = dist(x);
		/*int w = time(0);
		srand(w);
		m_x = rand() % 700 + 1*/;
	};
		
}

