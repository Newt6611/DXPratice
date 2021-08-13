
#include "Renderer.h"

Renderer* Renderer::m_Instance;

void Renderer::Init()
{
	InitD3D11();
	InitRenderTargetView();
	InitRasterzierState();
}

Renderer::~Renderer()
{
	m_Device->Release();
	m_Context->Release();
	m_Swapchain->Release();
	m_RenderTargetView->Release();
	m_RasterizerState->Release();
}

void Renderer::InitD3D11()
{
	Display* display = Display::Get();
	DXGI_SWAP_CHAIN_DESC swapchain_desc;
	ZeroMemory(&swapchain_desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapchain_desc.BufferDesc.Width = 0;
	swapchain_desc.BufferDesc.Height = 0;
	swapchain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchain_desc.SampleDesc.Count = 1;
	swapchain_desc.SampleDesc.Quality = 0;
	swapchain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchain_desc.BufferCount = 1;
	swapchain_desc.OutputWindow = display->GetHandle();
	swapchain_desc.Windowed = true;

	HRESULT result = D3D11CreateDeviceAndSwapChain(
		NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL,
		NULL, NULL, D3D11_SDK_VERSION, &swapchain_desc,
		&m_Swapchain, &m_Device, NULL, &m_Context
	);

	if (result != S_OK)
	{
		MessageBox(display->GetHandle(), L"failed creating swapchain", L"Error", ERROR);
	}
}

void Renderer::InitRenderTargetView()
{
	ID3D11Texture2D* backbuffer;
	HRESULT result = m_Swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbuffer);
	if (result == S_OK)
	{
		m_Device->CreateRenderTargetView(backbuffer, NULL, &m_RenderTargetView);
	}
}

void Renderer::InitRasterzierState()
{
	D3D11_RASTERIZER_DESC rasterizer_desc;
	ZeroMemory(&rasterizer_desc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizer_desc.FillMode = D3D11_FILL_SOLID;
	rasterizer_desc.CullMode = D3D11_CULL_NONE;
	rasterizer_desc.FrontCounterClockwise = false;
	rasterizer_desc.DepthClipEnable = true;
	m_Device->CreateRasterizerState(&rasterizer_desc, &m_RasterizerState);
}



void Renderer::DrawIndexed(int count)
{
	m_Context->DrawIndexed(count, 0, 0);
}

void Renderer::Draw(int vertexCount)
{
	m_Context->Draw(vertexCount, 0);
}





std::shared_ptr<VertexBuffer> Renderer::CreateVertexBuffer(VertexData* data, int size)
{
	std::shared_ptr<VertexBuffer> vertexBuffer = std::make_shared<VertexBuffer>(data, size);
	return vertexBuffer;
}

std::shared_ptr<IndexBuffer> Renderer::CreateIndexBuffer(UINT* indices, int count)
{
	std::shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>(indices, count);
	return indexBuffer;
}

std::shared_ptr<Shader> Renderer::CreateShader(LPCWSTR vertexFilePath, LPCWSTR pixelFilePath)
{
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexFilePath, pixelFilePath);
	return shader;
}





void Renderer::BeginFrame()
{
	float color[] = { 0.1, 0.2, 0.3, 1 };
	m_Context->ClearRenderTargetView(m_RenderTargetView, color);
	m_Context->RSSetState(m_RasterizerState);

	D3D11_VIEWPORT view_port[1];
	view_port[0].Width = Display::Get()->GetWidth();
	view_port[0].Height = Display::Get()->GetHeight();
	view_port[0].MinDepth = 0;
	view_port[0].MaxDepth = 1;
	view_port[0].TopLeftX = 0;
	view_port[0].TopLeftY = 0;
	m_Context->RSSetViewports(1, view_port);


	m_Context->OMSetRenderTargets(1, &m_RenderTargetView, NULL);
}

void Renderer::EndFrame()
{
	m_Swapchain->Present(0, 0);
}
