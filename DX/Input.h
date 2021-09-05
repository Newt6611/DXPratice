#pragma once

#include <SDL.h>

class World;

class Input
{
public:
	static void Update();

	static bool IsKeyDown(SDL_Scancode code);
	static bool MouseWheelYUp();
	static bool MouseWheelYUDown();

	static int mouseX;
	static int mouseY;
private:
	static const Uint8* keyboard_state;
	static float mouseWheelY;

	friend class World;
};