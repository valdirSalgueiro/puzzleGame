#ifndef ENGINE_H
#define ENGINE_H

#ifdef _WIN32

// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

#include <SDKDDKVer.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#elif __ANDROID__

#include <jni.h>
#include <errno.h>

#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

#include <android/log.h>

#endif

#include "core/gl2d.h"
#include "Vector2D.h"
#include <map>

#include "TMXLoader.h"
#include "Player.h"
#include "Items.h"
#include "fireball.h"
#include "EnemyManager.h"

class Engine{
public:

	enum DIRECTION{
		RIGHT = 1<<0,
		LEFT  = 1<<1,
		UP = 1<<2,
		DOWN = 1<<3
	};

	enum STATE {
		LOGO1,
		LOGO2,
		TITLE,
		INSTRUCT,
		STARTER,
		PLAYING,
		GAMEOVER
	};

	void init(int, int);
	void update(float);
	void render(float);

	void playing(float);

	void handleInput(int, int, int);

	STATE gameState;

private:	
	bool touch;
	int width, height;

	Player* player;
	Items* items;
	Fireball* fireball;
	bool showItems;

	std::map<std::string, int> sounds;

	TMXLoader* tmxLoader;

	int frames;

};


#endif