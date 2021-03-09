#include "Pacman.h"
#include "Structure.h"
#include <sstream>
#include <fstream>
#include <time.h>
#include <vector>
#include <iostream>

//debug

//Constructor method
Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv)
{
	srand(time(NULL));


	//Initialise Member variables
	_cherry = new Enemy();
	//Assigning values to variables
	_cherry->FrameCount = 0;
	_cherry->cFrameTime = 500;
	_cherry->CurrentFrameTime = 0;
	_cherry->resetTimer = 0;
	_cherry->frame = 300; //Changed from const int to a pointer which has a value assigned to it


	//Initialise Member variables
	_pacman = new Player();
	_pacman->currentFrameTime = 0;
	_pacman->frame = 0;
	_pacman->direction = 4;
	_pacman->speedMultiplier = 1.0f;
	_pacman->speedBoostTimer = 0;
	_pacman->maxSpeedBoost = 100;
	_pacman->maxSpeedBoostCooldown = 400;
	_pacman->speedBoost = false;
	_pacman->rechargingBoost = false;
	_pacman->isMoving = false;
	_pacman->pSpeed = 0.15f;
	_pacman->cFrameTime = 250;
	_pacman->size = 32;
	_pacman->isAlive = true;
	_pacman->killable = true;


	//Initialise Member variable
	_menu = new Menu();
	_menu->gameOver = false;
	_menu->munchieCounter = 0;
	_menu->ghostCounter = 0;
	_menu->pacmanCount = 3;
	_menu->maxMunchieCounter = 1;
	_menu->paused = false;
	_menu->ghostFrightTimer = 0;
	_menu->ghostFrightStage = 0;
	_menu->ghostFrightMode = false;
	_pKeyDown = false;
	_menu->startScreen = true;
	_menu->playing = false;
	_menu->leaderboardScreen = false;
	_menu->gameoverMainMenuHover = false;
	_menu->gameOverScreen = false;
	_menu->munchCount = MUNCHIECOUNT;
	_menu->startButtonHover = false;
	_menu->scoresButtonHover = false;
	_menu->exitButtonHover = false;
	_menu->leaderboardBackHover = false;

	//_RetKeyDown = false;
	randomCherry = true;

	//Initialise leaderboard
	_leaderboard = new Leaderboard();
	_leaderboard->score = 0;
	_leaderboard->leaderboardHighToLow = false;
	string name;
	cout << "Please enter your name: " << endl;
	getline(cin, name);
	_leaderboard->playerName = name;

	//local variable
	int i;
	//Initialise munchie
	for (i = 0; i < MUNCHIECOUNT; i++)
	{
		_munchies[i] = new Enemy();
		_munchies[i]->CurrentFrameTime = 0;
		_munchies[i]->frame = rand() % 500 + 50;
		_munchies[i]->FrameCount = rand() % 1;
		_munchies[i]->isAlive = true;
	}

	for (int i = 0; i < FRIGHTBALL; i++)
	{
		_frightBall[i] = new Enemy();
		_frightBall[i]->isAlive = true;
	}

	//Initialise Ghost
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_ghosts[i] = new MovingEnemy();
		_ghosts[i]->direction = 0;
		_ghosts[i]->speed = 0.2f;
		_ghosts[i]->killable = false;
		_ghosts[i]->frightTimer = 0;
		_ghosts[i]->maxFrightTime = 3000;
		_ghosts[i]->isAlive = true;
		_ghosts[i]->FrameCount = 0;
		_ghosts[i]->moveTimer = 0;
		_ghosts[i]->size = 20;
		_ghosts[i]->frame = 1500;
		_ghosts[i]->cFrameTime = 1500;
		_ghosts[i]->CurrentFrameTime = 0;
	}

	//Sounds
	_pop = new SoundEffect();
	_pDeath = new SoundEffect();
	_eatCherry = new SoundEffect();
	_eatGhost = new SoundEffect();
	_extraPacman = new SoundEffect();
	Intermission = new SoundEffect();
	_speedBoost = new SoundEffect();
	_frightSound = new SoundEffect();
	_gDeath = new SoundEffect();


	Audio::Initialise();
	if (!Audio::IsInitialised())
	{
		cout << "Audio is not initialised" << endl;
	}
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Pacman", 60);
	Input::Initialise();

	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();
}

Pacman::~Pacman()
{

	//Clean up the Texture
	//delete _munchies[0]->Texture;

	int nCount = 0;
	for (nCount = 0; nCount < MUNCHIECOUNT; nCount++)
	{
		delete _munchies[nCount]->position;
		delete _munchies[nCount]->sourceRect;
		delete _munchies[nCount];
		delete _munchies[nCount]->Texture;
		delete _munchies[nCount]->InvertedTexture;
		delete _munchies[nCount]->sourceRect;
	}

	for (nCount = 0; nCount < FRIGHTBALL; nCount++)
	{
		delete _frightBall[nCount]->position;
		delete _frightBall[nCount]->sourceRect;
		delete _frightBall[nCount];
		delete _frightBall[nCount]->Texture;
	}


	for (nCount = 0; nCount < GHOSTCOUNT; nCount++)
	{
		delete _ghosts[nCount]->position;
		delete _ghosts[nCount]->sourceRect;
		delete _ghosts[nCount]->texture;
		delete _ghosts[nCount]->blueGhost;
		delete _ghosts[nCount]->orangeGhost;
		delete _ghosts[nCount]->pinkGhost;
		delete _ghosts[nCount]->redGhost;
		delete _ghosts[nCount]->frightTexture1;
		delete _ghosts[nCount]->frightTexture2;
		delete _ghosts[nCount];
	}
	//Order of operations is important, array deleted last
	delete[] _munchies;

	delete _pacman->position;
	delete _pacman->texture;
	delete _pacman->sourceRect;
	delete _pacman;

	delete _cherry->Texture;
	delete _cherry->InvertedTexture;
	delete _cherry->sourceRect;

	//Pacman Title
	delete _pacmanTitleLabel;
	delete _pacmanTitleRectangle;
	delete __pacmanTitleStringPosition;

	//Pause Menu
	delete _pausemenuBackground;
	delete _pausemenuRectangle;
	delete _pausemenuStringPosition;

	//Start Button
	delete _startLabel;
	delete _startRectangle;
	delete _startStringPosition;

	//Start Highlighted Button
	delete _startHighlightedLabel;
	delete _startHighlightedRectangle;
	delete _startHighlightedStringPosition;

	//Exit Button
	delete _exitLabel;
	delete _exitRectangle;
	delete _exitStringPosition;

	//Exit Highlighted Button
	delete _exitHighlightedLabel;
	delete _exitHighlightedRectangle;
	delete _exitHighlightedStringPosition;

	//Scores Button
	delete _scoresLabel;
	delete _scoresRectangle;
	delete _scoresStringPosition;

	//Scores highlighted
	delete _scoresHighlightedLabel;
	delete _scoresHighlightedRectangle;
	delete _scoresHighlightedStringPosition;

	//Paused Label
	delete _pauseLogoLabel;
	delete _pauseLogoRectangle;
	delete _pauseLogoStringPosition;

	//Leaderboard Menu
	delete _leaderboardTitleLabel;
	delete _leaderboardTitleRectangle;
	delete _leaderboardTitleStringPosition;

	//Leaderboard Back Button
	delete _leaderboardBackLabel;
	delete _leaderboardBackRectangle;
	delete _leaderboardBackStringPosition;

	//Leaderboard Back Highlighted Button 
	delete _leaderboardBackHighlightedLabel;
	delete _leaderboardBackHighlightedRectangle;
	delete _leaderboardBackHighlightedStringPosition;

	//Game Over Buttons
	delete _gameoverTitleLabel;
	delete _gameoverTitleRectangle;
	delete _gameoverTitleStringPosition;

	delete _gameoverMainMenuLabel;
	delete _gameoverMainMenuRectangle;
	delete _gameoverMainMenuStringPosition;

	delete _gameoverMainMenuHighlightedLabel;
	delete _gameoverMainMenuHighlightedRectangle;
	delete _gameoverMainMenuHighlightedStringPosition;

	//Percentage Bar
	delete _percEmptyLabel;
	delete _percEmptyRectangle;
	delete _percEmptyStringPosition;

	delete _perc1of10Label;
	delete _perc1of10Rectangle;
	delete _perc1of10StringPosition;

	delete _perc2of10Label;
	delete _perc2of10Rectangle;
	delete _perc2of10StringPosition;

	delete _perc3of10Label;
	delete _perc3of10Rectangle;
	delete _perc3of10StringPosition;

	delete _perc4of10Label;
	delete _perc4of10Rectangle;
	delete _perc4of10StringPosition;

	delete _perc5of10Label;
	delete _perc5of10Rectangle;
	delete _perc5of10StringPosition;

	delete _perc6of10Label;
	delete _perc6of10Rectangle;
	delete _perc6of10StringPosition;

	delete _perc7of10Label;
	delete _perc7of10Rectangle;
	delete _perc7of10StringPosition;

	delete _perc8of10Label;
	delete _perc8of10Rectangle;
	delete _perc8of10StringPosition;

	delete _perc9of10Label;
	delete _perc9of10Rectangle;
	delete _perc9of10StringPosition;

	delete _percFullLabel;
	delete _percFullRectangle;
	delete _percFullStringPosition;



	//Sounds
	delete _pop;
	delete _pDeath;
	delete _eatCherry;
	delete _eatGhost;
	delete _extraPacman;
	delete Intermission;
	delete _speedBoost;
	delete _frightSound;
	delete _gDeath;
}

//void Pacman::LoadMap()
//{
//	
//	
//		fstream inFile("Map1.txt"); // Opens file
//		if (inFile) // If it can be opened
//		{
//			
//			int lineNum = -1;
//			string line;
//
//
//			// Creates and loads textures
//			Texture2D* munchie = new Texture2D();
//			munchie->Load("Textures/Munchie.png", true);
//			Texture2D* wall = new Texture2D();
//			wall->Load("Textures/FullWall.png", false);
//			Texture2D* pacman = new Texture2D();
//			pacman->Load("Textures/Pacman.png", false);
//
//
//			while (getline(inFile, line)) // Loops through every line in the file
//			{
//				lineNum++;
//				string a;
//				a = line;
//				for (int i = 0; i < a.length(); i++) // Loops through every character in the line
//				{
//					clog << "For Loop" << endl;
//					if (a[i] == 'G') // If the character is G creates a ghost
//					{
//						clog << "ghost error" << endl;
//						_ghosts[_menu->ghostCounter]->sourceRect = new Rect(0.0f, 0.0f, 32, 32);
//						_ghosts[_menu->ghostCounter]->position = new Vector2((32 * i), (32 * lineNum));
//						_ghosts[_menu->ghostCounter]->killable = false;
//						_menu->ghostCounter++;
//						_menu->mapSize[lineNum][i] = "-";
//					}
//					if (a[i] == 'P') // If the character is P creates Pacman
//					{
//						_pacman->texture = new Texture2D();
//						_pacman->texture = pacman;
//						_pacman->position = new Vector2((32 * i), (32 * lineNum));
//						_pacman->sourceRect = new Rect(0.0f, 0.0f, 32, 32);
//						_pacman->mapSizeX = _pacman->position->X / 32;
//						_pacman->mapSizeX = _pacman->position->Y / 32;
//						_menu->mapSize[lineNum][i] = "-";
//					}
//					if (a[i] == '-') // If the character is a - creates a munchie
//					{
//						_munchies[_menu->munchieCounter] = new Enemy();
//						_munchies[_menu->munchieCounter]->frame = rand() % 500 + 250;
//						_munchies[_menu->munchieCounter]->CurrentFrameTime = 0;
//						_munchies[_menu->munchieCounter]->FrameCount = rand() % 1;
//						_munchies[_menu->munchieCounter]->Texture = munchie;
//						_munchies[_menu->munchieCounter]->sourceRect = new Rect(0, 0, 12, 12);
//						_munchies[_menu->munchieCounter]->position = new Vector2(((32 * i) + 10), ((32 * lineNum) + 10));
//						_munchies[_menu->munchieCounter]->isAlive = true;
//						_menu->munchieCounter++;
//						_menu->mapSize[lineNum][i] = "-";
//					}
//					if (a[i] == 'f') // If the character is a f, it will create a frightball
//					{
//						_munchies[_menu->munchieCounter] = new Enemy();
//						_frightBall[i]->Texture = new Texture2D();
//						_frightBall[i]->Texture->Load("Textures/frightModeBall.png", false);
//						_munchies[_menu->munchieCounter]->sourceRect = new Rect(0, 0, 32, 32);
//						_munchies[_menu->munchieCounter]->position = new Vector2(((32 * i) + 10), ((32 * lineNum) + 10));
//						_munchies[_menu->munchieCounter]->isAlive = true;
//						_menu->munchieCounter++;
//						_menu->mapSize[lineNum][i] = "-";
//					}
//					//if (a[i] == 'X') // If the character is X creates a wall
//					//{
//					//	_walls[_menu->wallCount] = new Wall();
//					//	_walls[_menu->wallCount]->Texture = wall;
//					//	_walls[_menu->wallCount]->sourceRect = new Rect(0, 0, 32, 32);
//					//	_walls[_menu->wallCount]->Position = new Vector2((32 * i), (32 * lineNum));
//					//	_menu->wallCount++;
//					//	_menu->mapSize[lineNum][i] = "X";
//					//}
//					
//				}
//			}
//		}
//		else // If it cannot be opened
//		{
//			clog << "Error" << endl;
//			exit(88);
//		}
//
//		
//		
//}



void Pacman::LoadContent()
{
	 //Load Pacman
	_pacman->texture = new Texture2D();
	_pacman->texture->Load("Textures/Pacman.tga", false);
	_pacman->position = new Vector2(350.0f, 350.0f);
	_pacman->sourceRect = new Rect(0, 0, 32, 32);
	_pacman->mapSizeX = _pacman->position->X / 32;
	_pacman->mapSizeY = _pacman->position->Y / 32;

	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		//_menu->munchieCounter
		_munchies[i] = new Enemy();
		_munchies[i]->CurrentFrameTime = 0;
		_munchies[i]->frame = rand() % 500 + 50;
		_munchies[i]->FrameCount = rand() % 1;
		_munchies[i]->Texture = new Texture2D();
		_munchies[i]->Texture->Load("Textures/Munchie.tga", false);
		_munchies[i]->InvertedTexture = new Texture2D();
		_munchies[i]->InvertedTexture->Load("Textures/MunchieInverted.tga", true);
		_munchies[i]->sourceRect = new Rect(0, 0, 12, 12);
		_munchies[i]->position = new Vector2((rand() % Graphics::GetViewportWidth()),
		                                     (rand() % Graphics::GetViewportHeight()));
	}

	for (int i = 0; i < FRIGHTBALL; i++)
	{
		_frightBall[i]->Texture = new Texture2D();
		_frightBall[i]->Texture->Load("Textures/frightModeBall.png", false);
		_frightBall[i]->sourceRect = new Rect(0, 0, 32, 32);
		_frightBall[i]->position = new Vector2((rand() % Graphics::GetViewportWidth()),
		                                       (rand() % Graphics::GetViewportHeight()));
	}


	//Initialise ghost character
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_ghosts[i]->blueGhost = new Texture2D();
		_ghosts[i]->blueGhost->Load("Textures/GhostBlue.png", false);
		_ghosts[i]->orangeGhost = new Texture2D();
		_ghosts[i]->orangeGhost->Load("Textures/GhostOrange.png", false);
		_ghosts[i]->pinkGhost = new Texture2D();
		_ghosts[i]->pinkGhost->Load("Textures/GhostPink.png", false);
		_ghosts[i]->redGhost = new Texture2D();
		_ghosts[i]->redGhost->Load("Textures/GhostRed.png", false);
		_ghosts[i]->frightTexture1 = new Texture2D();
		_ghosts[i]->frightTexture1->Load("Textures/GhostFright.png", false);
		_ghosts[i]->frightTexture2 = new Texture2D();
		_ghosts[i]->frightTexture2->Load("Textures/GhostFright2.png", false);


		if (i == 0)
		{
			_ghosts[i]->texture = _ghosts[i]->blueGhost;
			_ghosts[i]->name = "Inky";
		}
		if (i == 1)
		{
			_ghosts[i]->texture = _ghosts[i]->orangeGhost;
			_ghosts[i]->name = "Clyde";
		}
		if (i == 2)
		{
			_ghosts[i]->texture = _ghosts[i]->pinkGhost;
			_ghosts[i]->name = "Pinky";
		}
		if (i == 3)
		{
			_ghosts[i]->texture = _ghosts[i]->redGhost;
			_ghosts[i]->name = "Blinky";
		}
	}

	//TEMPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_ghosts[_menu->ghostCounter]->sourceRect = new Rect(0.0f, 0.0f, 20, 20);
		_ghosts[_menu->ghostCounter]->position = new Vector2((rand() % Graphics::GetViewportWidth()),
		                                                     (rand() % Graphics::GetViewportHeight()));
		_menu->ghostCounter++;
	}


	//Load Cherry
	_cherry->Texture = new Texture2D();
	_cherry->Texture->Load("Textures/Cherry.png", true);
	_cherry->InvertedTexture = new Texture2D();
	_cherry->InvertedTexture->Load("Textures/CherryInverted.png", true);
	_cherry->sourceRect = new Rect(250.0f, 250.0f, 24, 24);
	_cherry->position = new Vector2(150.0f, 150.0f);

	// Set string position
	_stringPosition = new Vector2(10.0f, 25.0f);

	//Set pause menu parameters
	_pausemenuBackground = new Texture2D();
	_pausemenuBackground->Load("Textures/Transparency.png", false);
	_pausemenuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_pausemenuStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);

	//Pacman Title For Main Menu
	_pacmanTitleLabel = new Texture2D();
	_pacmanTitleLabel->Load("Textures/PacmanTitle.png", false);
	_pacmanTitleRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	__pacmanTitleStringPosition = new
		Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);

	//Start Button
	_startLabel = new Texture2D();
	_startLabel->Load("Textures/PacmanStart.png", false);
	_startRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_startStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);

	_startHighlightedLabel = new Texture2D();
	_startHighlightedLabel->Load("Textures/PacmanStartHighlighted.png", false);
	_startHighlightedRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_startHighlightedStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
	                                              Graphics::GetViewportHeight() / 2.0f);

	//Scores Button
	_scoresLabel = new Texture2D();
	_scoresLabel->Load("Textures/PacmanScores.png", false);
	_scoresRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_scoresStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);

	_scoresHighlightedLabel = new Texture2D();
	_scoresHighlightedLabel->Load("Textures/PacmanScoresHighlighted.png", false);
	_scoresHighlightedRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_scoresHighlightedStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
	                                               Graphics::GetViewportHeight() / 2.0f);

	//Exit Button
	_exitLabel = new Texture2D();
	_exitLabel->Load("Textures/PacmanExit.png", false);
	_exitRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_exitStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);

	_exitHighlightedLabel = new Texture2D();
	_exitHighlightedLabel->Load("Textures/PacmanExitHighlighted.png", false);
	_exitHighlightedRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_exitHighlightedStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
	                                             Graphics::GetViewportHeight() / 2.0f);

	//Pause Label
	_pauseLogoLabel = new Texture2D();
	_pauseLogoLabel->Load("Textures/PacmanPaused.png", false);
	_pauseLogoRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_pauseLogoStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);

	//Leaderboard Menu
	_leaderboardTitleLabel = new Texture2D();
	_leaderboardTitleLabel->Load("Textures/PacmanLeaderboardTitle.png", false);
	_leaderboardTitleRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_leaderboardTitleStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
	                                              Graphics::GetViewportHeight() / 2.0f);

	//Leaderboard Back Button
	_leaderboardBackLabel = new Texture2D();
	_leaderboardBackLabel->Load("Textures/PacmanLeaderboardBack.png", false);
	_leaderboardBackRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());;
	_leaderboardBackStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
	                                             Graphics::GetViewportHeight() / 2.0f);

	//Leaderboard Back Highlighted Button
	_leaderboardBackHighlightedLabel = new Texture2D();
	_leaderboardBackHighlightedLabel->Load("Textures/PacmanLeaderboardBackHighlighted.png", false);
	_leaderboardBackHighlightedRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(),
	                                                Graphics::GetViewportHeight());
	_leaderboardBackHighlightedStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
	                                                        Graphics::GetViewportHeight() / 2.0f);

	//Game Over
	_gameoverTitleLabel = new Texture2D();
	_gameoverTitleLabel->Load("Textures/PacmanGameOver.png", false);
	_gameoverTitleRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_gameoverTitleStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
	                                           Graphics::GetViewportHeight() / 2.0f);

	_gameoverMainMenuLabel = new Texture2D();
	_gameoverMainMenuLabel->Load("Textures/PacmanGOMainMenu.png", false);
	_gameoverMainMenuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_gameoverMainMenuStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
	                                              Graphics::GetViewportHeight() / 2.0f);

	_gameoverMainMenuHighlightedLabel = new Texture2D();
	_gameoverMainMenuHighlightedLabel->Load("Textures/PacmanGOMainMenuHighlighted.png", false);
	_gameoverMainMenuHighlightedRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(),
	                                                 Graphics::GetViewportHeight());
	_gameoverMainMenuHighlightedStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
	                                                 Graphics::GetViewportHeight() / 2.0f);


	//Percentage Bar
	_percEmptyLabel = new Texture2D();
	_percEmptyLabel->Load("Textures/SpeedboostEmpty.png", false);
	_percEmptyRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(),
		Graphics::GetViewportHeight());
	_percEmptyStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
		Graphics::GetViewportHeight() / 2.0f);

	_perc1of10Label = new Texture2D();
	_perc1of10Label->Load("Textures/Speedboost1of10.png", false);
	_perc1of10Rectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(),
		Graphics::GetViewportHeight());
	_perc1of10StringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
		Graphics::GetViewportHeight() / 2.0f);

	_perc2of10Label = new Texture2D();
	_perc2of10Label->Load("Textures/Speedboost2of10.png", false);
	_perc2of10Rectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(),
		Graphics::GetViewportHeight());
	_perc2of10StringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
		Graphics::GetViewportHeight() / 2.0f);

	_perc3of10Label = new Texture2D();
	_perc3of10Label->Load("Textures/Speedboost3of10.png", false);
	_perc3of10Rectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(),
		Graphics::GetViewportHeight());
	_perc3of10StringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
		Graphics::GetViewportHeight() / 2.0f);

	_perc4of10Label = new Texture2D();
	_perc4of10Label->Load("Textures/Speedboost4of10.png", false);
	_perc4of10Rectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(),
		Graphics::GetViewportHeight());
	_perc4of10StringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
		Graphics::GetViewportHeight() / 2.0f);

	_perc5of10Label = new Texture2D();
	_perc5of10Label->Load("Textures/Speedboost5of10.png", false);
	_perc5of10Rectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(),
		Graphics::GetViewportHeight());
	_perc5of10StringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
		Graphics::GetViewportHeight() / 2.0f);

	_perc6of10Label = new Texture2D();
	_perc6of10Label->Load("Textures/Speedboost6of10.png", false);
	_perc6of10Rectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(),
		Graphics::GetViewportHeight());
	_perc6of10StringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
		Graphics::GetViewportHeight() / 2.0f);

	_perc7of10Label = new Texture2D();
	_perc7of10Label->Load("Textures/Speedboost7of10.png", false);
	_perc7of10Rectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(),
		Graphics::GetViewportHeight());
	_perc7of10StringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
		Graphics::GetViewportHeight() / 2.0f);

	_perc8of10Label = new Texture2D();
	_perc8of10Label->Load("Textures/Speedboost8of10.png", false);
	_perc8of10Rectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(),
		Graphics::GetViewportHeight());
	_perc8of10StringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
		Graphics::GetViewportHeight() / 2.0f);

	_perc9of10Label = new Texture2D();
	_perc9of10Label->Load("Textures/Speedboost9of10.png", false);
	_perc9of10Rectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(),
		Graphics::GetViewportHeight());
	_perc9of10StringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
		Graphics::GetViewportHeight() / 2.0f);

	_percFullLabel = new Texture2D();
	_percFullLabel->Load("Textures/SpeedboostFull.png", false);
	_percFullRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(),
		Graphics::GetViewportHeight());
	_percFullStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
		Graphics::GetViewportHeight() / 2.0f);
	



	
	//Leaderboard
	//_menu->leader = new Vector2(Graphics::GetViewportWidth() / 2 - 50, 150);

	//Sounds
	_pop->Load("Sounds/pop.wav");
	_pDeath->Load("Sounds/pacmanDeath.wav");
	_eatCherry->Load("Sounds/eatCherry.wav");
	_eatGhost->Load("Sounds/eatGhost.wav");;
	_extraPacman->Load("Sounds/extraPacman.wav");;
	Intermission->Load("Sounds/Intermission.wav");;
	_speedBoost->Load("Sounds/speedBoost.wav");
	_frightSound->Load("Sounds/frightModeSound.wav");
	_gDeath->Load("Sounds/ghostDeath.wav");
}


void Pacman::Update(int elapsedTime)
{
	// Gets the current state of the keyboard
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
	//Gets the current state of the mouse
	Input::MouseState* mouseState = Input::Mouse::GetState();
	CheckPaused(keyboardState, pauseKey);
	if (!_menu->paused)
	{
		
		CheckStart(keyboardState, startKey);
		//LoadMap();
		Input(elapsedTime, keyboardState, mouseState);
		UpdatePacman(elapsedTime);

		// Loop through array of ghosts here and pass in ghost at index i
		for (int i = 0; i < GHOSTCOUNT; i++)
		{
			UpdateGhost(_ghosts[i], elapsedTime);
		}
		// Gets the current state of the keyboard

		CheckGhostCollisions();
		UpdateCherry(elapsedTime);
		UpdateMunchie(elapsedTime);
		CheckFrightBallCollision();
		CheckCherryCollision();
		CheckMunchieCollision();
		CheckViewportCollision();
		FrightMode(elapsedTime);
	}
}

void Pacman::UpdatePacman(int elapsedTime)
{
	//Keeping track of how much time has elapsed since the last Update() ran
	_pacman->currentFrameTime += elapsedTime;


	//Changing pacmans visual direction

	if (_pacman->isMoving && _pacman->isAlive)
	{
		if (_pacman->direction == 4) //D Key
		{
			_pacman->position->X += _pacman->pSpeed * elapsedTime * _pacman->speedMultiplier; //Moves Pacman right
			_pacman->sourceRect->Y = _pacman->sourceRect->Height * _pacman->direction;
			_pacman->sourceRect->X = _pacman->sourceRect->Width * _pacman->frame;
		}
		else if (_pacman->direction == 1) //S Key
		{
			_pacman->position->Y += _pacman->pSpeed * elapsedTime * _pacman->speedMultiplier; //Moves Pacman down
			_pacman->sourceRect->Y = _pacman->sourceRect->Height * _pacman->direction;
			_pacman->sourceRect->X = _pacman->sourceRect->Width * _pacman->frame;
		}
		else if (_pacman->direction == 2) //A Key
		{
			_pacman->position->X -= _pacman->pSpeed * elapsedTime * _pacman->speedMultiplier; //Moves Pacman left
			_pacman->sourceRect->Y = _pacman->sourceRect->Height * _pacman->direction;
			_pacman->sourceRect->X = _pacman->sourceRect->Width * _pacman->frame;
		}
		else if (_pacman->direction == 3) //W Key
		{
			_pacman->position->Y -= _pacman->pSpeed * elapsedTime * _pacman->speedMultiplier; //Moves Pacman up
			_pacman->sourceRect->Y = _pacman->sourceRect->Height * _pacman->direction;
			_pacman->sourceRect->X = _pacman->sourceRect->Width * _pacman->frame;
		}


		if (_pacman->currentFrameTime > _pacman->cFrameTime)
		{
			_pacman->frame++;
			if (_pacman->frame >= 2)
				_pacman->frame = 0;

			_pacman->currentFrameTime = 0;
		}

		if (_pacman->speedBoost)
		{
			_pacman->speedBoostTimer++;
		}
	}
	else
	{
		_pacman->sourceRect->X = 0;
		_pacman->isMoving = false;
	}
}

void Pacman::UpdateMunchie(int elapsedTime)
{
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		_munchies[i]->CurrentFrameTime += elapsedTime;

		if (_munchies[i]->CurrentFrameTime > _munchies[i]->frame)
		{
			_munchies[i]->FrameCount++;
			
			if (_munchies[i]->FrameCount >= 2)
				_munchies[i]->FrameCount = 0;

			_munchies[i]->CurrentFrameTime = 0;
		}
	}
}

void Pacman::UpdateCherry(int elapsedTime)
{
	_cherry->CurrentFrameTime += elapsedTime;

	if (_cherry->CurrentFrameTime > _cherry->frame)
	{
		_cherry->FrameCount++;
		if (_cherry->FrameCount >= 2)
			_cherry->FrameCount = 0;

		_cherry->CurrentFrameTime = 0;
	}
}

void Pacman::UpdateGhost(MovingEnemy* ghost, int elapsedTime)
{
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_ghosts[i]->CurrentFrameTime += elapsedTime;

		if (_ghosts[i]->CurrentFrameTime > _ghosts[i]->frame)
		{
			_ghosts[i]->FrameCount++;

			if (_ghosts[i]->FrameCount >= 2)
				_ghosts[i]->FrameCount = 0;

			_ghosts[i]->CurrentFrameTime = 0;
		}
	}

	
	int windWidth = Graphics::GetViewportWidth();
	int windHeight = Graphics::GetViewportHeight();

		if (ghost->direction == 0) //Moves Right 
		{
			ghost->position->X += ghost->speed * elapsedTime;
		}
		else if (ghost->direction == 1) //Moves Left 
		{
			ghost->position->X -= ghost->speed * elapsedTime;
		}
		else if (ghost->direction == 3)
		{
			ghost->position->Y += ghost->speed * elapsedTime; //Moves downwards
			
		}
		else if (ghost->direction == 4)
		{
			ghost->position->Y -= ghost->speed * elapsedTime; //Moves up
			
		}

		int randNum = rand() % 4 + 1;
	
		if (ghost->FrameCount == 0)
		{
			ghost->direction = randNum;
		}
		if (ghost->FrameCount > 1000)
		{
			ghost->direction = randNum;
			ghost->FrameCount = 0;
		}
		
	
		if (ghost->position->X + ghost->sourceRect->Width >= windWidth) //Hits Right edge 
		{
			ghost->direction = 1; //Change direction 
		}
		else if (ghost->position->X <= 0) //Hits left edge 
		{
			ghost->direction = 0; //Change direction 
		}
		else if (ghost->position->Y + ghost->sourceRect->Height >= windHeight)
		{
			
			ghost->direction = 4;
		}
		else if (ghost->position->Y < 0)
		{
			ghost->direction = 3;
		}

	
}

void Pacman::CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey)
{
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
	if (!_menu->startScreen || !_menu->gameOverScreen)
	{
		//Checks to see if P key is pressed
		if (keyboardState->IsKeyDown(Input::Keys::P) && !_pKeyDown)
		{
			_pKeyDown = true;
			_menu->paused = !_menu->paused;
		}
		if (keyboardState->IsKeyUp(Input::Keys::P))
		{
			_pKeyDown = false;
		}
	}
}

void Pacman::CheckStart(Input::KeyboardState* state, Input::Keys startKey)
{
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();

	//Checks to see if enter is being pressed
	if (keyboardState->IsKeyDown(Input::Keys::RETURN) && !_pKeyDown)
	{
		_RetKeyDown = true;
		_menu->startScreen = false;
	}
	if (keyboardState->IsKeyUp(Input::Keys::RETURN))
	{
		_RetKeyDown = false;
	}
}


void Pacman::CheckViewportCollision()
{
	int windWidth = Graphics::GetViewportWidth();
	int windHeight = Graphics::GetViewportHeight();


	//Colliding with wall and resets to the other side so it loops
	if (_pacman->position->X + _pacman->sourceRect->Width > windWidth)
	{
		_pacman->position->X = _pacman->size - _pacman->sourceRect->Width;
	}
	else if (_pacman->position->X + _pacman->sourceRect->Width < _pacman->size)
	{
		_pacman->position->X = windWidth - _pacman->sourceRect->Width;
	}
	else if (_pacman->position->Y + _pacman->sourceRect->Width < _pacman->size)
	{
		_pacman->position->Y = windHeight - _pacman->sourceRect->Width;
	}
	else if (_pacman->position->Y + _pacman->sourceRect->Width > windHeight)
	{
		_pacman->position->Y = _pacman->size - _pacman->sourceRect->Width;
	}
}


void Pacman::CheckMunchieCollision()
{
	int left1 = _pacman->position->X;
	int left2 = 0;
	int right1 = _pacman->position->X + _pacman->sourceRect->Width;
	int right2 = 0;
	int top1 = _pacman->position->Y;
	int top2 = 0;
	int bottom1 = _pacman->position->Y + _pacman->sourceRect->Height;
	int bottom2 = 0;


	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		left2 = _munchies[i]->position->X;
		right2 = _munchies[i]->position->X + _munchies[i]->sourceRect->Width;
		bottom2 = _munchies[i]->position->Y + _munchies[i]->sourceRect->Height;
		top2 = _munchies[i]->position->Y;

		if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2))
			// If Pacman and munchies are colliding
		{
			_munchies[i]->isAlive = false;
			_munchies[i]->position->X = -500;
			_munchies[i]->position->Y = -500;
			_munchies[i]->sourceRect = new Rect(-500, -500, 12, 12);
			Audio::Play(_pop);
			_menu->munchCount = _menu->munchCount - 1;
			if (_menu->munchCount <= 0)
			{
				_menu->gameOverScreen = true;
				_menu->gameOver = true;
				_menu->ghostFrightMode = false;
				_ghosts[i]->killable = false;
				_pacman->killable = true;
				_pacman->isAlive = false;
				_pacman->isMoving = false;
				_pacman->position->X = 2000;
				_pacman->position->Y = 2000;
				_pacman->sourceRect = new Rect(-2000, -2000, 32, 32);
				i = GHOSTCOUNT;
				fstream outFile("Leaderboard.txt", ios::out | ios::app);
				{
					outFile << "Score: " << _leaderboard->score << " Name: " << _leaderboard->playerName << endl;
				}
				outFile.close();
			}


			_leaderboard->score += 10;
		}
		
	}
}

void Pacman::CheckGhostCollisions()
{
	// Local Variables
	int i = 0;
	int bottom1 = _pacman->position->Y + _pacman->sourceRect->Height; //Bottom of pacman
	int bottom2 = 0;
	int left1 = _pacman->position->X;
	int left2 = 0;
	int right1 = _pacman->position->X + _pacman->sourceRect->Width;
	int right2 = 0;
	int top1 = _pacman->position->Y;
	int top2 = 0;

	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		// Populate variables with Ghost data
		bottom2 = _ghosts[i]->position->Y + _ghosts[i]->sourceRect->Height;
		left2 = _ghosts[i]->position->X;
		right2 = _ghosts[i]->position->X + _ghosts[i]->sourceRect->Width;
		top2 = _ghosts[i]->position->Y;

		if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2))
		{
			if (_menu->ghostFrightMode == true)
				//This states that if the ghosts can be killed the following actions will happen
			{
				_leaderboard->score += 40;
				_pacman->killable = false;
				_ghosts[i]->killable = true;
				_ghosts[i]->position = new Vector2((rand() % Graphics::GetViewportWidth()),
					(rand() % Graphics::GetViewportHeight()));
				//_menu->pacmanCount -= 1;
				Audio::Play(_gDeath);
			}
			else if (_menu->ghostFrightMode == false)
			{
				_menu->gameOverScreen = true;
				_menu->gameOver = true;
				_menu->ghostFrightMode = false;
				_ghosts[i]->killable = false;
				_pacman->killable = true;
				_pacman->isAlive = false;
				_pacman->isMoving = false;
				_pacman->position->X = 2000;
				_pacman->position->Y = 2000;
				_pacman->sourceRect = new Rect(-2000, -2000, 32, 32);
				i = GHOSTCOUNT;
				Audio::Play(_pDeath);
				fstream outFile("Leaderboard.txt", ios::out | ios::app);
				{
					outFile << "Score: " << _leaderboard->score << " Name: " << _leaderboard->playerName << endl;
				}
				outFile.close();
			}
		}
	}
}


void Pacman::CheckCherryCollision()
{
	// Local Variables
	int i = 0;
	int bottom1 = _pacman->position->Y + _pacman->sourceRect->Height; //Bottom of pacman

	int left1 = _pacman->position->X;

	int right1 = _pacman->position->X + _pacman->sourceRect->Width;

	int top1 = _pacman->position->Y;


	for (int i = 0; i < CHERRYCOUNT; i++)
	{
		int bottom2 = _cherry->position->Y + _cherry->sourceRect->Height;
		int left2 = _cherry->position->X;
		int right2 = _cherry->position->X + _cherry->sourceRect->Width;
		int top2 = _cherry->position->Y;
		if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2))
		{
			_cherry->isAlive = false;
			_cherry->position->X = -800;
			_cherry->position->Y = -800;
			_cherry->sourceRect = new Rect(-800, -800, 32, 32);
			i = CHERRYCOUNT;
			Audio::Play(_eatCherry);
			_leaderboard->score += 100;
		}
	}
}

void Pacman::CheckFrightBallCollision()
{
	// Local Variables
	int i = 0;
	int bottom1 = _pacman->position->Y + _pacman->sourceRect->Height; //Bottom of pacman

	int left1 = _pacman->position->X;

	int right1 = _pacman->position->X + _pacman->sourceRect->Width;

	int top1 = _pacman->position->Y;


	for (int i = 0; i < FRIGHTBALL; i++)
	{
		int bottom2 = _frightBall[i]->position->Y + _frightBall[i]->sourceRect->Height;
		int left2 = _frightBall[i]->position->X;
		int right2 = _frightBall[i]->position->X + _frightBall[i]->sourceRect->Width;
		int top2 = _frightBall[i]->position->Y;
		if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2))
		{
			_frightBall[i]->position->X = -400;
			_frightBall[i]->position->Y = -400;
			_frightBall[i]->sourceRect = new Rect(-400, -400, 32, 32);
			i = FRIGHTBALL;
			Audio::Play(_frightSound);
			_leaderboard->score += 50;
			_menu->ghostFrightMode = true;
		}
	}
}

void Pacman::OriginalGhostColours()
{
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		if (_ghosts[i]->name == "Inky")
			_ghosts[i]->texture = _ghosts[i]->blueGhost;
		if (_ghosts[i]->name == "Blinky")
			_ghosts[i]->texture = _ghosts[i]->redGhost;
		if (_ghosts[i]->name == "Clyde")
			_ghosts[i]->texture = _ghosts[i]->orangeGhost;
		if (_ghosts[i]->name == "Pinky")
			_ghosts[i]->texture = _ghosts[i]->pinkGhost;
	}
}

void Pacman::FrightMode(int elapsedTime)
{
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		if (_ghosts[i]->killable == false)
		{
			_ghosts[i]->killable = false;
			if (_ghosts[i]->direction == 0)
			{
				_ghosts[i]->sourceRect->X = 0;
			}
			if (_ghosts[i]->direction == 1)
			{
				_ghosts[i]->sourceRect->X = 20;
			}
			if (_ghosts[i]->direction == 2)
			{
				_ghosts[i]->sourceRect->X = 40;
			}
			if (_ghosts[i]->direction == 3)
			{
				_ghosts[i]->sourceRect->X = 60;
			}
		}
		if (_menu->ghostFrightMode == true)
		{
			_ghosts[i]->killable = true;
			_pacman->killable = false;
			_menu->ghostFrightTimer++;

			if (_menu->ghostFrightTimer == 2000)
			{
				//OriginalGhostColours();
				_ghosts[i]->killable = false;
				_pacman->killable = true;
				_menu->ghostFrightMode = false;
				_menu->ghostFrightTimer = 0;
			}
		}
	}
}


void Pacman::Input(int elapsedTime, Input::KeyboardState* state, Input::MouseState* mouseState)
{
	// Gets the current state of the keyboard
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();

	// Checks if D key is pressed
	if (!_menu->paused && !_menu->startScreen)
	{
		//Speed multiplier
		if (((keyboardState->IsKeyDown(Input::Keys::SPACE) || keyboardState->IsKeyDown(Input::Keys::NUMPAD5))) &&
			_pacman->speedBoostTimer < _pacman->maxSpeedBoost)
		{
			if (!_pacman->rechargingBoost) // If its not recharging applies the boost
			{
				_pacman->speedMultiplier = 2.0f; //Apply speed boost multiplier
				_pacman->speedBoost = true; //Sets to true so we know what state pacman is in
				Audio::Play(_speedBoost);
			}
		}
		else
		{
			if (_pacman->speedBoostTimer >= _pacman->maxSpeedBoost)
			{
				_pacman->speedBoost = false; //Set the state of speeedBoost to false
				_pacman->speedMultiplier = 1.0f; //Apply normal speed
				_pacman->rechargingBoost = true; //Set the state of recharging to true
				_pacman->speedBoostCooldownCounter++; //Increments the speed boost cooldown
				if (_pacman->speedBoostCooldownCounter > _pacman->maxSpeedBoostCooldown)
				{
					_pacman->rechargingBoost = false;
					_pacman->speedBoostTimer = 0;
					_pacman->speedBoostCooldownCounter = 0;
				}
			}
		}


		if (keyboardState->IsKeyDown(Input::Keys::D) || keyboardState->IsKeyDown(Input::Keys::NUMPAD6))
		{
			_pacman->isMoving = true;
			_pacman->direction = 4;
		}

			// Checks if A key is pressed
		else if (keyboardState->IsKeyDown(Input::Keys::A) || keyboardState->IsKeyDown(Input::Keys::NUMPAD4))
		{
			_pacman->isMoving = true;
			_pacman->direction = 2;
		}

			// Checks if W key is pressed
		else if (keyboardState->IsKeyDown(Input::Keys::W) || keyboardState->IsKeyDown(Input::Keys::NUMPAD9))
		{
			_pacman->isMoving = true;
			_pacman->direction = 3;
		}

			// Checks if S key is pressed
		else if (keyboardState->IsKeyDown(Input::Keys::S) || keyboardState->IsKeyDown(Input::Keys::NUMPAD2))
		{
			_pacman->isMoving = true;
			_pacman->direction = 1;
		}


		//Random Cherry
		if (keyboardState->IsKeyDown(Input::Keys::R) && _cherry->resetTimer < 1)
		{
			_cherry->resetTimer++;
			_cherry->position = new Vector2((rand() % Graphics::GetViewportWidth()),
			                                (rand() % Graphics::GetViewportHeight()));
		}
	}

}


void Pacman::Draw(int elapsedTime)
{
	// Allows us to easily create a string
	std::stringstream stream;
	Input::MouseState* mouseState = Input::Mouse::GetState();
	//This takes the mouse input the same way the keyboard one does for our moving
	SpriteBatch::BeginDraw(); // Starts Drawing


	//Draws start screen
	if (_menu->startScreen)
	{
		std::stringstream menuStream;
		_menu->playing = true;
		_pacman->isAlive = false;
		_pacman->killable = false;
		SpriteBatch::Draw(_pausemenuBackground, _pausemenuRectangle, nullptr);
		SpriteBatch::Draw(_pacmanTitleLabel, _pacmanTitleRectangle, nullptr);

		//Deciding Which Button Is Needed To Be Drawn
		if (_menu->startButtonHover == false)
		{
			SpriteBatch::Draw(_startLabel, _startRectangle, nullptr);
		}
		else
		{
			SpriteBatch::Draw(_startHighlightedLabel, _startHighlightedRectangle, nullptr);
		}
		//Deciding Which Button Is Needed To Be Drawn
		if (_menu->scoresButtonHover == false)
		{
			SpriteBatch::Draw(_scoresLabel, _scoresRectangle, nullptr);
		}
		else
		{
			SpriteBatch::Draw(_scoresHighlightedLabel, _scoresHighlightedRectangle, nullptr);
		}
		//Deciding Which Button Is Needed To Be Drawn
		if (_menu->exitButtonHover == false)
		{
			SpriteBatch::Draw(_exitLabel, _exitRectangle, nullptr);
		}
		else
		{
			SpriteBatch::Draw(_exitHighlightedLabel, _exitHighlightedRectangle, nullptr);
		}


		//Start Button Hover and Click Options
		if (mouseState->X >= 350 && mouseState->X <= 670 && mouseState->Y >= 230 && mouseState->Y <= 300)
			//This is to say if the mouse if highlighted over this area, not yet clicked
		{
			_menu->startButtonHover = true;
			if (mouseState->LeftButton == Input::ButtonState::PRESSED) // If left click
			{
				_menu->startScreen = false;
				_menu->playing = true;
				_menu->startButtonHover = false;
			}
		}
		else
		{
			_menu->startButtonHover = false;
		}
		//Scores button
		if (mouseState->X >= 315 && mouseState->X <= 705 && mouseState->Y >= 370 && mouseState->Y <= 455)
			//This is to say if the mouse if highlighted over this area, not yet clicked
		{
			_menu->scoresButtonHover = true;
			if (mouseState->LeftButton == Input::ButtonState::PRESSED) // If left click
			{
				_menu->startScreen = false;
				_menu->playing = false;
				_menu->leaderboardScreen = true;
				_menu->scoresButtonHover = false;
			}
		}
		else
		{
			_menu->scoresButtonHover = false;
		}
		//Exit Button
		if (mouseState->X >= 385 && mouseState->X <= 650 && mouseState->Y >= 510 && mouseState->Y <= 585)
			//This is to say if the mouse if highlighted over this area, not yet clicked
		{
			_menu->exitButtonHover = true;
			if (mouseState->LeftButton == Input::ButtonState::PRESSED) // If left click
			{
				//Close all files correctly
				exit(10);
			}
		}
		else
		{
			_menu->exitButtonHover = false;
		}


		SpriteBatch::DrawString(menuStream.str().c_str(), _pausemenuStringPosition, Color::Cyan);
	}
	else if (_menu->playing)
	{
		_pacman->isAlive = true;
		//LoadMap();
		stream << "Name: " << _leaderboard->playerName << "    Score: " << _leaderboard->score;
		if (_pacman->isAlive)
		{
			SpriteBatch::Draw(_pacman->texture, _pacman->position, _pacman->sourceRect); // Draws Pacman
		}


		if (_cherry->FrameCount == 0)
		{
			SpriteBatch::Draw(_cherry->InvertedTexture, _cherry->position, nullptr, Vector2::Zero, 1.0f, 0.0f,
			                  Color::White, SpriteEffect::NONE);
		}
		else
		{
			SpriteBatch::Draw(_cherry->Texture, _cherry->position, nullptr, Vector2::Zero, 1.0f, 0.0f, Color::White,
			                  SpriteEffect::NONE);
		}
		for (int frameCount = 0; frameCount < MUNCHIECOUNT; frameCount++)
		{
			if (_munchies[frameCount]->FrameCount == 0)
			{
				// Draws Red Munchie
				SpriteBatch::Draw(_munchies[frameCount]->InvertedTexture, _munchies[frameCount]->position, nullptr,
					Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);

			}
			else
			{
				// Draw Blue Munchie
				SpriteBatch::Draw(_munchies[frameCount]->Texture, _munchies[frameCount]->position, nullptr,
					Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);


				_munchies[frameCount]->FrameCount++;

			}


		}
		

		for (int frameCount = 0; frameCount < GHOSTCOUNT; frameCount++)
			//Depending on the number in the loop, each ghost will be drawn with a different texture for different colours.
		{
			if (frameCount == 0)
			{
				SpriteBatch::Draw(_ghosts[frameCount]->blueGhost, _ghosts[frameCount]->position,
				                  _ghosts[frameCount]->sourceRect);
				_ghosts[frameCount]->name = "Inky";
			}
			if (frameCount == 1)
			{
				SpriteBatch::Draw(_ghosts[frameCount]->orangeGhost, _ghosts[frameCount]->position,
				                  _ghosts[frameCount]->sourceRect);
				_ghosts[frameCount]->name = "Clyde";
			}
			if (frameCount == 2)
			{
				SpriteBatch::Draw(_ghosts[frameCount]->pinkGhost, _ghosts[frameCount]->position,
				                  _ghosts[frameCount]->sourceRect);
				_ghosts[frameCount]->name = "Pinky";
			}
			if (frameCount == 3)
			{
				SpriteBatch::Draw(_ghosts[frameCount]->redGhost, _ghosts[frameCount]->position,
				                  _ghosts[frameCount]->sourceRect);
				_ghosts[frameCount]->name = "Blinky";
			}


			if (_menu->ghostFrightMode == false)
			{
				SpriteBatch::Draw(_ghosts[frameCount]->texture, _ghosts[frameCount]->position,
				                  _ghosts[frameCount]->sourceRect);
			}
			else if (_menu->ghostFrightMode == true)
			{
				for (int i = 0; i < GHOSTCOUNT; i++)
				{
					_ghosts[i]->killable = true;
					if (_ghosts[i]->FrameCount == 0)
					{
						SpriteBatch::Draw(_ghosts[i]->frightTexture1, _ghosts[i]->position, _ghosts[i]->sourceRect);
					}
					else
					{
						SpriteBatch::Draw(_ghosts[i]->frightTexture2, _ghosts[i]->position, _ghosts[i]->sourceRect);
						_ghosts[i]->FrameCount++;
					}
					if (_ghosts[i]->FrameCount >= 100)
					{
						_ghosts[i]->FrameCount = 0;
						_menu->ghostFrightMode = false;
						_ghosts[i]->killable = false;
					}
				}
			}
			
		}

		for (int frameCount = 0; frameCount < FRIGHTBALL; frameCount++)
		{
			SpriteBatch::Draw(_frightBall[frameCount]->Texture, _frightBall[frameCount]->position,
			                  _frightBall[frameCount]->sourceRect);
		}


		//I tried combining the logic for the percentage bar but it just didn't work
		if(_pacman->speedBoostTimer > 90 && _pacman->speedBoostTimer <= _pacman->maxSpeedBoost)
		{
			SpriteBatch::Draw(_percEmptyLabel, _percEmptyRectangle, nullptr);
		}
		else if (_pacman->speedBoostTimer > (_pacman->maxSpeedBoost / 10) * 8 && _pacman->speedBoostTimer <= (_pacman->maxSpeedBoost / 10) * 9)
		{
			SpriteBatch::Draw(_perc1of10Label, _perc1of10Rectangle, nullptr);
		}
		else if (_pacman->speedBoostTimer > (_pacman->maxSpeedBoost / 10) * 7 && _pacman->speedBoostTimer <= (_pacman->maxSpeedBoost / 10) * 8)
		{
			SpriteBatch::Draw(_perc2of10Label, _perc2of10Rectangle, nullptr);
		}
		else if (_pacman->speedBoostTimer > (_pacman->maxSpeedBoost / 10) * 6 && _pacman->speedBoostTimer <= (_pacman->maxSpeedBoost / 10) * 7)
		{
			SpriteBatch::Draw(_perc3of10Label, _perc3of10Rectangle, nullptr);
		}
		else if (_pacman->speedBoostTimer > (_pacman->maxSpeedBoost / 10) * 5 && _pacman->speedBoostTimer <= (_pacman->maxSpeedBoost / 10) * 6)
		{
			SpriteBatch::Draw(_perc4of10Label, _perc4of10Rectangle, nullptr);
		}
		else if (_pacman->speedBoostTimer > (_pacman->maxSpeedBoost / 10) * 4 && _pacman->speedBoostTimer <= (_pacman->maxSpeedBoost / 10) * 5)
		{
			SpriteBatch::Draw(_perc5of10Label, _perc5of10Rectangle, nullptr);
		}
		else if (_pacman->speedBoostTimer > (_pacman->maxSpeedBoost / 10) * 3 && _pacman->speedBoostTimer <= (_pacman->maxSpeedBoost / 10) * 4)
		{
			SpriteBatch::Draw(_perc6of10Label, _perc6of10Rectangle, nullptr);
		}
		else if (_pacman->speedBoostTimer > (_pacman->maxSpeedBoost / 10) * 2 && _pacman->speedBoostTimer <= (_pacman->maxSpeedBoost / 10) * 3)
		{
			SpriteBatch::Draw(_perc7of10Label, _perc7of10Rectangle, nullptr);
		}
		else if (_pacman->speedBoostTimer > (_pacman->maxSpeedBoost / 10) * 1 && _pacman->speedBoostTimer <= (_pacman->maxSpeedBoost / 10) * 2)
		{
			SpriteBatch::Draw(_perc8of10Label, _perc8of10Rectangle, nullptr);
		}
		else if (_pacman->speedBoostTimer > 0 && _pacman->speedBoostTimer <= (_pacman->maxSpeedBoost/10) * 1)
		{
			SpriteBatch::Draw(_perc9of10Label, _perc9of10Rectangle, nullptr);
		}
		else if (_pacman->speedBoostTimer <= 0)
		{
			SpriteBatch::Draw(_percFullLabel, _percFullRectangle, nullptr);
		}

		if (_pacman->speedBoostCooldownCounter >= 0 && _pacman->speedBoostCooldownCounter < (_pacman->maxSpeedBoostCooldown/10)*1)
		{
			SpriteBatch::Draw(_percEmptyLabel, _percEmptyRectangle, nullptr);
		}
		else if (_pacman->speedBoostCooldownCounter >= (_pacman->maxSpeedBoostCooldown / 10) * 1 && _pacman->speedBoostCooldownCounter < (_pacman->maxSpeedBoostCooldown / 10) * 2)
		{
			SpriteBatch::Draw(_perc1of10Label, _perc1of10Rectangle, nullptr);
		}
		else if (_pacman->speedBoostCooldownCounter >= (_pacman->maxSpeedBoostCooldown / 10) * 2 && _pacman->speedBoostCooldownCounter < (_pacman->maxSpeedBoostCooldown / 10) * 3)
		{
			SpriteBatch::Draw(_perc2of10Label, _perc2of10Rectangle, nullptr);
		}
		else if (_pacman->speedBoostCooldownCounter >= (_pacman->maxSpeedBoostCooldown / 10) * 3 && _pacman->speedBoostCooldownCounter < (_pacman->maxSpeedBoostCooldown / 10) * 4)
		{
			SpriteBatch::Draw(_perc3of10Label, _perc3of10Rectangle, nullptr);
		}
		else if (_pacman->speedBoostCooldownCounter >= (_pacman->maxSpeedBoostCooldown / 10) * 4 && _pacman->speedBoostCooldownCounter < (_pacman->maxSpeedBoostCooldown / 10) * 5)
		{
			SpriteBatch::Draw(_perc4of10Label, _perc4of10Rectangle, nullptr);
		}
		else if (_pacman->speedBoostCooldownCounter >= (_pacman->maxSpeedBoostCooldown / 10) * 5 && _pacman->speedBoostCooldownCounter < (_pacman->maxSpeedBoostCooldown / 10) * 6)
		{
			SpriteBatch::Draw(_perc5of10Label, _perc5of10Rectangle, nullptr);
		}
		else if (_pacman->speedBoostCooldownCounter >= (_pacman->maxSpeedBoostCooldown / 10) * 6 && _pacman->speedBoostCooldownCounter < (_pacman->maxSpeedBoostCooldown / 10) * 7)
		{
			SpriteBatch::Draw(_perc6of10Label, _perc6of10Rectangle, nullptr);
		}
		else if (_pacman->speedBoostCooldownCounter >= (_pacman->maxSpeedBoostCooldown / 10) * 7 && _pacman->speedBoostCooldownCounter < (_pacman->maxSpeedBoostCooldown / 10) * 8)
		{
			SpriteBatch::Draw(_perc7of10Label, _perc7of10Rectangle, nullptr);
		}
		else if (_pacman->speedBoostCooldownCounter >= (_pacman->maxSpeedBoostCooldown / 10) * 8 && _pacman->speedBoostCooldownCounter < (_pacman->maxSpeedBoostCooldown / 10) * 9)
		{
			SpriteBatch::Draw(_perc8of10Label, _perc8of10Rectangle, nullptr);
		}
		else if (_pacman->speedBoostCooldownCounter >= (_pacman->maxSpeedBoostCooldown / 10) * 9 && _pacman->speedBoostCooldownCounter < _pacman->maxSpeedBoostCooldown)
		{
			SpriteBatch::Draw(_perc9of10Label, _perc9of10Rectangle, nullptr);
		}
		else if (_pacman->speedBoostCooldownCounter >= _pacman->maxSpeedBoostCooldown)
		{
			SpriteBatch::Draw(_percFullLabel, _percFullRectangle, nullptr);
		}


		//Draws pause screen
		if (_menu->paused)
		{
			std::stringstream menuStream;
			SpriteBatch::Draw(_pausemenuBackground, _pausemenuRectangle, nullptr);
			SpriteBatch::Draw(_pacmanTitleLabel, _pacmanTitleRectangle, nullptr);
			SpriteBatch::Draw(_pauseLogoLabel, _pausemenuRectangle, nullptr);
			SpriteBatch::DrawString(menuStream.str().c_str(), _pausemenuStringPosition, Color::Red);
		}
		else if (_menu->gameOverScreen == true)
		{
			
			SpriteBatch::Draw(_pausemenuBackground, _pausemenuRectangle, nullptr);
			SpriteBatch::Draw(_gameoverTitleLabel, _gameoverTitleRectangle, nullptr);
			
				
			
			
			
			//Deciding Which Button Is Needed To Be Drawn
			if (_menu->gameoverMainMenuHover == false)
			{
				SpriteBatch::Draw(_exitLabel, _exitRectangle, nullptr);
			}
			else
			{
				SpriteBatch::Draw(_exitHighlightedLabel, _exitHighlightedRectangle, nullptr);
			}

			//Exit Button
			if (mouseState->X >= 385 && mouseState->X <= 650 && mouseState->Y >= 510 && mouseState->Y <= 585)
				//This is to say if the mouse if highlighted over this area, not yet clicked
			{
				_menu->gameoverMainMenuHover = true;
				if (mouseState->LeftButton == Input::ButtonState::PRESSED) // If left click
				{
					_menu->gameOverScreen = false;
					_menu->startScreen = true;
				}
			}
			else
			{
				_menu->gameoverMainMenuHover = false;
			}


			
		}
	}
	//Draws leaderboard screen
	else if (_menu->leaderboardScreen == true)
	{

		//if (_leaderboard->leaderboardHighToLow == false)
		//{
		//	fstream inFile("Leaderboard.txt", ios::in | ios::app); // Opens file
		//	if (inFile) // If file can be opened
		//	{
		//		int loopCount = 0;
		//		string names[10] = {};
		//		int scores[10] = {};
		//		string line;
		//		while (getline(inFile, line))
		//		{
		//			int indexOfSpace = 0;
		//			for (int i = 0; i < line.length(); i++)
		//			{
		//				if (line[i] == ' ')
		//				{
		//					indexOfSpace = i;
		//					break;
		//				}
		//			}
		//			scores[loopCount] = stoi(line.substr(indexOfSpace + 1, line.length()));
		//			names[loopCount] = line.substr(0, indexOfSpace);
		//			loopCount++;
		//		}
		//		inFile.close();

		//		if (loopCount == 10)
		//		{
		//			int lowestScore = GetSmallestElement(scores, loopCount);
		//			int lowestScoreIndex = 0;
		//			for (int i = 0; i < 10; i++)
		//			{
		//				if (scores[i] == lowestScore)
		//				{
		//					lowestScoreIndex = i;
		//				}
		//			}
		//			if (_leaderboard->score > lowestScore)
		//			{
		//				scores[lowestScoreIndex] = _leaderboard->score;
		//				names[lowestScoreIndex] = _leaderboard->playerName;
		//			}

		//			int p = sizeof(scores) / sizeof(scores[0]); // Sets size
		//			int temp;
		//			string temp2;

		//			// Loops through all values in values and orders them and also orders the names to correspond
		//			for (int i = 0; i < p; i++)
		//			{
		//				for (int j = i + 1; j < p; j++)
		//				{
		//					if (scores[i] > scores[j])
		//					{
		//						temp = scores[i];
		//						temp2 = names[i];
		//						scores[i] = scores[j];
		//						names[i] = names[j];
		//						scores[j] = temp;
		//						names[j] = temp2;
		//					}
		//				}
		//			}
		//			fstream outFile("Leaderboard.txt", ios::out | ios::trunc);
		//			//Truncate the file to write over the top of it
		//			for (int i = 9; i < -1; i--)
		//			{
		//				outFile << "Score: " << scores[i] << " Name: " << names[i] << endl;
		//			}
		//			outFile.close();

		//			inFile.open("Scores.txt", ios::in | ios::app);
		//			if (inFile.is_open())
		//			{
		//				while (getline(inFile, line))
		//				{
		//					cout << line << endl;
		//				}
		//				inFile.close();
		//			}
		//			
		//		}
		//		_leaderboard->leaderboardHighToLow = true;
		//	}
		//	else
		//	{
		//		cerr << "File could not be opened!";
		//		exit(5);
		//	}

		//}
		SpriteBatch::Draw(_pausemenuBackground, _pausemenuRectangle, nullptr);
		SpriteBatch::Draw(_leaderboardTitleLabel, _leaderboardTitleRectangle, nullptr);


		 
		//Deciding Which Button Is Needed To Be Drawn
		if (_menu->leaderboardBackHover == false)
		{
			SpriteBatch::Draw(_leaderboardBackLabel, _leaderboardBackRectangle, nullptr);
		}
		else
		{
			SpriteBatch::Draw(_leaderboardBackHighlightedLabel, _leaderboardBackHighlightedRectangle, nullptr);
		}

		//Exit Button
		if (mouseState->X >= 375 && mouseState->X <= 650 && mouseState->Y >= 650 && mouseState->Y <= 718)
			//This is to say if the mouse if highlighted over this area, not yet clicked
		{
			_menu->leaderboardBackHover = true;
			if (mouseState->LeftButton == Input::ButtonState::PRESSED) // If left click
			{
				_menu->leaderboardScreen = false;
				_menu->startScreen = true;
			}
		}
		else
		{
			_menu->leaderboardBackHover = false;
		}
	}


	

	// Draws String
	SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Green);
	SpriteBatch::EndDraw(); // Ends Drawing
}


int Pacman::GetSmallestElement(int arr[], int n)
{
	int temp = arr[0];
	for (int i = 0; i < n; i++)
	{
		if (temp > arr[i])
		{
			temp = arr[i];
		}
	}
	return temp;
}
