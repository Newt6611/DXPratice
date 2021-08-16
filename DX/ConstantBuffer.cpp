#include "ConstantBuffer.h"
#include "Renderer.h"

ConstantBuffer::ConstantBuffer()
{
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = sizeof(C_PerObj);
	buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;

	ID3D11Device* device = Renderer::Get()->GetDevice();
	HRESULT result = device->CreateBuffer(&buffer_desc, nullptr, &m_PerObjBuffer);
	if (result != S_OK)
	{
		LogError("Failed When Creating Constant Buffer !");
	}

	m_PerObjData = new C_PerObj();
}



ConstantBuffer::~ConstantBuffer()
{
	m_PerObjBuffer->Release();
	delete m_PerObjData;
}

void ConstantBuffer::BindPerObj()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();

	context->VSSetConstantBuffers(0, 1, &m_PerObjBuffer);

	D3D11_MAPPED_SUBRESOURCE map_data;
	ZeroMemory(&map_data, sizeof(D3D11_MAPPED_SUBRESOURCE));

	HRESULT result = context->Map(m_PerObjBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &map_data);

	CopyMemory(map_data.pData, m_PerObjData, sizeof(C_PerObj));
	context->Unmap(m_PerObjBuffer, 0);
}
