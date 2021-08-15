
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
	delete m_RasterizerState;
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
		LogError("Failed When Creating Swapchain !");
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
	else 
	{
		LogError("Failed When Creating RenderTargetView !");
	}
}

void Renderer::InitRasterzierState()
{
	m_RasterizerState = new RasterzierState();
}



RasterzierState* Renderer::SetRasterzierState(RasterzierStateType type)
{
	return m_RasterizerState->SetState(type);
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
	m_RasterizerState->Bind();

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
