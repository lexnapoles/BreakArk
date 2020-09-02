#include <SDL.h>

#ifndef INPUTHANDLER_H
#define	INPUTHANDLER_H

struct UserInput
{
	bool rightDown; //Pressed right key
	bool rightUp;  //Unpressed right key
	bool leftDown;
	bool leftUp;
	bool esc; 
	bool quit;
	bool enter;
	bool mouseDown;
	int  mousePosX;
	int  mousePosY;
};

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	bool HandleEvents();
	UserInput& GetInput() { return userInput; }
private:
	UserInput userInput;
    SDL_Event e;	
	
    void ResetInput();

};

#endif	/* INPUTHANDLER_H */