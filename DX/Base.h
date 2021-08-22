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

struct PS_PerFrame
{
	XMFLOAT3 eyePos;
	float pad;
};



// Light 
struct Directional_Light
{
	XMFLOAT4 Color = XMFLOAT4(1, 1, 1, 1);
	XMFLOAT3 Ambient = XMFLOAT3(1, 1, 1);
	float pad;
	
	XMFLOAT3 Diffuse = XMFLOAT3(1, 1, 1);
	float pad1;

	XMFLOAT3 Specular = XMFLOAT3(1, 1, 1);
	float pad2;

	XMFLOAT3 Direction = XMFLOAT3(0, 0, 1);
	float pad3;
};



// Shader Stage //
enum ShaderStage
{
	VS = 0,
	PS
};

template<typename T>
using Ref = std::shared_ptr<T>;