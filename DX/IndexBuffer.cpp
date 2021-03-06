#include "IndexBuffer.h"

#include "Renderer.h"
#include "Display.h"

IndexBuffer::IndexBuffer(UINT* indices, int count, ID3D11Device* device, ID3D11DeviceContext* context)
	: m_Count(count), device(device), context(context)
{
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.Usage = D3D11_USAGE_IMMUTABLE;
	buffer_desc.ByteWidth = sizeof(UINT) * count;
	buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA init_data;
	init_data.pSysMem = indices;
	init_data.SysMemPitch = 0;
	init_data.SysMemSlicePitch = 0;

	HRESULT result = device->CreateBuffer(&buffer_desc, &init_data, &m_Buffer);
	if (result != S_OK)
	{
		LogError("Failed When Creating IndexBuffer !");
	}
}

IndexBuffer::~IndexBuffer()
{
	m_Buffer->Release();
}

void IndexBuffer::Bind()
{
	context->IASetIndexBuffer(m_Buffer, DXGI_FORMAT_R32_UINT, 0);
}