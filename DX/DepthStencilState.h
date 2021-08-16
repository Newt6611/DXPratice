#pragma once

#include <d3d11.h>
#include "Log.h"

class DepthStencilState
{
public:
	DepthStencilState();
	~DepthStencilState();

private:
	ID3D11DepthStencilState* m_DepthStencilState;
};