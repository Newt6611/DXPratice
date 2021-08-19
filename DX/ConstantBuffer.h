#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include "ShaderStage.h"
#include "ConstantBufferType.h"


template<class T>
class ConstantBuffer
{
public:
	ConstantBuffer(ShaderStage stage);
	~ConstantBuffer();

	void Bind(unsigned int slot);

	void SetData(T data);

	T m_Data;
private:
	ShaderStage m_ShaderStage;
	ID3D11Buffer* m_Buffer;
};
