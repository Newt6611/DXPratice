#pragma once

#include <DirectXMath.h>

using namespace DirectX;

struct VS_Object
{
	XMMATRIX World;
	XMMATRIX View;
	XMMATRIX Projection;
	float pad;
};

struct PS_Object
{
	float alpha;
	XMFLOAT3 pad;
};