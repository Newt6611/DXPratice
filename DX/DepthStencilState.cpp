#include "DepthStencilState.h"
#include "Display.h"
#include "Renderer.h"
#include "Log.h"

DepthStencilState::DepthStencilState()
{
	InitDepthStencilState();
	InitDepthStencilView(800, 600);
	InitShadow();
}

DepthStencilState::~DepthStencilState()
{
	m_DepthStencilState->Release();
	m_DepthStencilView->Release();

	m_ShadowSRV->Release();
	m_ShadowView->Release();
}

void DepthStencilState::Clear()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
}

void DepthStencilState::ClearShadow()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->ClearDepthStencilView(m_ShadowView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0.0f);

}

void DepthStencilState::Bind()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->OMSetDepthStencilState(m_DepthStencilState, 0);
}

void DepthStencilState::BindShadow()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->OMSetRenderTargets(0, NULL, m_ShadowView);
}

void DepthStencilState::InitDepthStencilView(float width, float height)
{
	if (m_Width == width && m_Height == height)
		return;

	m_Width = width;
	m_Height = height;

	ID3D11Device* device = Renderer::Get()->GetDevice();
	if(m_DepthStencilView)
		m_DepthStencilView->Release();
	
	D3D11_TEXTURE2D_DESC texture_desc;
	ZeroMemory(&texture_desc, sizeof(D3D11_TEXTURE2D_DESC));
	texture_desc.Width = m_Width;
	texture_desc.Height = m_Height;
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
	ZeroMemory(&depth_stencil_view_desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
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

void DepthStencilState::InitShadow()
{
	ID3D11Device* device = Renderer::Get()->GetDevice();

	int width = 1024;
	int height = 1024;
	D3D11_TEXTURE2D_DESC texture_desc = {};
	ZeroMemory(&texture_desc, sizeof(D3D11_TEXTURE2D_DESC));
	texture_desc.Width = m_Width;
	texture_desc.Height = m_Height;
	texture_desc.MipLevels = 1;
	texture_desc.Format = DXGI_FORMAT_R32_TYPELESS;
	texture_desc.SampleDesc.Count = 1;
	texture_desc.SampleDesc.Quality = 0;
	texture_desc.ArraySize = 1;
	texture_desc.Usage = D3D11_USAGE_DEFAULT;
	texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL;
	texture_desc.CPUAccessFlags = 0;
	texture_desc.MiscFlags = 0;

	D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc = {};
	ZeroMemory(&dsv_desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsv_desc.Format = DXGI_FORMAT_D32_FLOAT;
	dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsv_desc.Texture2D.MipSlice = 0;
	dsv_desc.Flags = 0;

	D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
	srv_desc.Format = DXGI_FORMAT_R32_FLOAT;
	srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srv_desc.Texture2D.MipLevels = texture_desc.MipLevels;
	srv_desc.Texture2D.MostDetailedMip = 0;

	ID3D11Texture2D* texture;
	HRESULT result = device->CreateTexture2D(&texture_desc, NULL, &texture);
	if (result != S_OK)
	{
		LogError("Failed When Creating Shadow Texture !");
	}

	result = device->CreateDepthStencilView(texture, &dsv_desc, &m_ShadowView);
	if (result != S_OK)
	{
		LogError("Failed When Creating Shadow DSV");
	}

	result = device->CreateShaderResourceView(texture, &srv_desc, &m_ShadowSRV);
	if (result != S_OK)
	{
		LogError("Failed When Creating Shadow SRV");
	}

	texture->Release();
}

void DepthStencilState::InitDepthStencilState()
{
	ID3D11Device* device = Renderer::Get()->GetDevice();

	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
	ZeroMemory(&depth_stencil_desc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depth_stencil_desc.DepthEnable = true;
	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	
	HRESULT result = device->CreateDepthStencilState(&depth_stencil_desc, &m_DepthStencilState);
	if (result != S_OK)
	{
		LogError("Failed When Creating DepthStencilState !");
	}
}