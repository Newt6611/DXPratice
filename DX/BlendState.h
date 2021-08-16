#pragma once

#include <d3d11.h>
#include "Log.h"


class BlendState
{
public:
	BlendState();
	~BlendState();

	inline ID3D11BlendState* GetBlendState() const { return m_BlendState; }

	void Bind();

private:
	ID3D11BlendState* m_BlendState;
};