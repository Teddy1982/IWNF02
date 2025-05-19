#include "Snake.h"

#include <ctime>

#include "..\opengl\RenderData.h"
#include "..\tools\Logger.h"

const int GAMEAREA_MIN_X_INDEX = 0;
const int GAMEAREA_MIN_Y_INDEX = 0;
const int GAMEAREA_MIN_Z_INDEX = 0;

const int GAMEAREA_MAX_X_INDEX = 9;
const int GAMEAREA_MAX_Y_INDEX = 9;
const int GAMEAREA_MAX_Z_INDEX = 9;

Snake::Snake() {
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		Logger::log(2, "SDL_AUDIO Init Error: %s\n", SDL_GetError());
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		Logger::log(2, "Mix_OpenAudio Error: %s\n", Mix_GetError());
	}

	myMusic = Mix_LoadMUS("audio/background_music.mp3");
	if (!myMusic) {
		Logger::log(2, "Mix_LoadMUS Error: %s\n", Mix_GetError());
	}

	mySound = Mix_LoadWAV("audio/eatFruit.wav");
	if (!mySound) {
		Logger::log(2, "Mix_LoadWAV Error: %s\n", Mix_GetError());
	}

	Mix_PlayMusic(myMusic, -1);
}

Snake::~Snake() {
	Mix_HaltMusic();
	Mix_FreeMusic(myMusic);
	myMusic = nullptr;
	Mix_HaltChannel(-1);
	mySound = nullptr;
	Mix_FreeChunk(mySound);
	Mix_CloseAudio();
	SDL_Quit();
}

void Snake::init() {
	mSnakeBody.clear();
	mSnakeModel->clear();

	mScore = 0;

	int random_values[3];

	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	for (int i = 0; i < 3; i++) {
		random_values[i] = std::rand() % 10;
	}

	mXPos = random_values[0];
	mYPos = random_values[1];
	mZPos = random_values[2];

	mSnakeBody.push_front(glm::ivec3(mXPos, mYPos, mZPos));

	mSnakeModel = std::make_shared<std::deque<std::shared_ptr<SnakeModel>>>();
	auto snakeHead = std::make_shared<SnakeModel>();
	snakeHead->init(mXPos, mYPos, mZPos);
	mSnakeModel->push_back(snakeHead);

	placeFruit();
	mDirection = Direction::pause;

	mIsGameOver = false;
	mIsRunning = true;
}

void Snake::update() {
	if (mIsPlayingMusic == true) {
		if (Mix_PausedMusic() == 1) {
			Mix_ResumeMusic();
		}
	}
	else {
		Mix_PauseMusic();
	}

	bool isBorder = false;
	
	if (mDirection == Direction::right) {
		if (mXPos < GAMEAREA_MAX_X_INDEX) {
			mXPos += 1;
		}
		else {
			isBorder = true;
		}
	}
	else if (mDirection == Direction::left) {
		if (mXPos > GAMEAREA_MIN_X_INDEX) {
			mXPos -= 1;
		}
		else {
			isBorder = true;
		}
	}
	else if (mDirection == Direction::up) {
		if (mYPos < GAMEAREA_MAX_Y_INDEX) {
			mYPos += 1;
		}
		else {
			isBorder = true;
		}
	}
	else if (mDirection == Direction::down) {
		if (mYPos > GAMEAREA_MIN_Y_INDEX) {
			mYPos -= 1;
		}
		else {
			isBorder = true;
		}
	}
	else if (mDirection == Direction::backward) {
		if (mZPos < GAMEAREA_MAX_Z_INDEX) {
			mZPos += 1;
		}
		else {
			isBorder = true;
		}
	}
	else if (mDirection == Direction::forward) {
		if (mZPos > GAMEAREA_MIN_Z_INDEX) {
			mZPos -= 1;
		}
		else {
			isBorder = true;
		}
	}

	if (isBorder == true) {
		mIsRunning = false;
		mDirection = Direction::pause;
		mIsGameOver = true;
	}


	if (mDirection != Direction::pause) {
		for (int i = 0; i < mSnakeBody.size(); i++) {
			if (mXPos == mSnakeBody[i].x && mYPos == mSnakeBody[i].y && mZPos == mSnakeBody[i].z) {
				mIsRunning = false;
				mDirection = Direction::pause;
				mIsGameOver = true;
				break;
			}
		}
		mSnakeBody.push_front(glm::ivec3(mXPos, mYPos, mZPos));
		
		auto snakeHead = std::make_shared<SnakeModel>();
		snakeHead->init(mXPos, mYPos, mZPos);
		mSnakeModel->push_front(snakeHead);

		if (mFruitXPos == mSnakeBody.front().x && mFruitYPos == mSnakeBody.front().y && mFruitZPos == mSnakeBody.front().z) {
			mScore += 50;
			if (mIsPlayingSound) {
				Mix_PlayChannel(-1, mySound, 0);
			}
			placeFruit();
		}
		else {
			mSnakeBody.pop_back();
			mSnakeModel->pop_back();
		}
	}
}

void Snake::placeFruit() {
	int random_values[3];

	for (int i = 0; i < 3; i++) {
		random_values[i] = std::rand() % 10;
	}

	mFruitXPos = random_values[0];
	mFruitYPos = random_values[1];
	mFruitZPos = random_values[2];

	bool isPlaced;

	do {
		isPlaced = true;
		for (int i = 0; i < mSnakeBody.size(); i++) {
			if (mFruitXPos == mSnakeBody[i].x && mFruitYPos == mSnakeBody[i].y && mFruitZPos == mSnakeBody[i].z) {
				isPlaced = false;
				mFruitXPos++;
				if (mFruitXPos > GAMEAREA_MAX_X_INDEX) {
					mFruitXPos = GAMEAREA_MIN_X_INDEX;
					mFruitZPos++;
					if (mFruitZPos > GAMEAREA_MAX_Z_INDEX) {
						mFruitZPos = GAMEAREA_MIN_Z_INDEX;
						mFruitYPos++;
						if (mFruitYPos > GAMEAREA_MAX_Y_INDEX) {
							mFruitYPos = GAMEAREA_MIN_Y_INDEX;
						}
					}
				}
				break;
			}
		}
	} while (isPlaced == false);

	mFruitModel = std::make_shared<FruitModel>();
	mFruitModel->init(mFruitXPos, mFruitYPos, mFruitZPos);
}
