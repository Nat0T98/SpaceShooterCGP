#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "GameObject.h"
#include "Ship.h"
#include "Collision.h"
#include "Enemy.h"
#include "Meteor.h"
#include "Laser.h"
#include "Comet.h"
#include "Background.h"
#include "PickUps.h"

SDL_Renderer* g_sdlRenderer;
SDL_Window* g_sdlWindow;
TTF_Font* g_font;

SDL_Texture* LoadTexture(const char* filename)
{
	//Load BMP
	SDL_Surface* Image = IMG_Load(filename);
	if (Image == nullptr)
	{
		std::cout << "Failed to load " << filename  << "SDL Error; "<< SDL_GetError() << std::endl;
	}

	//Draw window and print image
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(g_sdlRenderer, Image);
	if (Texture == nullptr)
	{
		std::cout << "Failed to create texture from surface, SDL Error; " << IMG_GetError() << std::endl;
	}

	SDL_FreeSurface(Image);

	return Texture;
}

bool Initialise()
{
	// Initilise all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialise SDL. SDL Errors; " << SDL_GetError() << std::endl;
		return true;
	}

	// Create a window with the specified name, anywhere on the screen, 800x600 pixel size and no SDL_WindowFlags flags.
	int iWindowFlag = NULL;
	g_sdlWindow = SDL_CreateWindow("Week 1 - Intro and Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 750, 960, iWindowFlag);
	
	if (g_sdlWindow == nullptr)
	{
		std::cout << "Failed to create window, SDL Error; " << SDL_GetError() << std::endl;
		return true;
	}
	// Create a rendering context for our window, Enable hardware acceleration with the SDL_RENDERER_ACCELERAED flag
	g_sdlRenderer = SDL_CreateRenderer(g_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	if (g_sdlRenderer == nullptr)
	{
		std::cout << "Failed to create renderer, SDL error: " << SDL_GetError() << std::endl;
		return true;
	}

	//Store a bitmask for which file types we want to initialise
	// init flags = IMG_INIT_JPG | IMG_INIT_PNG
	int flags = IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if (initted != flags)
	{
		std::cout << "Failed to initialise SDL_Image. SDL_Image Error; " << IMG_GetError() << std::endl;
		return true;
	}

	// Store a bitmask for which file types we want to initialise
	flags = MIX_INIT_MP3;
	initted = Mix_Init(flags);
	if (initted != flags)
	{
		std::cout << "Failed to initialise SDL_Mixer. SDL_Mixer Error; " << Mix_GetError() << std::endl;
		return true;
	}
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0)
	{
		std::cout << "Failed to open audio device. SDL_Mixer Error; " << Mix_GetError() << std::endl;
		return true;
	}

	//TTF Initialisation
	if (TTF_Init() < 0)
	{
		std::cout << "Failed to initialise TTF. SDL_TTF Error; " << TTF_GetError() << std::endl;
		return true;
	}

	g_font = TTF_OpenFont("Assets/8bitOperatorPlus8-Regular.ttf", 32);
	if (g_font == nullptr)
	{
		std::cout << "Failed to load font. SDL_TTF Error; " << TTF_GetError() << std::endl;
		return true;
	}
	return false;
}

void CleanUp()
{
	SDL_DestroyRenderer(g_sdlRenderer);
	SDL_DestroyWindow(g_sdlWindow); // Opposite of SDL_CreateWindow(...)
	Mix_CloseAudio();
	TTF_CloseFont(g_font);
	IMG_Quit();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit(); //Opposite of SDL_Init(...)
}

int main(int argc, char* argv[])
{
	if (Initialise())
	{
		std::cout << "Application failed to initialise. Quitting..." << std::endl;
		return -1;
	}
#pragma region Loading Textures
//Load textures
	SDL_Texture* P_Ship = LoadTexture("Assets/spacecraft.png");
	Ship PlayerShip{ P_Ship };
	PlayerShip.isAnimated = true;	
	PlayerShip.animationSpeed = 5;	
	PlayerShip.animPixelWidth = 90;	
	PlayerShip.animPixelHeight = 128;	
	PlayerShip.animState = 0;	
	PlayerShip.animFrames = 3;

	SDL_Texture* E_Ship1 = LoadTexture("Assets/enemyRed.png");	
	Enemy EnemyShip1{ E_Ship1 };
	SDL_Texture* E_Ship2 = LoadTexture("Assets/enemyGreen.png");
	Enemy EnemyShip2{ E_Ship2 }; 
	SDL_Texture* E_Ship3 = LoadTexture("Assets/enemyBlue.png");
	Enemy EnemyShip3{ E_Ship3 };
	SDL_Texture* E_Ship4 = LoadTexture("Assets/enemyBlack.png");
	Enemy EnemyShip4{ E_Ship4 };


	SDL_Texture* _Meteors1 = LoadTexture("Assets/Meteor.png");
	Meteor Meteor1{ _Meteors1 };
	SDL_Texture* _Meteors2 = LoadTexture("Assets/Meteor.png");
	Meteor Meteor2{ _Meteors2 };
	SDL_Texture* _Meteors3 = LoadTexture("Assets/Meteor.png");
	Meteor Meteor3{ _Meteors3 };

	SDL_Texture* _Comet1 = LoadTexture("Assets/Comet.png");
	Comet Comet1{ _Comet1 };
	SDL_Texture* _Comet2 = LoadTexture("Assets/Comet.png");
	Comet Comet2{ _Comet2 };
	SDL_Texture* _Comet3 = LoadTexture("Assets/Comet.png");
	Comet Comet3{ _Comet3 };

	SDL_Texture* _Background1 = LoadTexture("Assets/background.png");
	Background Background1{ _Background1 };

	SDL_Texture* _HP1 = LoadTexture("Assets/HP.png");
	PickUps HP1{ _HP1 };	
	
	SDL_Texture* _Laser = LoadTexture("Assets/pBullet1.png");
	Laser Lasers{ _Laser };
#pragma endregion

	
#pragma region SFX
//Load Sound Effects
	Mix_Chunk* LaserSFX = Mix_LoadWAV("Assets/laser4.mp3");
	//Load Music File
	Mix_Music* Music = Mix_LoadMUS("Music/Music2.mp3");
	//Play Music with inifinte looping
	Mix_PlayMusic(Music, -1);
#pragma endregion
	
	PlayerShip.health;	
	std::string HealthStr = std::to_string(PlayerShip.health);
	std::string enemyStr = std::to_string(EnemyShip1.enemiesRemaining);
	
	

#pragma region ttf
//Remaining enemies title
	SDL_Surface* RemEnem = TTF_RenderText_Blended(g_font, "Enemies Remaining: ", {255,255,255,255});
	SDL_Texture* RemEnTexture = SDL_CreateTextureFromSurface(g_sdlRenderer, RemEnem);
	SDL_FreeSurface(RemEnem);

	SDL_Surface* enemyNum = TTF_RenderText_Blended(g_font, enemyStr.c_str(), { 255,255,255,255 });
	SDL_Texture* enemyNumTexture = SDL_CreateTextureFromSurface(g_sdlRenderer, enemyNum);
	SDL_FreeSurface(enemyNum);

	SDL_Surface* RemHealth = TTF_RenderText_Blended(g_font, "Health: ", { 255,255,255,255 });
	SDL_Texture* HealthTexture = SDL_CreateTextureFromSurface(g_sdlRenderer, RemHealth);
	SDL_FreeSurface(RemHealth);


	SDL_Surface* HealthNum = TTF_RenderText_Blended(g_font, HealthStr.c_str(), {255,255,255,255});
	SDL_Texture* HealthNumTexture = SDL_CreateTextureFromSurface(g_sdlRenderer, HealthNum);
	SDL_FreeSurface(HealthNum);

	SDL_Surface* GOver = TTF_RenderText_Blended(g_font, "", { 255, 255, 255, 255 });
	SDL_Texture* GOverTexture = SDL_CreateTextureFromSurface(g_sdlRenderer, GOver);
	SDL_FreeSurface(GOver);

#pragma endregion
		
	Uint32 previousFrameTicks = SDL_GetTicks();
	bool keepRunning = true;
	while (keepRunning)
	{
		float deltaTime = (SDL_GetTicks() - (float)(previousFrameTicks)) / 1000;
		previousFrameTicks = SDL_GetTicks();
		
				
		SDL_Event sdlEvent;
		while (SDL_PollEvent(&sdlEvent))
		{
			switch (sdlEvent.type)
			{
			case SDL_QUIT:
				keepRunning = false;
				break;
							
			case SDL_KEYDOWN:
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
				{					
					keepRunning = false;			
				}
				
				else if (sdlEvent.key.keysym.sym == SDLK_w || sdlEvent.key.keysym.sym == SDLK_UP)
				{
					PlayerShip.KeyMoveUp() * deltaTime;	
				}
				else if (sdlEvent.key.keysym.sym == SDLK_a || sdlEvent.key.keysym.sym == SDLK_LEFT)
				{
					PlayerShip.KeyMoveLeft() * deltaTime;	
				}
				else if (sdlEvent.key.keysym.sym == SDLK_s || sdlEvent.key.keysym.sym == SDLK_DOWN)
				{
					PlayerShip.KeyMoveDown() * deltaTime;	
				}
				else if (sdlEvent.key.keysym.sym == SDLK_d || sdlEvent.key.keysym.sym == SDLK_RIGHT)
				{
					PlayerShip.KeyMoveRight() * deltaTime;	
				}		
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (sdlEvent.button.button == SDL_BUTTON_LEFT)
				{
					Mix_PlayChannel(-1, LaserSFX, 0);	
					Lasers.Draw(g_sdlRenderer);
				}
				break;

			case SDL_MOUSEMOTION:
				
				PlayerShip.m_x = sdlEvent.motion.x;
				PlayerShip.m_y = sdlEvent.motion.y;
				break;

			default:
				break;
			}

			

			Lasers.Move()* deltaTime;
			//Lasers.m_x = PlayerShip.m_x;
			//Lasers.m_y = PlayerShip.m_y;
			
#pragma region Object move functions
			EnemyShip1.MoveDown()* deltaTime;
			EnemyShip1.resetEnPos();
			EnemyShip2.MoveDown()* deltaTime;
			EnemyShip2.resetEnPos();
			EnemyShip3.MoveDown()* deltaTime;
			EnemyShip3.resetEnPos();
			EnemyShip4.MoveDown()* deltaTime;
			EnemyShip4.resetEnPos();

			Meteor1.MoveDown()* deltaTime;
			Meteor1.resetMetPos();
			Meteor2.MoveDown()* deltaTime;
			Meteor2.resetMetPos();
			Meteor3.MoveDown()* deltaTime;
			Meteor3.resetMetPos();

			Comet1.MoveDown()* deltaTime;
			Comet1.resetCometPos();
			Comet2.MoveDown()* deltaTime;
			Comet2.resetCometPos();
			Comet3.MoveDown()* deltaTime;
			Comet3.resetCometPos();

			HP1.MoveDown()* deltaTime;
			HP1.resetPickUpPos();

#pragma endregion
		}		
#pragma region Collion against player
		//Enemy ship collison	
		if (Collision::CircleCollision(PlayerShip.m_x + PlayerShip.m_w / 2,   PlayerShip.m_y + PlayerShip.m_h/2,    PlayerShip.m_w/2,
										EnemyShip1.m_x + EnemyShip1.m_w/2, EnemyShip1.m_y + EnemyShip1.m_h/2,  EnemyShip1.m_w/2))
		{
			PlayerShip.health -= EnemyShip1.enemyDamage;
			std::cout << "Health: " << PlayerShip.health << std::endl;
			//keepRunning = false;
		}
		if (Collision::CircleCollision(PlayerShip.m_x + PlayerShip.m_w / 2, PlayerShip.m_y + PlayerShip.m_h / 2, PlayerShip.m_w / 2,
										EnemyShip2.m_x + EnemyShip2.m_w / 2, EnemyShip2.m_y + EnemyShip2.m_h / 2, EnemyShip2.m_w / 2))
		{
			PlayerShip.health -= EnemyShip2.enemyDamage;
			std::cout << "Health: " << PlayerShip.health << std::endl;
			//keepRunning = false;
		}
		if (Collision::CircleCollision(PlayerShip.m_x + PlayerShip.m_w / 2, PlayerShip.m_y + PlayerShip.m_h / 2, PlayerShip.m_w / 2,
			EnemyShip3.m_x + EnemyShip3.m_w / 2, EnemyShip3.m_y + EnemyShip3.m_h / 2, EnemyShip3.m_w / 2))
		{
			PlayerShip.health -= EnemyShip3.enemyDamage;
			std::cout << "Health: " << PlayerShip.health << std::endl;
			//keepRunning = false;
		}
		if (Collision::CircleCollision(PlayerShip.m_x + PlayerShip.m_w / 2, PlayerShip.m_y + PlayerShip.m_h / 2, PlayerShip.m_w / 2,
			EnemyShip4.m_x + EnemyShip4.m_w / 2, EnemyShip4.m_y + EnemyShip4.m_h / 2, EnemyShip4.m_w / 2))
		{
			PlayerShip.health -= EnemyShip4.enemyDamage;
			std::cout << "Health: " << PlayerShip.health << std::endl;
			//keepRunning = false;
		}

		//meteor collison
		if (Collision::CircleCollision(PlayerShip.m_x + PlayerShip.m_w / 2, PlayerShip.m_y + PlayerShip.m_h / 2, PlayerShip.m_w / 2,
										Meteor1.m_x + Meteor1.m_w / 2, Meteor1.m_y + Meteor1.m_h / 2, Meteor1.m_w / 2))
		{
			PlayerShip.health -= Meteor1.meteorDamage;
			std::cout << "Health: " << PlayerShip.health << std::endl;
			//keepRunning = false;
		}
		if (Collision::CircleCollision(PlayerShip.m_x + PlayerShip.m_w / 2, PlayerShip.m_y + PlayerShip.m_h / 2, PlayerShip.m_w / 2,
										Meteor2.m_x + Meteor2.m_w / 2, Meteor2.m_y + Meteor2.m_h / 2, Meteor2.m_w / 2))
		{
			PlayerShip.health -= Meteor2.meteorDamage;
			std::cout << "Health: " << PlayerShip.health << std::endl;
			//keepRunning = false;
		}
		if (Collision::CircleCollision(PlayerShip.m_x + PlayerShip.m_w / 2, PlayerShip.m_y + PlayerShip.m_h / 2, PlayerShip.m_w / 2,
			Meteor3.m_x + Meteor3.m_w / 2, Meteor3.m_y + Meteor3.m_h / 2, Meteor3.m_w / 2))
		{
			PlayerShip.health -= Meteor3.meteorDamage;
			std::cout << "Health: " << PlayerShip.health << std::endl;
			//keepRunning = false;
		}

		//comet collision
		if (Collision::CircleCollision(PlayerShip.m_x + PlayerShip.m_w / 2, PlayerShip.m_y + PlayerShip.m_h / 2, PlayerShip.m_w / 2,
			Comet1.m_x + Comet1.m_w / 2, Comet1.m_y + Comet1.m_h / 2, Comet1.m_w / 2))
		{
			PlayerShip.health -= Comet1.cometDamage;
			std::cout << "Health: " << PlayerShip.health << std::endl;
			//keepRunning = false;
		}
		if (Collision::CircleCollision(PlayerShip.m_x + PlayerShip.m_w / 2, PlayerShip.m_y + PlayerShip.m_h / 2, PlayerShip.m_w / 2,
			Comet2.m_x + Comet2.m_w / 2, Comet2.m_y + Comet2.m_h / 2, Comet2.m_w / 2))
		{
			PlayerShip.health -= Comet2.cometDamage;
			std::cout << "Health: " << PlayerShip.health << std::endl;
			//keepRunning = false;
		}
		if (Collision::CircleCollision(PlayerShip.m_x + PlayerShip.m_w / 2, PlayerShip.m_y + PlayerShip.m_h / 2, PlayerShip.m_w / 2,
			Comet3.m_x + Comet3.m_w / 2, Comet3.m_y + Comet3.m_h / 2, Comet3.m_w / 2))
		{
			PlayerShip.health -= Comet3.cometDamage;
			std::cout << "Health: " << PlayerShip.health << std::endl;
			//keepRunning = false;
		}

		//HP Pick up Collison
		if (Collision::CircleCollision(PlayerShip.m_x + PlayerShip.m_w / 2, PlayerShip.m_y + PlayerShip.m_h / 2, PlayerShip.m_w / 2,
			HP1.m_x + HP1.m_w / 2, HP1.m_y + HP1.m_h / 2, HP1.m_w / 2))
		{
			PlayerShip.health += HP1.HpPickUpVal;
			if (PlayerShip.health >= PlayerShip.maxHealth)
			{
				PlayerShip.health = PlayerShip.maxHealth;
			}
			
			std::cout << "Health: " << PlayerShip.health << std::endl;
			//keepRunning = false;
		}

		HealthStr = std::to_string(PlayerShip.health);
		SDL_Surface* HealthNum = TTF_RenderText_Blended(g_font, HealthStr.c_str(), { 255, 255, 255, 255 });
		SDL_Texture* HealthNumTexture = SDL_CreateTextureFromSurface(g_sdlRenderer, HealthNum);
		SDL_FreeSurface(HealthNum);

		if (PlayerShip.health <= PlayerShip.minHealth)
		{
			PlayerShip.dead();
						
		}

		
		
#pragma endregion

#pragma region Rendering
//Rendering
		//Clear the rendering context
		SDL_RenderClear(g_sdlRenderer);
		
		Background1.Draw(g_sdlRenderer);
		
		//Render the player ship
		PlayerShip.Draw(g_sdlRenderer);
		PlayerShip.timeInAnimationState = SDL_GetTicks() / 1000.0f;
		PlayerShip.ShipBounds();
		Lasers.Draw(g_sdlRenderer);	
		

		//Render objects
		EnemyShip1.Draw(g_sdlRenderer);
		EnemyShip2.Draw(g_sdlRenderer);
		EnemyShip3.Draw(g_sdlRenderer);
		EnemyShip4.Draw(g_sdlRenderer);
		Meteor1.Draw(g_sdlRenderer);
		Meteor2.Draw(g_sdlRenderer);	
		Meteor3.Draw(g_sdlRenderer);	
		Comet1.Draw(g_sdlRenderer);	
		Comet2.Draw(g_sdlRenderer);
		Comet3.Draw(g_sdlRenderer);
		HP1.Draw(g_sdlRenderer);
		
		
		//Text Rendering
		SDL_Rect RemEnRect{ 5, 75, 200, 28 };
		SDL_RenderCopy(g_sdlRenderer, RemEnTexture, NULL, &RemEnRect);
		SDL_Rect RemEnNumRect{ 200, 75, 30, 28 };
		SDL_RenderCopy(g_sdlRenderer, enemyNumTexture, NULL, &RemEnNumRect);	

		SDL_Rect HealthTxtRect{ 5, 110, 100, 28 };
		SDL_RenderCopy(g_sdlRenderer, HealthTexture, NULL, &HealthTxtRect);
		SDL_Rect HealthNumRect{ 100, 110, 30, 28 };
		SDL_RenderCopy(g_sdlRenderer, HealthNumTexture, NULL, &HealthNumRect);

		/*SDL_Rect GameOverRect{ 400, 300, 100, 28 };
		SDL_RenderCopy(g_sdlRenderer, GOverTexture, NULL, &GameOverRect);*/

		if (PlayerShip.health <= PlayerShip.minHealth) 
		{
			
			SDL_Surface* gameOverSurface = TTF_RenderText_Blended(g_font, "GAME OVER", { 255, 0, 0, 255 });
			SDL_Texture* gameOverTexture = SDL_CreateTextureFromSurface(g_sdlRenderer, gameOverSurface);
			SDL_FreeSurface(gameOverSurface);

			SDL_Rect gameOverRect = { 230, 450, 300, 56 };
			SDL_RenderCopy(g_sdlRenderer, gameOverTexture, nullptr, &gameOverRect);
			SDL_DestroyTexture(gameOverTexture);
			HP1.HpPickUpVal = 0;
			SDL_DestroyTexture(P_Ship);
			
		}
		

				
		//Update the screen with the state of the render target
		SDL_RenderPresent(g_sdlRenderer);
		//Halt execution for 16 milliseconds (approx 60 fps)
		SDL_Delay(25);
#pragma endregion

		
	};	
		
#pragma region Clean Up
//Clean Up
	SDL_DestroyTexture(P_Ship);	
	SDL_DestroyTexture(_Laser);	
	SDL_DestroyTexture(_Background1);	
	SDL_DestroyTexture(E_Ship1);
	SDL_DestroyTexture(E_Ship2);
	SDL_DestroyTexture(E_Ship3);
	SDL_DestroyTexture(E_Ship4);
	SDL_DestroyTexture(_Meteors1);
	SDL_DestroyTexture(_Meteors2);	
	SDL_DestroyTexture(_Meteors3);	
	SDL_DestroyTexture(_Comet1);	
	SDL_DestroyTexture(_Comet2);	
	SDL_DestroyTexture(_Comet3);	
	SDL_DestroyTexture(_HP1);
	SDL_DestroyTexture(RemEnTexture);	
	SDL_DestroyTexture(enemyNumTexture);	
	SDL_DestroyTexture(HealthTexture);
	SDL_DestroyTexture(HealthNumTexture);
	SDL_DestroyTexture(GOverTexture);
	Mix_FreeChunk(LaserSFX);
	Mix_FreeMusic(Music);
	
	CleanUp();
#pragma endregion

	
	return 0;
}
