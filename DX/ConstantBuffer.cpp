#include "ConstantBuffer.h"
#include "Renderer.h"

ConstantBuffer::ConstantBuffer()
{
	ID3D11Device* device = Renderer::Get()->GetDevice();
	
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = sizeof(C_PerObj);
	buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;

	HRESULT result = device->CreateBuffer(&buffer_desc, nullptr, &m_PerObjBuffer);
	if (result != S_OK)
	{
		LogError("Failed When Creating Constant Buffer !");
	}

	buffer_desc.ByteWidth = sizeof(C_PixelObj);

	result = device->CreateBuffer(&buffer_desc, nullptr, &m_PerPixelBuffer);
	if (result != S_OK)
	{
		LogError("Failed When Creating Constant Buffer 2!");
	}

	m_PerObjData = new C_PerObj();
	m_PixelObjData = new C_PixelObj();
}



ConstantBuffer::~ConstantBuffer()
{
	m_PerObjBuffer->Release();
	m_PerPixelBuffer->Release();
	delete m_PerObjData;
	delete m_PixelObjData;
}

void ConstantBuffer::BindPerObj()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();

	context->VSSetConstantBuffers(0, 1, &m_PerObjBuffer);

	D3D11_MAPPED_SUBRESOURCE map_data;
	ZeroMemory(&map_data, sizeof(D3D11_MAPPED_SUBRESOURCE));

	context->Map(m_PerObjBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &map_data);

	CopyMemory(map_data.pData, m_PerObjData, sizeof(C_PerObj));
	context->Unmap(m_PerObjBuffer, 0);
}

void ConstantBuffer::BindPixel()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();

	context->PSSetConstantBuffers(0, 1, &m_PerPixelBuffer);
	D3D11_MAPPED_SUBRESOURCE map_data;
	ZeroMemory(&map_data, sizeof(D3D11_MAPPED_SUBRESOURCE));

	context->Map(m_PerPixelBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &map_data);

	CopyMemory(map_data.pData, m_PixelObjData, sizeof(C_PerObj));
	context->Unmap(m_PerPixelBuffer, 0);
}
