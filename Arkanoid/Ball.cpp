#include "Ball.h"

Ball::Ball(int id)
	:Renderable(id)
{
	ballShape.setPosition(sf::Vector2f(460, 700)); //so it will start over player to bounce back
	ballShape.setFillColor(sf::Color(15, 49, 221)); //some random color
	ballShape.setRadius(7);
	ballShape.setOutlineColor(sf::Color::Yellow);
	ballShape.setOutlineThickness(1.5f);
	setShape();
	setVelocity(sf::Vector2f(200, 200));
	
}

void Ball::bounceOnXAxis()
{
	velocity.x *= -1;
}

void Ball::bounceOnYAxis()
{
	velocity.y *= -1;
}

void Ball::speedUp()
{
	velocity.x *= 1.01f;
	velocity.y *= 1.01f;
}

void Ball::update(const sf::Time& deltaTime)
{
	if (velocity.x > 450) velocity.x = 450;
	if (velocity.y > 450) velocity.y = 450;
	ballShape.move(velocity * deltaTime.asSeconds());
}

const float& Ball::getRadius() const
{
	return ballShape.getRadius();
}

void Ball::setShape()
{
	shape = &ballShape;
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(ballShape);
}
