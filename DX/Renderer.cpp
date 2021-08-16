
#include "Renderer.h"

Renderer* Renderer::m_Instance;

void Renderer::Init()
{
	InitD3D11();
	InitRenderTargetView();
	InitRasterzierState();
	InitSamplerState();

	InitCamera();
}

Renderer::~Renderer()
{
	m_Device->Release();
	m_Context->Release();
	m_Swapchain->Release();
	delete m_RenderTargetView;
	delete m_RasterizerState;
	delete m_Camera;
	delete m_SamplerState;
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
	m_RenderTargetView = new RenderTargetView();
}

void Renderer::InitRasterzierState()
{
	m_RasterizerState = new RasterzierState();
}

void Renderer::InitSamplerState()
{
	m_SamplerState = new SamplerState();
}

void Renderer::InitCamera()
{
	Display* display = Display::Get();
	m_Camera = new Camera(display->GetWidth(), display->GetHeight(), 0.1f, 100.f);
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

std::shared_ptr<Texture> Renderer::CreateTexture(std::wstring filePath)
{
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(filePath);
	return texture;
}





void Renderer::BeginFrame()
{
	m_RenderTargetView->Clear();

	m_RenderTargetView->Bind();
	m_RasterizerState->Bind();
	m_SamplerState->Bind();

	auto viewport = CD3D11_VIEWPORT(0.f, 0.f, static_cast<float>(Display::Get()->GetWidth()), static_cast<float>(Display::Get()->GetHeight()));
	m_Context->RSSetViewports(1, &viewport);
}

void Renderer::EndFrame()
{
	m_Swapchain->Present(0, 0);
}
