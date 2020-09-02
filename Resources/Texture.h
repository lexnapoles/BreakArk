//Texture class

#ifndef TEXTURE_H
#define	TEXTURE_H

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

class Texture
{
public:
	//Initializes variables
	Texture();

	//Deallocates memory
	~Texture();

	//Loads image at specified path
	bool LoadFromFile(const std::string path, SDL_Renderer *renderer);


	//Creates image from font string
#ifdef _SDL_TTF_H
	bool LoadFromRenderedText(const std::string textureText, const SDL_Color textColor, SDL_Renderer *renderer, TTF_Font *font);
#endif

	//Deallocates texture
	void Free();

	//Set color modulation
	void SetColor(const Uint8 red, const Uint8 green,  const Uint8 blue);

	//Set blending
	void SetBlendMode(const SDL_BlendMode blending);

	//Set alpha modulation
	void SetAlpha(const Uint8 alpha);

	//Renders texture at given point
	void Render( const int x, const int y, SDL_Renderer *renderer, SDL_RendererFlip flip = SDL_FLIP_NONE, SDL_Rect *clip = NULL, SDL_Point *center = NULL, double angle = 0.0);

	//Gets image dimensions
	int GetWidth();
	int GetHeight();

private:
	//The texture
	SDL_Texture* texture;

	//Image dimensions
	int width;
	int height;
};


#endif /* TEXTURE_H */

