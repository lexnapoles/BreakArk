#include "Counter.h"

Counter::Counter(int posX, int posY)
{
	this->posX = posX;
	this->posY = posY;

	//Open the font
	font = TTF_OpenFont("Font\\leadcoat.ttf", FONT_SIZE);

	textColor = { 255, 0, 0, 255 };
}

Counter::~Counter()
{
	TTF_CloseFont(font);
	font = nullptr;

}

void Counter::UpdateCounter(int value, std::string text, SDL_Renderer* renderer)
{
	std::stringstream ss;
	ss << text << value;

	InitTexture(renderer, ss.str(), textColor, font);
}

void Counter::Render(SDL_Renderer* renderer)
{
	objectTexture->Render(posX, posY, renderer);
}

