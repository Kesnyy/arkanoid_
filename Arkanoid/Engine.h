#pragma once
#include "Paddle.h"
#include "Block.h"
#include "RenderSystem.h"
#include "Ball.h"
#include "TextInfo.h"
#include <memory>

class Engine
{
public:
	Engine();
	void start();
private:
	void update(const sf::Time& deltaTime);
	void processEvents();
	void draw();

	void setBlocks();
	void setTextInfo();
	void pushBlocksToRenderable();
	bool checkCollision(const GameObject *first, const GameObject *second);
	void updateCollision(); //could be another class but since it's so small project, aint gonna make it more complicated
	void updateTextInfo();
	void checkBlocks();

	bool ballPlayerCollision();
	int randomNumber(int a, int b); //a, b = range
	float calculateDistance(float point1, float point2) const;
	sf::RenderWindow window;
	sf::Font font;
	RenderSystem renderSystem;
	Paddle player;
	Ball ball;
	std::vector<std::shared_ptr<Block>> blocks;
	std::shared_ptr<TextInfo> destroyedBlocksText;
	std::shared_ptr<TextInfo> ballVelocityText;
	std::shared_ptr<TextInfo> playerVelocityText;
	std::shared_ptr<TextInfo> gameOverText;

	int destroyedCount;
	int leftToDestroyCount;
	bool gameOver;
	bool xOverScreen;
	bool yOverScreen;
	bool isGameOverAdded;
};

