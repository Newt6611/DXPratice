#pragma once

#include <d3d11.h>
#include <memory>
#include <DirectXMath.h>
#include "Log.h"

using namespace DirectX;


// Constant Buffer Type //
struct VS_Object
{
	XMMATRIX World = XMMatrixIdentity();
	XMMATRIX View = XMMatrixIdentity();
	XMMATRIX Projection = XMMatrixIdentity();
	XMFLOAT4 color = XMFLOAT4(1, 1, 1, 1);
};

// Light 
struct Directional_Light
{
	XMFLOAT4 Color = XMFLOAT4(1, 1, 1, 1);
	XMFLOAT3 Ambient = XMFLOAT3(1, 1, 1);
	float pad = 0;
	
	XMFLOAT3 Diffuse = XMFLOAT3(1, 1, 1);
	float pad1 = 0;

	XMFLOAT3 Specular = XMFLOAT3(1, 1, 1);
	float pad2 = 0;

	XMFLOAT3 Direction = XMFLOAT3(0, 0, 1);
	float pad3 = 0;
};

struct Point_Light
{
	XMFLOAT4 Color = XMFLOAT4(1, 1, 1, 1);
	XMFLOAT3 Position = XMFLOAT3(0, 0, 0);
	float Constant = 1;
	
	XMFLOAT3 Ambient = XMFLOAT3(1, 1, 1);
	float Linear = 0.14;

	XMFLOAT3 Diffuse = XMFLOAT3(1, 1, 1);
	float Quadratic = 0.07;

	XMFLOAT3 Specular = XMFLOAT3(1, 1, 1);
	float pad = 0;
};


struct PS_PerFrame
{
	Directional_Light d_Light;
	Point_Light p_Light[4];
	XMFLOAT3 eyePos;
	float pad;
};


// Shader Stage //
enum ShaderStage
{
	VS = 0,
	PS
};

template<typename T>
using Ref = std::shared_ptr<T>;