#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

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
	SDL_Texture* Texture = LoadTexture("Assets/door.png");
	//SDL_Texture* TextureC = LoadTexture("PlayerShip.bmp");

	//Load Sound Effects
	Mix_Chunk* coinsSFX = Mix_LoadWAV("Assets/Coin01.wav");
	//Load Music File
	Mix_Music* Music = Mix_LoadMUS("Assets/rng_lo-fi_loop.mp3");
	//Play Music with inifinte looping
	Mix_PlayMusic(Music, -1);

	//Load Fonts
	SDL_Surface* textSurface = TTF_RenderText_Blended(g_font, "Hello World", { 255,255,255,255 });
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(g_sdlRenderer, textSurface);
	SDL_FreeSurface(textSurface);
	
	int ShipX = 300;
	int ShipY = 800;

	bool keepRunning = true;
	while (keepRunning)
	{
		
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
					ShipY--;
				}
				else if (sdlEvent.key.keysym.sym == SDLK_a || sdlEvent.key.keysym.sym == SDLK_LEFT)
				{
					ShipX--;
				}
				else if (sdlEvent.key.keysym.sym == SDLK_s || sdlEvent.key.keysym.sym == SDLK_DOWN)
				{
					ShipY++;
				}
				else if (sdlEvent.key.keysym.sym == SDLK_d || sdlEvent.key.keysym.sym == SDLK_RIGHT)
				{
					ShipX++;
				}		
				break;

			case SDL_KEYUP:
				if (sdlEvent.key.keysym.sym == SDLK_BACKSPACE)
				{
					Mix_PlayChannel(-1, coinsSFX, 0);
				} 
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (sdlEvent.button.button == SDL_BUTTON_LEFT)
				{
					int x;
					int y;
					//SDL_GetRelativeMouseState(&x, &y);
					SDL_GetMouseState(&x, &y);
					//std::cout << "X pos is: " << x << "Y pos is: " << y << std::endl;
				}
				break;

			case SDL_MOUSEMOTION:
				//int mouseX = sdlEvent.motion.x;
				//int mouseY = sdlEvent.motion.y;
				//std::cout << "X pos is: " << sdlEvent.motion.x << " Y pos is: " << sdlEvent.motion.y << std::endl;
				ShipX = sdlEvent.motion.x;
				ShipY = sdlEvent.motion.y;
				break;

			default:
				break;
			}
		}		

		//Rendering
		//Clear the rendering context
		SDL_RenderClear(g_sdlRenderer);

		//Create a destination or where an image will be copied too
		SDL_Rect destinationRect{ 0 ,0,100,100 };
		//Copy the texture onto the rendering target
		SDL_RenderCopy(g_sdlRenderer, Texture, NULL, &destinationRect);
		//SDL_RenderCopy(g_sdlRenderer, TextureB, NULL, &destinationRectB);

		//Text Rendering
		SDL_Rect fontDstRect{ 25, 100, 300, 32 };
		SDL_RenderCopy(g_sdlRenderer, textTexture, NULL, &fontDstRect);
				
		//Update the screen with the state of the render target
		SDL_RenderPresent(g_sdlRenderer);

		//Halt execution for 16 milliseconds (approx 60 fps)
		SDL_Delay(25);
	};
						
	
	//Clean Up
	SDL_DestroyTexture(Texture);
	SDL_DestroyTexture(textTexture);
	Mix_FreeChunk(coinsSFX);
	Mix_FreeMusic(Music);
	
	CleanUp();
	return 0;
}