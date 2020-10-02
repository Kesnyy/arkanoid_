#pragma once
#include "Renderable.h"
#include "GameObject.h"
class Block : public Renderable, public GameObject
{
public:
	Block(int id);
	Block(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color &color, int id);
	void setPosition(const sf::Vector2f &position);
	void setColor(const sf::Color &color);
	void setSize(const sf::Vector2f &size);
	void setDestroyed(const bool& destroyed_);
	const bool& isDestroyed() const;
private:
	virtual void setShape(); //inh from game object
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; //inherited from Renderable
	
	sf::RectangleShape block;

	bool destroyed;
};

