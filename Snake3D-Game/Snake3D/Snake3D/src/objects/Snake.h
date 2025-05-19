#pragma once
#include <deque>
#include <memory>

#include <glm/glm.hpp>
#include <SDL.h>
#include <SDL_mixer.h>

#include "..\model\SnakeModel.h"
#include "..\model\FruitModel.h"
#include "Highscore.h"

enum class Direction {
	pause = 0,
	left,
	right,
	up,
	down,
	forward,
	backward
};

class Snake {
public:
	Snake();
	~Snake();

	std::deque<glm::ivec3> mSnakeBody;
	std::shared_ptr<std::deque<std::shared_ptr<SnakeModel>>> mSnakeModel = std::make_shared<std::deque<std::shared_ptr<SnakeModel>>>();
	std::shared_ptr<FruitModel> mFruitModel = std::make_shared<FruitModel>();

	Direction mDirection = Direction::pause;

	int mScore;
	bool mIsRunning;
	bool mIsGameOver;

	int mLevel = 40;

	int mXPos;
	int mYPos;
	int mZPos;

	int mFruitXPos;
	int mFruitYPos;
	int mFruitZPos;

	Mix_Music* myMusic = nullptr;
	Mix_Chunk* mySound = nullptr;

	bool mIsPlayingMusic = true;
	bool mIsPlayingSound = true;

	void init();
	void update();
	void placeFruit();

	Highscore mHighscore;
};
