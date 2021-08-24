
#include "Renderer.h"
#include "World.h"
#include "DirectionalLight.h"

Renderer* Renderer::m_Instance;

void Renderer::Init(World* world)
{
	world = world;
	InitD3D11();
	InitDepthStencilState();
	InitRenderTargetView();
	InitRasterzierState();
	InitSamplerState();
	InitBlendState();

	InitCamera();
}

Renderer::~Renderer()
{
	m_Device->Release();
	m_Context->Release();
	m_Swapchain->Release();
	delete m_RenderTargetView;
	delete m_DepthStencilState;
	delete m_RasterizerState;
	delete m_Camera;
	delete m_SamplerState;
	delete m_BlendState;
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

void Renderer::InitDepthStencilState()
{
	m_DepthStencilState = new DepthStencilState();
}

void Renderer::InitRasterzierState()
{
	m_RasterizerState = new RasterzierState();
}

void Renderer::InitSamplerState()
{
	m_SamplerState = new SamplerState();
}

void Renderer::InitBlendState()
{
	m_BlendState = new BlendState();
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



Ref<VertexBuffer> Renderer::CreateVertexBuffer(VertexData* data, int size)
{
	Ref<VertexBuffer> vertexBuffer = std::make_shared<VertexBuffer>(data, size, m_Device, m_Context);
	return vertexBuffer;
}

Ref<IndexBuffer> Renderer::CreateIndexBuffer(UINT* indices, int count)
{
	Ref<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>(indices, count, m_Device, m_Context);
	return indexBuffer;
}

Ref<Shader> Renderer::CreateShader(LPCWSTR vertexFilePath, LPCWSTR pixelFilePath, int type)
{
	Ref<Shader> shader = std::make_shared<Shader>(vertexFilePath, pixelFilePath, type);
	return shader;
}

Ref<Model> Renderer::CreateModel(std::string filePath)
{
	if (m_LoadedModelCache.find(filePath) != m_LoadedModelCache.end())
		return m_LoadedModelCache[filePath];

	Ref<Model> model = std::make_shared<Model>(filePath);
	m_LoadedModelCache[filePath] = model;
	return model;
}

Ref<Texture> Renderer::CreateTexture(std::string filePath)
{
	if (m_LoadedTextureCache.find(filePath) != m_LoadedTextureCache.end())
		return m_LoadedTextureCache[filePath];

	Ref<Texture> texture = std::make_shared<Texture>(filePath);
	m_LoadedTextureCache[filePath] = texture;
	return texture;
}

Ref<Texture> Renderer::CreateTexture(std::string filePath, TextureType type)
{
	Ref<Texture> texture = std::make_shared<Texture>(filePath, type);
	return texture;
}

Ref<DirectionalLight> Renderer::CreateDirectionalLight()
{
	Ref<DirectionalLight> light = std::make_shared<DirectionalLight>(world, m_Device, m_Context);
	return light;
}

Ref<DirectionalLight> Renderer::CreateDirectionalLight(XMFLOAT3 direction, XMFLOAT3 color)
{
	Ref<DirectionalLight> light = std::make_shared<DirectionalLight>(world, color, direction, m_Device, m_Context);
	return light;
}




void Renderer::Update()
{
	
	if (wire_frame && m_RasterizerState->GetType() == RasterzierStateType::Solid)
		m_RasterizerState->SetState(RasterzierStateType::WireFrame);
	else if (!wire_frame && m_RasterizerState->GetType() == RasterzierStateType::WireFrame)
		m_RasterizerState->SetState(RasterzierStateType::Solid);


	if (transparency && m_BlendState->GetType() == BlendStateType::None)
		m_BlendState->SetBlendState(BlendStateType::Transparency);
	else if (!transparency && m_BlendState->GetType() == BlendStateType::Transparency)
		m_BlendState->SetBlendState(BlendStateType::None);
}

void Renderer::BeginFrame()
{
	m_RenderTargetView->Clear();
	m_DepthStencilState->Clear();

	m_DepthStencilState->Bind();
	m_RenderTargetView->Bind();

	m_RasterizerState->Bind();
	
	m_BlendState->Bind();
	m_SamplerState->Bind();

	auto viewport = CD3D11_VIEWPORT(0.f, 0.f, static_cast<float>(Display::Get()->GetWidth()), static_cast<float>(Display::Get()->GetHeight()));
	m_Context->RSSetViewports(1, &viewport);
}

void Renderer::EndFrame()
{
	m_Swapchain->Present(1, 0);
}
