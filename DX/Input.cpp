#include "Input.h"
#include "Log.h"

const Uint8* Input::keyboard_state;
int Input::mouseX;
int Input::mouseY;
float Input::mouseWheelY;

bool Input::IsKeyDown(SDL_Scancode code)
{
	return keyboard_state[code];
}

bool Input::MouseWheelYUp()
{
	return mouseWheelY == 1;
}

bool Input::MouseWheelYUDown()
{
	return mouseWheelY == -1;
}

void Input::Update()
{
	keyboard_state = SDL_GetKeyboardState(NULL);
	SDL_GetRelativeMouseState(&mouseX, &mouseY);
}