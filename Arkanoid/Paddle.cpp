#include "Paddle.h"

Paddle::Paddle(const sf::Vector2f& size, int id)
	:Renderable(id), size(size)
{
	paddle.setSize(size);
	paddle.setFillColor(sf::Color::Green);
	paddle.setOutlineColor(sf::Color(10, 99, 124));
	paddle.setOutlineThickness(2);
	paddle.setPosition(1024 / 2 - size.x / 2, 768 - size.y - 1); // centered i guess
	setShape();
	setVelocity(sf::Vector2f(250, 0));
	//paddle.setOrigin(size.x / 2, size.y / 2);
}

void Paddle::update(const sf::Time& deltaTime)
{
	sf::Vector2f dirVector(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		dirVector = sf::Vector2f(-1, 0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		dirVector = sf::Vector2f(1, 0);

	paddle.move(dirVector.x * deltaTime.asSeconds() * velocity.x,
		dirVector.y * deltaTime.asSeconds() * velocity.y);
}

void Paddle::setShape()
{
	shape = &paddle;
}

const sf::Vector2f& Paddle::getSize() const
{
	return size;
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(paddle);
}
