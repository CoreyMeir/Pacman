#pragma once
// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif

// Just need to include main header file
#include "S2D/S2D.h"
#include "Structure.h"
#include <string>
struct Enemy;
struct Player;

// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;

// Declares the Pacman class which inherits from the Game class.
// This allows us to overload the Game class methods to help us
// load content, draw and update our game.
class Pacman : public Game
{
private:

	//Input methods
	void Input(int elapsedTime, Input::KeyboardState* state, Input::MouseState* mouseState);

	//Check Methods
	void CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey);
	void CheckStart(Input::KeyboardState* state, Input::Keys startKey);
	void CheckViewportCollision();
	void CheckGhostCollisions();
	void CheckCollisionFrightMode();
	void CheckMunchieCollision();
	void CheckCherryCollision();
	void CheckFrightBallCollision();
	void OriginalGhostColours();
	void FrightMode(int elapsedTime);
	void LoadMap();

	//Update Methods
	void UpdatePacman(int elapsedTime);
	void UpdateMunchie(int elapsedTime);
	void UpdateMunchies(int elapsedTime);
	void UpdateCherry(int elapsedTime);
	void UpdateGhost(MovingEnemy*, int elapsedTime);

	int GetSmallestElement(int is[10], int i);

	//Keys data
	Input::Keys pauseKey;
	Input::Keys startKey;

	//Sounds
	SoundEffect* _pop;
	SoundEffect* _pDeath;
	SoundEffect* _eatCherry;
	SoundEffect* _eatGhost;
	SoundEffect* _extraPacman;
	SoundEffect* Intermission;
	SoundEffect* _speedBoost;
	SoundEffect* _frightSound;
	SoundEffect* _gDeath;

	MovingEnemy* _ghosts[GHOSTCOUNT];
	
	// Data to represent Pacman
	Player* _pacman;

	//Data to represent Cherry
	Enemy* _cherry;
	
	// Data to represent Munchie
	Enemy* _munchies[MUNCHIECOUNT];
	Enemy* _munchie;

	//Data to represent fright ball
	Enemy* _frightBall[FRIGHTBALL];

	//Data to represent Menu struct
	Menu* _menu;

	Wall* _walls[WALLCOUNT];
	//Data to represent leaderboard
	Leaderboard* _leaderboard;
	
	// Position for String
	Vector2* _stringPosition;

	//Pacman Title
	Texture2D* _pacmanTitleLabel;
	Rect* _pacmanTitleRectangle;
	Vector2* __pacmanTitleStringPosition;
	
	// Data for start menu
	Texture2D* _startLabel;
	Rect* _startRectangle;
	Vector2* _startStringPosition;
	
	Texture2D* _startHighlightedLabel;
	Rect* _startHighlightedRectangle;
	Vector2* _startHighlightedStringPosition;

	Texture2D* _scoresLabel;
	Rect* _scoresRectangle;
	Vector2* _scoresStringPosition;

	Texture2D* _scoresHighlightedLabel;
	Rect* _scoresHighlightedRectangle;
	Vector2* _scoresHighlightedStringPosition;

	Texture2D* _exitLabel;
	Rect* _exitRectangle;
	Vector2* _exitStringPosition;

	Texture2D* _exitHighlightedLabel;
	Rect* _exitHighlightedRectangle;
	Vector2* _exitHighlightedStringPosition;

	//Pause Menu 
	Texture2D* _pausemenuBackground;
	Rect* _pausemenuRectangle;
	Vector2* _pausemenuStringPosition;

	Texture2D* _pauseLogoLabel;
	Rect* _pauseLogoRectangle;
	Vector2* _pauseLogoStringPosition;

	//Leaderboard Menu
	Texture2D* _leaderboardTitleLabel;
	Rect* _leaderboardTitleRectangle;
	Vector2* _leaderboardTitleStringPosition;

	//Leaderboard screen back button
	Texture2D* _leaderboardBackLabel;
	Rect* _leaderboardBackRectangle;
	Vector2* _leaderboardBackStringPosition;

	//Leaderboard screen back highlighted button
	Texture2D* _leaderboardBackHighlightedLabel;
	Rect* _leaderboardBackHighlightedRectangle;
	Vector2* _leaderboardBackHighlightedStringPosition;

	//Game Over Screen
	Texture2D* _gameoverTitleLabel;
	Rect* _gameoverTitleRectangle;
	Vector2* _gameoverTitleStringPosition;
	
	Texture2D* _gameoverMainMenuLabel;
	Rect* _gameoverMainMenuRectangle;
	Vector2* _gameoverMainMenuStringPosition;

	Texture2D* _gameoverMainMenuHighlightedLabel;
	Rect* _gameoverMainMenuHighlightedRectangle;
	Vector2* _gameoverMainMenuHighlightedStringPosition;

	//Percentage Bar
	Texture2D* _percEmptyLabel;
	Rect* _percEmptyRectangle;
	Vector2* _percEmptyStringPosition;

	Texture2D* _perc1of10Label;
	Rect* _perc1of10Rectangle;
	Vector2* _perc1of10StringPosition;
	
	Texture2D* _perc2of10Label;
	Rect* _perc2of10Rectangle;
	Vector2* _perc2of10StringPosition;

	Texture2D* _perc3of10Label;
	Rect* _perc3of10Rectangle;
	Vector2* _perc3of10StringPosition;

	Texture2D* _perc4of10Label;
	Rect* _perc4of10Rectangle;
	Vector2* _perc4of10StringPosition;

	Texture2D* _perc5of10Label;
	Rect* _perc5of10Rectangle;
	Vector2* _perc5of10StringPosition;

	Texture2D* _perc6of10Label;
	Rect* _perc6of10Rectangle;
	Vector2* _perc6of10StringPosition;

	Texture2D* _perc7of10Label;
	Rect* _perc7of10Rectangle;
	Vector2* _perc7of10StringPosition;

	Texture2D* _perc8of10Label;
	Rect* _perc8of10Rectangle;
	Vector2* _perc8of10StringPosition;

	Texture2D* _perc9of10Label;
	Rect* _perc9of10Rectangle;
	Vector2* _perc9of10StringPosition;

	Texture2D* _percFullLabel;
	Rect* _percFullRectangle;
	Vector2* _percFullStringPosition;
	
	
	
	//Data for other menus
	bool _paused;
	bool randomCherry;
	bool _pKeyDown;
	bool _startscreen;
	bool _RetKeyDown;
	bool _RKeyDown;



public:
	/// <summary> Constructs the Pacman class. </summary>
	Pacman(int argc, char* argv[]);

	/// <summary> Destroys any data associated with Pacman class. </summary>
	virtual ~Pacman();

	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();
	

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	/// <summary> Called every frame - draw game here. </summary>
	void virtual Draw(int elapsedTime);

	
};