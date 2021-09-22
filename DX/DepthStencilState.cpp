#include "DepthStencilState.h"
#include "Display.h"
#include "Renderer.h"
#include "Log.h"

DepthStencilState::DepthStencilState()
{
	InitDepthStencilState();
	InitDepthStencilView(800, 600);
}

DepthStencilState::~DepthStencilState()
{
	m_DepthStencilState->Release();
	m_DepthStencilView->Release();
}

void DepthStencilState::Clear()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0.0f);
}

void DepthStencilState::Bind()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->OMSetDepthStencilState(m_DepthStencilState, 0);
}

void DepthStencilState::BindDepthSRV()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();

	if (m_SRV == nullptr)
		LogError("NNN");
	else
		context->PSSetShaderResources(3, 1, &m_SRV);
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
	//texture_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	texture_desc.Format = DXGI_FORMAT_R32_TYPELESS;
	texture_desc.MipLevels = 1;
	texture_desc.ArraySize = 1;
	texture_desc.CPUAccessFlags = 0;
	texture_desc.MiscFlags = 0;
	texture_desc.SampleDesc.Count = 1;
	texture_desc.SampleDesc.Quality = 0;
	texture_desc.Usage = D3D11_USAGE_DEFAULT;
	texture_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

	ID3D11Texture2D* depth_texture;
	HRESULT result = device->CreateTexture2D(&texture_desc, 0, &depth_texture);
	if (result != S_OK)
	{
		LogError("Failed When Creating Depth Texture !");
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
	ZeroMemory(&depth_stencil_view_desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	//depth_stencil_view_desc.Format = texture_desc.Format;
	depth_stencil_view_desc.Format = DXGI_FORMAT_D32_FLOAT;
	depth_stencil_view_desc.Flags = 0;
	depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depth_stencil_view_desc.Texture2D.MipSlice = 0;
	
	result = device->CreateDepthStencilView(depth_texture, &depth_stencil_view_desc, &m_DepthStencilView);
	
	if (result != S_OK)
	{
		LogError("Failed When Creating Depth Stencil View !");
	}


	D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
	srv_desc.Format = DXGI_FORMAT_R32_FLOAT;
	srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srv_desc.Texture2D.MipLevels = texture_desc.MipLevels;
	srv_desc.Texture2D.MostDetailedMip = 0;

	result = device->CreateShaderResourceView(depth_texture, &srv_desc, &m_SRV);
	if (result != S_OK)
	{
		LogError("Failed When Creating Shadow SRV");
	}


	depth_texture->Release();
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