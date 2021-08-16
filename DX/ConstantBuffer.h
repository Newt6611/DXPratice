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

};

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	C_PerObj* GetPerObj() { return m_PerObjData; }

	void BindPerObj();

private:
	ID3D11Buffer* m_PerObjBuffer;
	C_PerObj* m_PerObjData;
};
