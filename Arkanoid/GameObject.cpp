#include "GameObject.h"

GameObject::GameObject()
	:shape(nullptr)
{
}

sf::Shape* GameObject::getShape() const
{
	return shape;
}

const sf::Vector2f& GameObject::getPosition()
{
	return shape->getPosition();
}
