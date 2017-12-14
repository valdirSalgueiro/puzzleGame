#include "Engine.h"
#include <vector>

void Engine::init(int width_, int height_) 
{
	width = width_;
	height = height_;
	startBatch(width, height);

	std::vector<int> playerSounds;
	playerSounds.push_back(sounds["fire"]);

	tmxLoader = new TMXLoader();
	player = new Player(tmxLoader);
	items = new Items();
	fireball = new Fireball(tmxLoader);
	gameState = PLAYING;
}

void Engine::update(float time) {
	if (gameState == LOGO1) {
		if (frames > 180) {
			frames = 0;

			gameState = LOGO2;
		}
	}

	else if (gameState == LOGO2) {
		if (frames > 180) {
			frames = 0;

			gameState = TITLE;
		}
	}
	else {
		if (gameState == PLAYING || gameState == GAMEOVER)
			playing(time);
	}
	frames++;
}

void Engine::render(float time) {

	if (gameState == LOGO1) {
	}
	else if (gameState == LOGO2) {
	}
	else {
		spriteBatchBegin();
		tmxLoader->paint();

		EnemyManager::getSingleton()->draw();

		player->draw();

		if (showItems)
			items->draw();

		fireball->draw();

		spriteBatchEnd();
	}
}




void Engine::playing(float time) {
	EnemyManager::getSingleton()->update(2);
	player->update(2);
	fireball->update(2);

	if (player->isAlive && EnemyManager::getSingleton()->collide(player->tileX, player->tileY)) {
		player->die();
	}

	if (fireball->active) {
		Enemy* enemy = EnemyManager::getSingleton()->checkForDeath(fireball->tileX, fireball->tileY);
		if (enemy != NULL) {
			fireball->die(true, enemy->x, enemy->y);
		}
	}
}

void Engine::handleInput(int type, int x, int y) {
	if (type == 1 || type == 6) {
		return;
	}

	if (player != NULL) {
		if (player->fireBall) {
			int tempX = x / 92;
			int tempY = y / 92;
			if (player->tileX == tempX && tempY > player->tileY) {
				fireball->activate(player->tileX, player->tileY, Fireball::DOWN);
				player->fireBall = false;
			}
			if (player->tileX == tempX && tempY < player->tileY) {
				fireball->activate(player->tileX, player->tileY, Fireball::UP);
				player->fireBall = false;
			}
			if (player->tileY == tempY && tempX > player->tileX) {
				fireball->activate(player->tileX, player->tileY, Fireball::RIGHT);
				player->fireBall = false;
			}
			if (player->tileY == tempY && tempX < player->tileX) {
				fireball->activate(player->tileX, player->tileY, Fireball::LEFT);
				player->fireBall = false;
			}

		}
		else if (player->tileX != (int)x / 92 || player->tileY != (int)y / 92) {
			if (!showItems) {
				player->move(x, y);
			}
			else {
				if (x >= 337 && x <= 400
					&& y >= 177 && y <= 242) {//1o item
					player->crossWall = true;
				}
				else if (x >= 400 && x <= 463
					&& y >= 177 && y <= 242) {//2o item
					player->jumpTile = true;
				}
				else if (x >= 337 && x <= 400
					&& y >= 242 && y <= 303) {//3o item
					fireball->active = false;
					player->fireBall = true;
				}
				else if (x >= 400 && x <= 463
					&& y >= 242 && y <= 303) {//4o item
				}
				showItems = false;
			}

		}
		else {
			if (player->player_state == Player::STOPPED) {
				showItems = true;
			}
		}
	}
}
