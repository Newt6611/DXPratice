#pragma once

#include <Windows.h>
#include <SDL.h>
#include <SDL_syswm.h>

#include "Log.h"

class Display 
{
public:
	static Display* Get() {
		if (m_Instance == nullptr)
			m_Instance = new Display();
		return m_Instance;
	}

	Display(const Display &d) = delete;
	void operator=(const Display& d) = delete;

	void Init(int width, int height);

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }

	~Display();

	inline SDL_Window* GetWindow() { return m_Window; }
	inline HWND& GetHandle() { return m_handle; }
	inline HINSTANCE& GetInstance() { return m_instance; }

	void OnResize();

private:
	Display() {} 
	void InitWindow();

private:
	static Display* m_Instance;
	int m_width;
	int m_height;

	SDL_Window* m_Window;

	HINSTANCE m_instance;
	HWND m_handle;

};