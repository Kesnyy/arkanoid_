#pragma once
#include "Renderable.h"

class RenderSystem
{
public:
	RenderSystem(sf::RenderWindow& wd);
	void add(Renderable &object);
	void remove(int id);
	void render();
private:
	std::vector<Renderable *> drawableObjects;
	sf::RenderWindow& window;
};

