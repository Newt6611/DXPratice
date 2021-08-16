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

	InitDepthStencilView();
}

RenderTargetView::~RenderTargetView()
{
	m_RenderTargetView->Release();
	m_DepthStencilView->Release();
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
	context->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);
}

void RenderTargetView::Clear()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->ClearRenderTargetView(m_RenderTargetView, m_ClearColor);
	context->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
}





void RenderTargetView::InitDepthStencilView()
{
	ID3D11Device* device = Renderer::Get()->GetDevice();

	D3D11_TEXTURE2D_DESC texture_desc;
	ZeroMemory(&texture_desc, sizeof(D3D11_TEXTURE2D_DESC));
	texture_desc.Width = Display::Get()->GetWidth();
	texture_desc.Height = Display::Get()->GetHeight();
	texture_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	texture_desc.MipLevels = 1;
	texture_desc.ArraySize = 1;
	texture_desc.CPUAccessFlags = 0;
	texture_desc.MiscFlags = 0;
	texture_desc.SampleDesc.Count = 1;
	texture_desc.SampleDesc.Quality = 0;
	texture_desc.Usage = D3D11_USAGE_DEFAULT;
	texture_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	ID3D11Texture2D* depth_texture;
	HRESULT result = device->CreateTexture2D(&texture_desc, 0, &depth_texture);
	if (result != S_OK)
	{
		LogError("Failed When Creating Depth Texture !");
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
	depth_stencil_view_desc.Format = texture_desc.Format;
	depth_stencil_view_desc.Flags = 0;
	depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depth_stencil_view_desc.Texture2D.MipSlice = 0;
	result = device->CreateDepthStencilView(depth_texture, &depth_stencil_view_desc, &m_DepthStencilView);
	if (result != S_OK)
	{
		LogError("Failed When Creating Depth Stencil View !");
	}

	depth_texture->Release();
}
