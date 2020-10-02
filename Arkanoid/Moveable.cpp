#include "Moveable.h"

Moveable::Moveable()
{
}

void Moveable::setVelocity(const sf::Vector2f& vel)
{
	velocity = vel;
}

const sf::Vector2f& Moveable::getVelocity() const
{
	return velocity;
}
