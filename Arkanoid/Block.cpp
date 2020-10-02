#include "Block.h"

Block::Block(int id)
	:destroyed(false), Renderable(id)
{
	setShape();
	setSize(sf::Vector2f(0, 0));
	setPosition(sf::Vector2f(0, 0));
	setColor(sf::Color::White);
}

Block::Block(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, int id)
	:destroyed(false), Renderable(id)
{
	
	setSize(size);
	setPosition(position);
	setColor(color);
	block.setOutlineColor(sf::Color::Red);
	block.setOutlineThickness(1);
	setShape();
}

void Block::setPosition(const sf::Vector2f& position)
{
	block.setPosition(position);
}

void Block::setColor(const sf::Color& color)
{
	block.setFillColor(color);
}

void Block::setSize(const sf::Vector2f& size)
{
	block.setSize(size);
}

void Block::setDestroyed(const bool& destroyed_)
{
	destroyed = destroyed_;
}

const bool& Block::isDestroyed() const
{
	return destroyed;
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(block);
}

void Block::setShape()
{
	shape = &block;
}
