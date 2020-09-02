#include "Texture.h"



Texture::Texture()
{
	//Initialize
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	//Deallocate
	Free();
}

bool Texture::LoadFromFile(const std::string path, SDL_Renderer *renderer)
{

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cerr << "Unable to load image: " <<  path.c_str() << "SDL_image Error: " <<  IMG_GetError() << std::endl;
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cerr << "Unable to create texture from: " << path.c_str() << "SDL Error : " << SDL_GetError() << std::endl;
		}

		else
		{
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	texture = newTexture;
	return texture != NULL;
}


#ifdef _SDL_TTF_H
bool Texture::LoadFromRenderedText(const std::string textureText, const  SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font)
{
	//Get rid of preexisting texture
	Free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == NULL)
		{
			std::cerr << "Unable to create texture from rendered text. SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			//Get image dimensions
			width = textSurface->w;
			height = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		std::cerr << "Unable to render text surface. SDL_ttf Error: " <<  TTF_GetError() << std::endl;
	}


	//Return success
	return texture != NULL;
}
#endif

void Texture::Free()
{
	//Free texture if it exists
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

void Texture::SetColor(const Uint8 red, const Uint8 green,  const Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(texture, red, green, blue);
}

void Texture::SetBlendMode(const SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(texture, blending);
}

void Texture::SetAlpha(const Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(texture, alpha);
}

void Texture::Render(const int x,  const int y, SDL_Renderer *renderer, SDL_RendererFlip flip, SDL_Rect *clip, SDL_Point *center, double angle)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

int Texture::GetWidth()
{
	return width;
}

int Texture::GetHeight()
{
	return height;
}
