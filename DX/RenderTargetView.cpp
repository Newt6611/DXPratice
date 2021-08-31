#include "RenderTargetView.h"
#include "Renderer.h"


RenderTargetView::RenderTargetView()
{
	
	IDXGISwapChain* swap_chain = Renderer::Get()->GetSwapChain();
	ID3D11Device* device = Renderer::Get()->GetDevice();
	
	ID3D11Texture2D* backbuffer;
	D3D11_TEXTURE2D_DESC backbuffer_desc;
	
	HRESULT result = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbuffer);
	backbuffer->GetDesc(&backbuffer_desc);
	
	
	if (result == S_OK)
	{
		device->CreateRenderTargetView(backbuffer, NULL, &m_RenderTargetView);
	}
	else
	{
		LogError("Failed When Creating RenderTargetView !");
	}
	
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	ZeroMemory(&shaderResourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	shaderResourceViewDesc.Format = backbuffer_desc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;
	
	
	InitEditorTextureSRV();
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
	ID3D11DepthStencilView* depthStencilView = Renderer::Get()->GetDepthStencilState()->GetDepthStencilView();
	context->OMSetRenderTargets(1, &m_RenderTargetView, depthStencilView);
}

void RenderTargetView::Clear()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->ClearRenderTargetView(m_RenderTargetView, m_ClearColor);
}

void RenderTargetView::BindEditor()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	ID3D11DepthStencilView* depthStencilView = Renderer::Get()->GetDepthStencilState()->GetDepthStencilView();
	context->OMSetRenderTargets(1, &m_EditorRenderTargetView, depthStencilView);
}

void RenderTargetView::ClearEditor()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->ClearRenderTargetView(m_EditorRenderTargetView, m_ClearColor);
}

void RenderTargetView::InitEditorTextureSRV()
{
	ID3D11Device* device = Renderer::Get()->GetDevice();

	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT result;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

	ZeroMemory(&textureDesc, sizeof(textureDesc));

	textureDesc.Width = 800;
	textureDesc.Height = 600;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	result = device->CreateTexture2D(&textureDesc, NULL, &m_Texture);
	if (result != S_OK)
		LogError("Faied When Creating RTV texture !");

	// Setup the description of the render target view.
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	// Create the render target view.
	result = device->CreateRenderTargetView(m_Texture, &renderTargetViewDesc, &m_EditorRenderTargetView);
	if (result != S_OK)
		LogError("Failed When Creating RenderTargetView !");

	// Setup the description of the shader resource view.
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	// Create the shader resource view.
	result = device->CreateShaderResourceView(m_Texture, &shaderResourceViewDesc, &m_TextureSRV);
	if (result != S_OK)
		LogError("Faied When Creating RTV SRV !");
}
