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

void GameObject::randXpos()
{
	std::random_device rx;
	std::uniform_int_distribution<int> dist(50, 700);
	m_x = dist(rx);
}

void GameObject::randYpos()
{
	int negative = 960;
	std::random_device ry;
	std::uniform_int_distribution<int> dist(0, 960);
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


void GameObject::randCometWidth()
{
	std::random_device cw;	
	std::uniform_int_distribution<int> dist(25, 30);
	m_w = dist(cw);	
}

void GameObject::randCometHeight()
{
	std::random_device ch;	
	std::uniform_int_distribution<int> dist(25, 30);
	m_h = dist(ch);	
}



void GameObject::resetCometPos()
{
	if (m_y >= 950)
	{
		randXpos();
		randYpos();
		randCometHeight();
		randCometWidth();
	};
}

void GameObject::resetPickUpPos()
{
	if (m_y >= 950)
	{
		randXpos();	
		randYpos();
	};
}
