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
#include "Timer.h"
#include "Laser.h"
#include "Comet.h"


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


	SDL_Texture* _Meteors1 = LoadTexture("Assets/Meteor.png");
	Meteor Meteor1{ _Meteors1 };
	SDL_Texture* _Meteors2 = LoadTexture("Assets/Meteor.png");
	Meteor Meteor2{ _Meteors2 };

	SDL_Texture* _Comet1 = LoadTexture("Assets/Comet.png");
	Comet Comet1{ _Comet1 };
	SDL_Texture* _Comet2 = LoadTexture("Assets/Comet.png");
	Comet Comet2{ _Comet2 };


	SDL_Texture* Background = LoadTexture("Assets/background.png");

	SDL_Texture* _Laser = LoadTexture("Assets/pBullet1.png");
	Laser Lasers{ _Laser };

	//Load Sound Effects
	Mix_Chunk* LaserSFX = Mix_LoadWAV("Assets/laser4.mp3");
	//Load Music File
	Mix_Music* Music = Mix_LoadMUS("Music/Music2.mp3");
	//Play Music with inifinte looping
	Mix_PlayMusic(Music, -1);

		
	// Timer title
	SDL_Surface* textSurface = TTF_RenderText_Blended(g_font, "Time: ", {255,255,255,255});
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(g_sdlRenderer, textSurface);
	SDL_FreeSurface(textSurface);
	
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
			
			
			EnemyShip1.MoveDown()* deltaTime;
			EnemyShip1.resetEnPos();
			EnemyShip2.MoveDown()* deltaTime;
			EnemyShip2.resetEnPos();
			EnemyShip3.MoveDown()* deltaTime;
			EnemyShip3.resetEnPos();

			Meteor1.MoveDown()* deltaTime;
			Meteor1.resetMetPos();
			Meteor2.MoveDown()* deltaTime;
			Meteor2.resetMetPos();

			Comet1.MoveDown()* deltaTime;
			Comet1.resetCometPos();	
			Comet2.MoveDown()* deltaTime;
			Comet2.resetCometPos();


			Lasers.Move()* deltaTime;
			//Lasers.m_x = PlayerShip.m_x;
			//Lasers.m_y = PlayerShip.m_y;

		}		

		//Collision		
		if (Collision::CircleCollision(PlayerShip.m_x + PlayerShip.m_w / 2,   PlayerShip.m_y + PlayerShip.m_h/2,    PlayerShip.m_w/2,
										EnemyShip1.m_x + EnemyShip1.m_w/2, EnemyShip1.m_y + EnemyShip1.m_h/2,  EnemyShip1.m_w/2))
		{
			std::cout << "Collision Detected" << std::endl;
			//keepRunning = false;
		}
		if (Collision::CircleCollision(PlayerShip.m_x + PlayerShip.m_w / 2, PlayerShip.m_y + PlayerShip.m_h / 2, PlayerShip.m_w / 2,
										EnemyShip2.m_x + EnemyShip2.m_w / 2, EnemyShip2.m_y + EnemyShip2.m_h / 2, EnemyShip2.m_w / 2))
		{
			std::cout << "Collision Detected" << std::endl;
			//keepRunning = false;
		}

		if (Collision::CircleCollision(PlayerShip.m_x + PlayerShip.m_w / 2, PlayerShip.m_y + PlayerShip.m_h / 2, PlayerShip.m_w / 2,
										Meteor1.m_x + Meteor1.m_w / 2, Meteor1.m_y + Meteor1.m_h / 2, Meteor1.m_w / 2))
		{
			std::cout << "Collision Detected" << std::endl;
			//keepRunning = false;
		}
		if (Collision::CircleCollision(PlayerShip.m_x + PlayerShip.m_w / 2, PlayerShip.m_y + PlayerShip.m_h / 2, PlayerShip.m_w / 2,
										Meteor2.m_x + Meteor2.m_w / 2, Meteor2.m_y + Meteor2.m_h / 2, Meteor2.m_w / 2))
		{
			std::cout << "Collision Detected" << std::endl;
			//keepRunning = false;
		}


		//Rendering
		//Clear the rendering context
		SDL_RenderClear(g_sdlRenderer);
		//Render the background		
		SDL_Rect BackgroundRect{0,0,750,960};
		SDL_RenderCopy(g_sdlRenderer, Background, NULL, &BackgroundRect);

		//Render the player ship
		PlayerShip.Draw(g_sdlRenderer);
		PlayerShip.timeInAnimationState = SDL_GetTicks() / 1000.0f;

		Lasers.Draw(g_sdlRenderer);	
		

		//Render the enemy ships and meteors
		EnemyShip1.Draw(g_sdlRenderer);
		EnemyShip2.Draw(g_sdlRenderer);
		EnemyShip3.Draw(g_sdlRenderer);
		Meteor1.Draw(g_sdlRenderer);
		Meteor2.Draw(g_sdlRenderer);	
		Comet1.Draw(g_sdlRenderer);	
		Comet2.Draw(g_sdlRenderer);
		
		PlayerShip.ShipBounds();
		//Text Rendering
		SDL_Rect fontDstRect{ 5, 50, 100, 32 };
		SDL_RenderCopy(g_sdlRenderer, textTexture, NULL, &fontDstRect);
				
		//Update the screen with the state of the render target
		SDL_RenderPresent(g_sdlRenderer);
		//Halt execution for 16 milliseconds (approx 60 fps)
		SDL_Delay(25);
	};	
		

	//Clean Up
	SDL_DestroyTexture(P_Ship);	
	SDL_DestroyTexture(_Laser);	
	SDL_DestroyTexture(Background);	
	SDL_DestroyTexture(E_Ship1);
	SDL_DestroyTexture(E_Ship2);
	SDL_DestroyTexture(E_Ship3);
	SDL_DestroyTexture(_Meteors1);
	SDL_DestroyTexture(_Meteors2);	
	SDL_DestroyTexture(_Comet1);	
	SDL_DestroyTexture(_Comet2);	
	//SDL_DestroyTexture(textTexture);
	Mix_FreeChunk(LaserSFX);
	Mix_FreeMusic(Music);
	
	CleanUp();
	return 0;
}
