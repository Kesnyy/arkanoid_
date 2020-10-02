#pragma once
#include "Renderable.h"
#include "GameObject.h"
#include "Moveable.h"

class Paddle : public GameObject, public Renderable, public Moveable
{
public:
	Paddle(const sf::Vector2f &size, int id);

	void update(const sf::Time& deltaTime);
	const sf::Vector2f& getSize() const;
private:
	virtual void setShape();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; //inherited from Renderable

	sf::RectangleShape paddle;
	sf::Vector2f size;
};

