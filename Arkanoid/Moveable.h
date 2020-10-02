#pragma once
#include <SFML/Graphics.hpp>
class Moveable
{
public:
	Moveable();
	void setVelocity(const sf::Vector2f& vel);
	const sf::Vector2f& getVelocity() const;
protected:
	sf::Vector2f velocity;
};

