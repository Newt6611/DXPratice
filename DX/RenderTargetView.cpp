#include "RenderTargetView.h"
#include "Renderer.h"


RenderTargetView::RenderTargetView()
{
	IDXGISwapChain* swap_chain = Renderer::Get()->GetSwapChain();
	ID3D11Device* device = Renderer::Get()->GetDevice();

	ID3D11Texture2D* backbuffer;
	HRESULT result = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbuffer);
	if (result == S_OK)
	{
		device->CreateRenderTargetView(backbuffer, NULL, &m_RenderTargetView);
	}
	else
	{
		LogError("Failed When Creating RenderTargetView !");
	}
}

RenderTargetView::~RenderTargetView()
{
	m_RenderTargetView->Release();
}

void RenderTargetView::SetClearColor(float color[4])
{
	m_ClearColor[0] = color[0];
	m_ClearColor[1] = color[1];
	m_ClearColor[2] = color[2];
	m_ClearColor[3] = color[3];
}

void RenderTargetView::Bind()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->OMSetRenderTargets(1, &m_RenderTargetView, NULL);
}

void RenderTargetView::Clear()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->ClearRenderTargetView(m_RenderTargetView, m_ClearColor);
	
}