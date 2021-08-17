#include "DepthStencilState.h"
#include "Display.h"
#include "Renderer.h"
#include "Log.h"

DepthStencilState::DepthStencilState()
{
	InitDepthStencilState();
	InitDepthStencilView();
}

DepthStencilState::~DepthStencilState()
{
	m_DepthStencilState->Release();
	m_DepthStencilView->Release();
}

void DepthStencilState::Clear()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
}

void DepthStencilState::Bind()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->OMSetDepthStencilState(m_DepthStencilState, 0);
}

void DepthStencilState::InitDepthStencilView()
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

void DepthStencilState::InitDepthStencilState()
{
	ID3D11Device* device = Renderer::Get()->GetDevice();

	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
	depth_stencil_desc.DepthEnable = true;
	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_GREATER;
	depth_stencil_desc.StencilEnable = true;
	depth_stencil_desc.StencilReadMask = 0xFF;
	depth_stencil_desc.StencilWriteMask = 0xFF;
	// Stencil operations if pixel is front-facing.
	depth_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depth_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depth_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depth_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	HRESULT result = device->CreateDepthStencilState(&depth_stencil_desc, &m_DepthStencilState);
	if (result != S_OK)
	{
		LogError("Failed When Creating DepthStencilState !");
	}
}
