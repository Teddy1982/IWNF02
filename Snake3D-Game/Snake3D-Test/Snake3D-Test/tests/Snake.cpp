#include "Snake.h"

#include <ctime>

#include "..\opengl\OGLRenderData.h"
#include "..\tools\Logger.h"

const int GAMEAREA_MIN_X_INDEX = 0;
const int GAMEAREA_MIN_Y_INDEX = 0;
const int GAMEAREA_MIN_Z_INDEX = 0;

const int GAMEAREA_MAX_X_INDEX = 9;
const int GAMEAREA_MAX_Y_INDEX = 9;
const int GAMEAREA_MAX_Z_INDEX = 9;

Snake::Snake() {
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		Logger::log(1, "%s error: could not init SDL_AUDIO\n", __FUNCTION__);
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		Logger::log(1, "%s error: could not init Mix_OpenAudio\n", __FUNCTION__);
	}

	mySound = Mix_LoadWAV("audio/background_music.mp3");
	Mix_PlayChannel(-1, mySound, 0);  // -1 = erster freier Kanal
}

Snake::~Snake() {
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

	mIsRunning = true;
}

void Snake::update() {
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
	}


	if (mDirection != Direction::pause) {
		for (int i = 0; i < mSnakeBody.size(); i++) {
			if (mXPos == mSnakeBody[i].x && mYPos == mSnakeBody[i].y && mZPos == mSnakeBody[i].z) {
				mIsRunning = false;
				mDirection = Direction::pause;
				break;
			}
		}
		mSnakeBody.push_front(glm::ivec3(mXPos, mYPos, mZPos));
		
		auto snakeHead = std::make_shared<SnakeModel>();
		snakeHead->init(mXPos, mYPos, mZPos);
		mSnakeModel->push_front(snakeHead);

		if (mFruitXPos == mSnakeBody.front().x && mFruitYPos == mSnakeBody.front().y && mFruitZPos == mSnakeBody.front().z) {
			mScore += 50;
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

