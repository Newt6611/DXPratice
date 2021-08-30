#pragma once

class Editor;

class Timer
{
public:
	Timer();
	~Timer();

	void Update();

public:
	static float DeltaTime;
	static int FPS;

private:
	double m_DeltaTime;
	__int64 m_FPS;

	double m_PreTime;
	double m_SecondsPerCount;

	double m_FPS_BTW;
	int mc_FPS; // counter ++

	friend class Editor;
};