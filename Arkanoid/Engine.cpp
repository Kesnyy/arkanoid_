#include "Engine.h"
#include <iostream>
#include <random>
Engine::Engine()
	:window(sf::VideoMode(1024, 768), "Arkanoid"), player(sf::Vector2f(120, 20), 0),
	renderSystem(window), destroyedCount(0), leftToDestroyCount(0), ball(2), gameOver(false),
	yOverScreen(false), xOverScreen(false), isGameOverAdded(false)
{
	if (!font.loadFromFile("resources/font.ttf"))
	{
		std::cout << "Failed to load font\n";
		return;
	}
	setTextInfo();
	renderSystem.add(player);
	renderSystem.add(ball);
	renderSystem.add(*destroyedBlocksText);
	renderSystem.add(*playerVelocityText);
	renderSystem.add(*ballVelocityText);
}

void Engine::start()
{
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock fpsClock;

	setBlocks();
	pushBlocksToRenderable();

	while (window.isOpen())
	{
		timeSinceLastUpdate += fpsClock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		draw();
	}
}

void Engine::update(const sf::Time& deltaTime)
{
	if (!gameOver)
	{
		updateCollision();
		checkBlocks();
		ball.update(deltaTime);
		player.update(deltaTime);
		updateTextInfo();
	}
	else
	{
		if (!isGameOverAdded)
		{
			renderSystem.add(*gameOverText);
			isGameOverAdded = true;
		}
	}
}

void Engine::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

void Engine::draw()
{
	window.clear();
	renderSystem.render();
	window.display();
}

void Engine::setBlocks()
{
	blocks.clear();
	int index = 2; //starts with 2 since player = 0 and ball = 1
	sf::Vector2f blockSize(64, 20); //1024 / blockSize.x must be dividable (32, 64..)
	int piecesPerWidth = 1024 / blockSize.x; //1024 = window width
	int yGridSize = 4; //change to whatever you want

	sf::Vector2f blockPos(0, 0);
	for (int i = 0; i < yGridSize; ++i)
	{
		for (int j = 0; j < piecesPerWidth; ++j)
		{
			sf::Color clr(randomNumber(0, 255), randomNumber(0, 255), randomNumber(0, 255));
			blocks.push_back(std::make_shared<Block>(blockSize, blockPos, clr, index++));
			blockPos.x += blockSize.x;
		}
		blockPos.x = 0;
		blockPos.y += blockSize.y + 1;
	}
	leftToDestroyCount = blocks.size();
}

void Engine::setTextInfo()
{
	destroyedBlocksText = std::make_shared<TextInfo>("Destroyed: ", font, 2000);
	destroyedBlocksText->setPosition(sf::Vector2f(800, 600));

	ballVelocityText = std::make_shared<TextInfo>("Ball velocity: ", font, 2001);
	ballVelocityText->setPosition(sf::Vector2f(50, 600));
	ballVelocityText->setCharacterSize(15);

	playerVelocityText = std::make_shared<TextInfo>("Player speed: ", font, 2002);
	playerVelocityText->setPosition(sf::Vector2f(50, 625));
	playerVelocityText->setCharacterSize(15);

	gameOverText = std::make_shared<TextInfo>("GAME IS OVER! Thank you for playing :)", font, 2003);
	gameOverText->setPosition(sf::Vector2f(250, 500));
	gameOverText->setCharacterSize(45);
}

void Engine::pushBlocksToRenderable()
{
	for (int i = 0; i < blocks.size(); ++i)
	{
		renderSystem.add(*blocks[i]);
	}
	
}

bool Engine::checkCollision(const GameObject* first, const GameObject* second)
{
	if (first == nullptr || second == nullptr) return false;
	if (first->getShape() == nullptr || second->getShape() == nullptr) return false;
	return first->getShape()->getGlobalBounds().intersects(second->getShape()->getGlobalBounds());
}

void Engine::updateCollision()
{
	if (ballPlayerCollision())
	{
		ball.bounceOnYAxis();
		ball.speedUp();
	}
	for (int i = 0; i < blocks.size(); ++i)
	{
		auto block = blocks.at(i).get();
		if (checkCollision(&ball, block))
		{
			if (!block->isDestroyed())
			{
				ball.bounceOnYAxis();
				ball.speedUp();
				block->setDestroyed(true);
				renderSystem.remove(block->getId());
				std::cout << "kolizja\n";

				++destroyedCount;
			}
			
		}
	}
	if (ball.getPosition().x <= 0 || ball.getPosition().x + ball.getRadius() >= 1024 && !xOverScreen)
	{
		ball.bounceOnXAxis();
		xOverScreen = true;
	}
	else if (ball.getPosition().x > 0 && ball.getPosition().x + ball.getRadius() < 1024) xOverScreen = false;
	
	if (ball.getPosition().y <= 0 && !yOverScreen)
	{
		ball.bounceOnYAxis();
		yOverScreen = true;
	}
	if (ball.getPosition().y > 0) yOverScreen = false;
	
}

void Engine::updateTextInfo()
{
	std::string tmp = std::to_string(destroyedCount);
	std::string tmp2 = std::to_string(leftToDestroyCount);
	destroyedBlocksText->setText("Destroyed: " + tmp + "/" + tmp2);

	auto vel = (ball.getVelocity().x > ball.getVelocity().y ? ball.getVelocity().x : ball.getVelocity().y);

	std::string ballXVel = std::to_string(std::abs(vel));
	ballVelocityText->setText("Ball speed: " + ballXVel);

	std::string playerVel = std::to_string(std::abs(player.getVelocity().x)); //only X since paddle doesnt move elsewhere
	playerVelocityText->setText("Player speed: " + playerVel);
}

void Engine::checkBlocks()
{
	auto it = blocks.begin();
	while (it != blocks.end())
	{
		if ((*it)->isDestroyed())
			it = blocks.erase(it);
		else
			++it;
	}
	if (blocks.size() == 0) gameOver = true;
}

bool Engine::ballPlayerCollision()
{
	auto ballPos = ball.getPosition();
	auto playerPos = player.getPosition();
	auto playerSize = player.getSize();
	auto ballRadius = ball.getRadius();
	sf::Vector2f playerCenter(playerPos.x + playerSize.x / 2, playerPos.y + playerSize.y / 2);

	float xDist = calculateDistance(ballPos.x, playerCenter.x) - (playerSize.x / 2);
	float yDist = calculateDistance(ballPos.y, playerCenter.y) - (playerSize.y / 2);
	if (yDist <= 0)
	{
		gameOver = true;
		std::cout << "somet\n";
	}
	if (xDist <= ballRadius && yDist <= ballRadius)
	{
		if (xDist <= yDist) return true;
		else if (xDist > yDist)
		{
			gameOver = true;
		}
	}
	return false;
}

int Engine::randomNumber(int a, int b)
{

	std::random_device rd; 
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(a, b);
	return distrib(gen);
}

float Engine::calculateDistance(float point1, float point2) const
{
	return abs(point1 - point2);
}

