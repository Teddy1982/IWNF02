#define CATCH_CONFIG_MAIN
#include <catch_amalgamated.hpp>
#include "..\..\Snake3D\Snake3D\src\objects\Snake.h"


TEST_CASE("eatFruitTest") {
	Snake snake;
	snake.init();

	int snakeBodySize = snake.mSnakeBody.size();
	int snakeModelSize = snake.mSnakeModel->size();

	REQUIRE(snakeBodySize == 1);
	REQUIRE(snakeModelSize == 1);

	snake.mDirection = Direction::up;

	snake.mFruitXPos = 5;
	snake.mFruitYPos = 5;
	snake.mFruitZPos = 5;

	snake.mXPos = 5;
	snake.mYPos = 4;
	snake.mZPos = 5;

	snake.update();

	snakeBodySize = snake.mSnakeBody.size();
	snakeModelSize = snake.mSnakeModel->size();

	REQUIRE(snakeBodySize == 2);
	REQUIRE(snakeModelSize == 2);
}

TEST_CASE("hitUpBorder") {
	Snake snake;
	snake.init();

	snake.mDirection = Direction::up;

	snake.mXPos = 5;
	snake.mYPos = 8;
	snake.mZPos = 5;

	snake.update();

	REQUIRE(snake.mIsRunning == true);

	snake.update();

	REQUIRE(snake.mIsRunning == false);
}

TEST_CASE("hitDownBorder") {
	Snake snake;
	snake.init();

	snake.mDirection = Direction::down;

	snake.mXPos = 5;
	snake.mYPos = 1;
	snake.mZPos = 5;

	snake.update();

	REQUIRE(snake.mIsRunning == true);

	snake.update();

	REQUIRE(snake.mIsRunning == false);
}

TEST_CASE("hitLeftBorder") {
	Snake snake;
	snake.init();

	snake.mDirection = Direction::left;

	snake.mXPos = 1;
	snake.mYPos = 5;
	snake.mZPos = 5;

	snake.update();

	REQUIRE(snake.mIsRunning == true);

	snake.update();

	REQUIRE(snake.mIsRunning == false);
}

TEST_CASE("hitRightBorder") {
	Snake snake;
	snake.init();

	snake.mDirection = Direction::right;

	snake.mXPos = 8;
	snake.mYPos = 5;
	snake.mZPos = 5;

	snake.update();

	REQUIRE(snake.mIsRunning == true);

	snake.update();

	REQUIRE(snake.mIsRunning == false);
}

TEST_CASE("hitForwardBorder") {
	Snake snake;
	snake.init();

	snake.mDirection = Direction::forward;

	snake.mXPos = 5;
	snake.mYPos = 5;
	snake.mZPos = 1;

	snake.update();

	REQUIRE(snake.mIsRunning == true);

	snake.update();

	REQUIRE(snake.mIsRunning == false);
}

TEST_CASE("hitBackwardBorder") {
	Snake snake;
	snake.init();

	snake.mDirection = Direction::backward;

	snake.mXPos = 5;
	snake.mYPos = 5;
	snake.mZPos = 8;

	snake.update();

	REQUIRE(snake.mIsRunning == true);

	snake.update();

	REQUIRE(snake.mIsRunning == false);
}
