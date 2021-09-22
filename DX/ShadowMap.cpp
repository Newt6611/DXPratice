#include "ShadowMap.h"
#include "Log.h"
#include "Renderer.h"


ShadowMap::ShadowMap()
{
	Init();
}

ShadowMap::~ShadowMap()
{
	m_ShadowSRV->Release();
	m_ShadowView->Release();
}

void ShadowMap::Clear()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->ClearDepthStencilView(m_ShadowView, D3D11_CLEAR_DEPTH, 1, 0);
}

void ShadowMap::Bind()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	if(m_ShadowView != nullptr)
		context->OMSetRenderTargets(1, NULL, m_ShadowView);
}

void ShadowMap::BindDetphSRV() // For Test
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->PSSetShaderResources(3, 1, &m_ShadowSRV);
}

void ShadowMap::Init()
{
	ID3D11Device* device = Renderer::Get()->GetDevice();

	m_Widht = 1024;
	m_Height = 1024;
	D3D11_TEXTURE2D_DESC texture_desc = {};
	ZeroMemory(&texture_desc, sizeof(D3D11_TEXTURE2D_DESC));
	texture_desc.Width = m_Widht;
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