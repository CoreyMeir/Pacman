#pragma once
#define MUNCHIECOUNT 50
#define GHOSTCOUNT 4
#define CHERRYCOUNT 1
#define FRIGHTBALL 4
#define WALLCOUNT 400
// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#endif

// Just need to include main header file
#include "S2D/S2D.h"
#include <string>


// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;

//Structure Definition
struct Player
{
	float speedMultiplier;
	float speedBoostTimer;
	float maxSpeedBoost;
	float speedBoostCooldownCounter;
	float maxSpeedBoostCooldown;
	bool speedBoost;
	bool rechargingBoost;
	int currentFrameTime;
	int direction;
	int frame;
	int size;
	float pSpeed;
	int cFrameTime;
	bool isMoving;
	Rect* sourceRect;
	Texture2D* texture;
	Vector2* position;
	int mapSizeX;
	int mapSizeY;
	bool isAlive;
	bool killable;
	
};

struct Enemy
{
	int FrameCount;
	int frame;
	int CurrentFrameTime;
	bool resetCooldown;
	float resetTimer;
	float cFrameTime;
	Rect* sourceRect;
	Texture2D* Texture;
	Texture2D* InvertedTexture;
	Vector2* position;
	bool isAlive;

};

struct MovingEnemy
{
	
	Vector2* position;
	Texture2D* texture;
	Rect* sourceRect;
	int direction;
	int FrameCount;
	int moveTimer;
	int size;
	int frame;
	int CurrentFrameTime;
	float speed;
	bool killable;
	bool frightMode;
	bool isAlive;
	float frightTimer;
	float maxFrightTime;
	float cFrameTime;
	string name;
	Texture2D* blueGhost;
	Texture2D* redGhost;
	Texture2D* pinkGhost;
	Texture2D* orangeGhost;
	Texture2D* frightTexture1;
	Texture2D* frightTexture2;
};

struct Menu
{
	bool gameOver;
	int score;
	int munchieCounter;
	int ghostCounter;
	float ghostFrightTimer;
	int ghostFrightStage;
	bool ghostFrightMode;
	int maxMunchieCounter;
	int pacmanCount;
	int wallCount;
	bool paused;
	bool playing;
	bool startScreen;
	bool leaderboardScreen;
	bool startButtonHover;
	bool scoresButtonHover;
	bool exitButtonHover;
	bool leaderboardBackHover;
	bool gameoverMainMenuHover;
	bool gameOverScreen;
	int munchCount;
	Vector2* leader;
	int map;
	

	string mapSize[24][32]; //    768/32 = 24 and 1024(window size)/32 = 32
	
};

struct Leaderboard
{
	string playerName;
	int score;
	bool leaderboardHighToLow;
};

struct Wall
{
	Vector2* Position;
	Rect* sourceRect;
	Texture2D* Texture;
};
