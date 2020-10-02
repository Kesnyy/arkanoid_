#pragma once
#include "Renderable.h"
#include "GameObject.h"
#include "Moveable.h"

class Ball : public GameObject, public Renderable, public Moveable
{
public:
	Ball(int id);
	void bounceOnXAxis();
	void bounceOnYAxis();
	void speedUp();

	void update(const sf::Time& deltaTime);
	const float& getRadius() const;
private:
	virtual void setShape();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; //inherited from renderable
	sf::CircleShape ballShape;
};

