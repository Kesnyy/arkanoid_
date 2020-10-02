#pragma once
#include <SFML/Graphics.hpp>

class Renderable : public sf::Drawable
{
public:
	Renderable(int id);

	const int& getId() const;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0; //inheritated from Drawable
	int id;
};

