#ifndef COUNTER_H
#define	COUNTER_H

#include "..\Resources\Object.h"
#include <sstream>
#include <iostream>
#include <string>

class Counter : public Object
{
public:
	Counter(int posX, int posY);
	~Counter();

	void Render(SDL_Renderer* renderer);
	void UpdateCounter(int value, std::string text,  SDL_Renderer* renderer);

private:
	static const int FONT_SIZE = 20;
	int posX, posY;

	TTF_Font *font;
	SDL_Color textColor;

	void ShiftCollider() {}
};

#endif	/* COUNTER_H */