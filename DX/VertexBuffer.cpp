#include "VertexBuffer.h"
#include "Renderer.h"
#include "Display.h"

VertexBuffer::VertexBuffer(VertexData* data, int count)
	: m_Count(count)
{
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.ByteWidth = sizeof(VertexData) * count;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data;
	init_data.pSysMem = data;
	init_data.SysMemPitch = 0;
	init_data.SysMemSlicePitch = 0;

	ID3D11Device* device = Renderer::Get()->GetDevice();
	HRESULT result = device->CreateBuffer(&buffer_desc, &init_data, &m_VertexBuffer);
	if (result != S_OK)
	{
		LogError("Failed When Creating IndexBuffer !");
	}
}

VertexBuffer::~VertexBuffer()
{
	m_VertexBuffer->Release();
}

void VertexBuffer::Bind()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();

	UINT stride = sizeof(VertexData);
	UINT offset = 0;

	context->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
}