#include "Object.h"


Object::Object()
{
    objectTexture = new Texture();
}


Object::~Object()
{
	FreeTexture();
}

bool Object::InitTexture(SDL_Renderer *renderer, const std::string imagePath)
{
	return objectTexture->LoadFromFile(imagePath, renderer);
}

bool Object::InitTexture(SDL_Renderer* renderer, std::string textureText, const  SDL_Color textColor, TTF_Font* font)
{
	return objectTexture->LoadFromRenderedText(textureText, textColor, renderer, font);
}

void Object::FreeTexture()
{
	delete objectTexture;
	objectTexture = nullptr;
}