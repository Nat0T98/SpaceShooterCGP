#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "Ship.h"
#include "Collision.h"
#include "Enemy.h"


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

	SDL_Texture* E_Ship = LoadTexture("Assets/enemyRed.png");	
	Enemy EnemyShip{ E_Ship };


	SDL_Texture* Background = LoadTexture("Assets/background.png");	
	

	//Load Sound Effects
	Mix_Chunk* LaserSFX = Mix_LoadWAV("Assets/laser4.mp3");
	//Load Music File
	Mix_Music* Music = Mix_LoadMUS("Music/Music2.mp3");
	//Play Music with inifinte looping
	Mix_PlayMusic(Music, -1);

	//Load Fonts
	/*SDL_Surface* textSurface = TTF_RenderText_Blended(g_font, "Hello World", { 255,255,255,255 });
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(g_sdlRenderer, textSurface);
	SDL_FreeSurface(textSurface);*/
	
	

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
					//PlayerShip.Shoot()
				}
				break;

			case SDL_MOUSEMOTION:
				
				PlayerShip.m_x = sdlEvent.motion.x;
				PlayerShip.m_y = sdlEvent.motion.y;
				break;

			default:
				break;
			}
		}		

		//Collision
		
		if (Collision::CircleCollision(PlayerShip.m_x + PlayerShip.m_w / 2,   PlayerShip.m_y + PlayerShip.m_h/2,    PlayerShip.m_w/2,
										EnemyShip.m_x + EnemyShip.m_w/2, EnemyShip.m_y + EnemyShip.m_h/2,  EnemyShip.m_w/2))
		{
			std::cout << "Collision Detected" << std::endl;
			//keepRunning = false;

		}


		//Rendering
		//Clear the rendering context
		SDL_RenderClear(g_sdlRenderer);
		//Render the background		
		SDL_Rect BackgroundRect{ 0,0,750,960 };
		SDL_RenderCopy(g_sdlRenderer, Background, NULL, &BackgroundRect);

		//Render the player ship
		PlayerShip.Draw(g_sdlRenderer);
		PlayerShip.timeInAnimationState = SDL_GetTicks() / 1000.0f;
		

		//Render the enemy ship
		EnemyShip.Draw(g_sdlRenderer);
		
		//Text Rendering
		/*SDL_Rect fontDstRect{ 25, 100, 300, 32 };
		SDL_RenderCopy(g_sdlRenderer, textTexture, NULL, &fontDstRect);*/
				
		//Update the screen with the state of the render target
		SDL_RenderPresent(g_sdlRenderer);

		//Halt execution for 16 milliseconds (approx 60 fps)
		SDL_Delay(25);
	};	
		

	//Clean Up
	SDL_DestroyTexture(P_Ship);
	SDL_DestroyTexture(Background);	
	SDL_DestroyTexture(E_Ship);
	//SDL_DestroyTexture(textTexture);
	Mix_FreeChunk(LaserSFX);
	Mix_FreeMusic(Music);
	
	CleanUp();
	return 0;
}
//
//#include "SpaceShooter.hpp"
//#include "Player.class.hpp"
//#include "Background.class.hpp"
//
//bool	init(t_settings& settings) {
//	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
//		std::cout << SDL_GetError() << std::endl;
//		return false;
//	}
//	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
//		std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
//	settings.window = SDL_CreateWindow("Space Shooter",
//		SDL_WINDOWPOS_UNDEFINED,
//		SDL_WINDOWPOS_UNDEFINED,
//		WINDOW_WIDTH,
//		WINDOW_HEIGHT + INFOBOX_HEIGHT,
//		SDL_WINDOW_SHOWN);
//
//
//	if (settings.window == NULL) {
//		std::cout << SDL_GetError() << std::endl;
//		return false;
//	}
//	settings.renderer = SDL_CreateRenderer(settings.window, -1, SDL_RENDERER_ACCELERATED);
//	if (settings.renderer == NULL) {
//		std::cout << SDL_GetError() << std::endl;
//		return false;
//	}
//	SDL_SetRenderDrawColor(settings.renderer, 0x61, 0x23, 0x7A, 0xFF);
//	int imgFlags = IMG_INIT_PNG;
//	if (!(IMG_Init(imgFlags) & imgFlags)) {
//		std::cout << IMG_GetError() << std::endl;
//		return false;
//	}
//	if (TTF_Init() == -1) {
//		std::cout << TTF_GetError() << std::endl;
//		return false;
//	}
//	return true;
//}
//
//void	close(t_settings& settings, Player& player) {
//	player.free();
//
//	SDL_DestroyRenderer(settings.renderer);
//	SDL_DestroyWindow(settings.window);
//	settings.renderer = NULL;
//	settings.window = NULL;
//
//	TTF_Quit();
//	IMG_Quit();
//	SDL_Quit();
//}
//
//int		main(int ac, char* av[]) {
//	Background background;
//	t_settings settings;
//	srand(time(0));
//
//	settings.window = NULL;
//	settings.renderer = NULL;
//
//	if (!init(settings))
//		std::cout << "Failed to initialize!" << std::endl;
//
//	Player	player;
//	if (!player.load(PLAYER_IMG, settings))
//		std::cout << "Failed to load Player image" << std::endl;
//	else {
//		bool quit = false;
//		SDL_Event event;
//		unsigned long ticks = 0;
//		while (!quit) {
//			while (SDL_PollEvent(&event) != 0) {
//				if (event.type == SDL_QUIT)
//					quit = true;
//				else if (event.type == SDL_KEYDOWN) {
//					switch (event.key.keysym.sym) {
//					case SDLK_LEFT: case SDLK_a:	player.moveLeft(); break;
//					case SDLK_RIGHT: case SDLK_d:	player.moveRight(); break;
//					case SDLK_UP: case SDLK_w:		player.moveUp(); break;
//					case SDLK_DOWN: case SDLK_s:	player.moveDown(); break;
//					case SDLK_SPACE:				player.shoot(settings); break;
//					case SDLK_ESCAPE: quit = true;
//					default: break;
//					}
//				}
//			}
//			if (ticks % (STAR_HEIGHT * 5) == 0)
//				background.makeStar(settings);
//
//			if (ticks % (METEOR_HEIGHT * 20) == 0)
//				background.makeMeteor(settings);
//
//			if (ticks % (ENEMY_HEIGHT * 24) == 0)
//				background.makeEnemy(settings);
//
//			background.killEnemy(player);
//			background.killMeteor(player);
//
//			if (background.hitEnemy(player) || background.hitMeteor(player)) {
//				SDL_SetRenderDrawColor(settings.renderer, 0x61, 0x23, 0x7A, 0xFF);
//				SDL_RenderClear(settings.renderer);
//				background.loadGameOver(GAME_OVER, settings);
//				SDL_RenderPresent(settings.renderer);
//				SDL_Delay(2000);
//				break;
//			}
//
//			SDL_SetRenderDrawColor(settings.renderer, 0x61, 0x23, 0x7A, 0xFF);
//			SDL_RenderClear(settings.renderer);
//
//			background.displayStar(settings);
//			background.displayMeteor(settings, (ticks % 2 == 0));
//			background.displayEnemy(settings, (ticks % (ENEMY_HEIGHT / 2) == 0));
//
//			player.render(settings);
//			player.moveBullets(settings);
//
//			background.drawInfoBox(player, settings, ticks / 100);
//			SDL_RenderPresent(settings.renderer);
//			ticks++;
//		}
//	}
//	close(settings, player);
//}
