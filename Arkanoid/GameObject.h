#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
class GameObject
{
public:
	GameObject();
	sf::Shape* getShape() const;
	const sf::Vector2f& getPosition();
protected:
	virtual void setShape() = 0;
	sf::Shape* shape;
};

