#pragma once

#include <d3d11.h>

class SamplerState
{
public:
	SamplerState();
	~SamplerState();

	inline ID3D11SamplerState* GetState() const { return m_SamplerState; }

	void Bind();

private:
	ID3D11SamplerState* m_SamplerState;
};
