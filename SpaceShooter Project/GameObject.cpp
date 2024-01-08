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

int	GameObject::getWidth(void) {
	return _width;
}

int	GameObject::getHeight(void) {
	return _height;
}

int	GameObject::getX(void) {
	return _x;
}

int	GameObject::getY(void) {
	return _y;
}

SDL_Texture* GameObject::getTexture(void) {
	return _texture;
}

void GameObject::setWidth(int width) {
	_width = width;
}

void GameObject::setHeight(int height) {
	_height = height;
}

void GameObject::setX(int x) {
	_x = x;
}


void GameObject::setY(int y) {
	_y = y;
}

