#pragma once

#include <d3d11.h>

enum RasterzierStateType
{
	Solid = 0,
	WireFrame
};

class RasterzierState 
{
public:
	RasterzierState();
	~RasterzierState();

	void Bind();
	inline ID3D11RasterizerState* GetCurrentState() const { return m_CurrentState; }
	RasterzierState* SetState(RasterzierStateType type);

private:
	RasterzierStateType m_CurrentType;
	ID3D11RasterizerState* m_CurrentState;
	ID3D11RasterizerState* m_SolidState;
	ID3D11RasterizerState* m_WireFrameState;
};