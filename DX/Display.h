#pragma once

#include <Windows.h>

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

	inline HWND GetHandle() const { return m_handle; }

private:
	Display() {} 
	void InitWindow();

private:
	static Display* m_Instance;
	int m_width;
	int m_height;
	HINSTANCE m_instance;
	HWND m_handle;

};