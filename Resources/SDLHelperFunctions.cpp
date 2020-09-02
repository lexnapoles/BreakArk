#include "SDLHelperFunctions.h"


bool InitSDL(SDL_Window*& window, SDL_Renderer*& renderer, int screenWidth, int screenHeight)
{
//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			success = false;
		}

		//Create window
		window = SDL_CreateWindow( "BreakArk", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN );
		if( window == nullptr )
		{
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if( renderer == nullptr )
			{
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					success = false;
				}

				if (TTF_Init() < 0)
				{
					success = false;
				}

				if (SDLNet_Init() < 0)
				{
					success = false;
				}

			}
		}
	}

	return success;
}

void CloseSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
	//Destroy window	
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = nullptr;
	renderer = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
	SDLNet_Quit();
	SDL_Quit();
}

