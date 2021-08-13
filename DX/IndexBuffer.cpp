#include "IndexBuffer.h"

#include "Renderer.h"
#include "Display.h"

IndexBuffer::IndexBuffer(UINT* indices, int count)
	: m_Count(count)
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

	ID3D11Device* device = Renderer::Get()->GetDevice();
	HRESULT result = device->CreateBuffer(&buffer_desc, &init_data, &m_Buffer);
	if (result != S_OK)
		MessageBox(Display::Get()->GetHandle(), L"Failed Create Vertex Buffer", L"Error", ERROR);
}

IndexBuffer::~IndexBuffer()
{
	m_Buffer->Release();
}

void IndexBuffer::Bind()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->IASetIndexBuffer(m_Buffer, DXGI_FORMAT_R32_UINT, 0);
}