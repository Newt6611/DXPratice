#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include "ShaderStage.h"
#include "ConstantBufferType.h"


template<class T>
class ConstantBuffer
{
public:
	ConstantBuffer(){}
	~ConstantBuffer() {}

	void Init(ShaderStage stage, ID3D11Device* device, ID3D11DeviceContext* context)
	{
		m_ShaderStage = stage;
		this->device = device;
		this->context = context;

		D3D11_BUFFER_DESC buffer_desc;
		buffer_desc.ByteWidth = static_cast<UINT>(sizeof(T) + (16 - (sizeof(T) % 16)));
		buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		buffer_desc.MiscFlags = 0;
		buffer_desc.StructureByteStride = 0;

		HRESULT result = device->CreateBuffer(&buffer_desc, nullptr, &m_Buffer);
		if (result != S_OK)
		{
			LogError("Failed When Creating Constant Buffer !");
		}
	}

	void Bind(unsigned int slot)
	{
		D3D11_MAPPED_SUBRESOURCE map_data;
		ZeroMemory(&map_data, sizeof(D3D11_MAPPED_SUBRESOURCE));

		HRESULT r = context->Map(m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &map_data);
		if (r != S_OK)
			LogError("RRRR");

		CopyMemory(map_data.pData, &m_Data, sizeof(T));
		context->Unmap(m_Buffer, 0);

		switch (m_ShaderStage)
		{
		case ShaderStage::VS:
			context->VSSetConstantBuffers(slot, 1, &m_Buffer);
			break;
		case ShaderStage::PS:
			context->PSSetConstantBuffers(slot, 1, &m_Buffer);
			break;
		}
		
	}

	void SetData(T& data)
	{
		this->m_Data = data;
	}


private:
	ConstantBuffer(const ConstantBuffer<T>& rhs);

private:
	T m_Data;
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	ShaderStage m_ShaderStage;
	ID3D11Buffer* m_Buffer;
};
