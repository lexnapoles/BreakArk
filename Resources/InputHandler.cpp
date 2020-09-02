#include "InputHandler.h"


InputHandler::InputHandler()
{
	ResetInput();
}

InputHandler::~InputHandler()
{
}


void InputHandler::ResetInput()
{
	userInput.esc = false;
	userInput.leftDown = false;
	userInput.leftUp = false;
	userInput.quit = false;
	userInput.enter = false;
	userInput.rightDown = false;
	userInput.rightUp = false;
	userInput.mouseDown = false;
	userInput.mousePosX = 0;
	userInput.mousePosY = 0;
}


bool InputHandler::HandleEvents()
{
	//Get input from events, If one of the keys we're looking for is activated event = true 

	while (SDL_PollEvent(&e) != 0)
	{
		ResetInput();

		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_LEFT:   userInput.leftDown = true; break;
			case SDLK_RIGHT:  userInput.rightDown = true; break;
			case SDLK_ESCAPE: userInput.esc = true; break;
			case SDLK_RETURN: userInput.enter = true; break;
			}

			return true;
		}

		//If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_LEFT:   userInput.leftUp = true; break;
			case SDLK_RIGHT:  userInput.rightUp = true;  break;
			case SDLK_ESCAPE: userInput.esc = false; break;
			case SDLK_RETURN: userInput.enter = false; break;
			}
			return true;
		}

		else if (e.type == SDL_QUIT)
		{
			userInput.quit = true;
			return true;
		}

		//If mouse event happened
		if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
		{
			//Get mouse position
			SDL_GetMouseState(&userInput.mousePosX, &userInput.mousePosY);
			//Get type of event;
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				userInput.mouseDown = true;
			}
			return true;
		}
	}

	return false;
}