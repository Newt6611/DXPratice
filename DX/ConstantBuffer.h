#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include "Log.h"

using namespace DirectX;

struct C_PerObj
{
	XMMATRIX World;
	XMMATRIX View;
	XMMATRIX Projection;
	float pad;
};

struct C_PixelObj
{
	float alpha = 1;
	float pad;
	float pad2;
	float pad3;
};

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	inline C_PerObj* GetPerObj() { return m_PerObjData; }
	inline C_PixelObj* GetPixelObj() { return m_PixelObjData; }

	void BindPerObj();
	void BindPixel();

private:
	ID3D11Buffer* m_PerObjBuffer;
	ID3D11Buffer* m_PerPixelBuffer;


	C_PerObj* m_PerObjData;
	C_PixelObj* m_PixelObjData;
};
