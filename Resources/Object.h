#ifndef OBJECT_H
#define	OBJECT_H

#include <SDL.h>
#include "Texture.h"
#include "Integration.h"

class Object
{
public:
	Object();
	~Object();

	virtual void Render(SDL_Renderer *renderer) = 0;

	//Image to Texture
	bool InitTexture(SDL_Renderer* renderer, const std::string imagePath);
	//Text to Texture
	bool InitTexture(SDL_Renderer* renderer, std::string textureText, const  SDL_Color textColor, TTF_Font* font);
	
	void FreeTexture();
	
	virtual  void ShiftCollider() = 0;

protected:
	Texture* objectTexture;
        
};

#endif	/* OBJECT_H */