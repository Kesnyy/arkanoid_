#include "RenderSystem.h"

RenderSystem::RenderSystem(sf::RenderWindow& wd)
	:window(wd)
{
}

void RenderSystem::add(Renderable& object)
{
	drawableObjects.push_back(&object);
}

void RenderSystem::remove(int id)
{
	auto it = drawableObjects.begin();
	while (it != drawableObjects.end())
	{
		if ((*it)->getId() == id)
		{
			it = drawableObjects.erase(it);
		}
		else ++it;
	}
}

void RenderSystem::render()
{
	for (auto& obj : drawableObjects)
	{
		if(obj) window.draw(*obj);
	}
}
