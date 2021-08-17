#pragma once

#include <d3d11.h>
#include "Log.h"

enum BlendStateType
{
	None = 0,
	Transparency
};

class BlendState
{
public:
	BlendState();
	~BlendState();

	BlendStateType GetType() const { return m_CurrentType; }
	ID3D11BlendState* GetCurrentState() const { m_CurrentBlendState; }
	
	BlendState* SetBlendState(BlendStateType type);

	void Bind();

private:
	BlendStateType m_CurrentType;
	ID3D11BlendState* m_CurrentBlendState;
	ID3D11BlendState* m_NoneBlendState;
	ID3D11BlendState* m_TransparencyState;
};