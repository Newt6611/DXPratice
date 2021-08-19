#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <memory>
#include <unordered_map>
#include "Display.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "RasterzierState.h"
#include "Log.h"
#include "Texture.h"
#include "Camera.h"
#include "ConstantBuffer.h"
#include "SamplerState.h"
#include "RenderTargetView.h"
#include "BlendState.h"
#include "DepthStencilState.h"
#include "Model.h"

class Renderer 
{
public:
	static Renderer* Get() { 
		if (m_Instance == nullptr)
			m_Instance = new Renderer();
		return m_Instance;
	}

	Renderer(const Renderer &r) = delete;
	void operator=(Renderer &r) = delete;

	void Init();

	~Renderer();

	inline ID3D11Device* GetDevice() const { return m_Device; }
	inline ID3D11DeviceContext* GetContext() const { return m_Context; }
	inline IDXGISwapChain* GetSwapChain() const { return m_Swapchain; }
	
	inline RenderTargetView* GetRenderTargetView() const { return m_RenderTargetView; }
	inline DepthStencilState* GetDepthStencilState() const { return m_DepthStencilState; }
	inline RasterzierState* GetRasterizerState() const { return m_RasterizerState; }
	inline SamplerState* GetSamplerState() const { return m_SamplerState; }
	inline BlendState* GetBlendState() const { return m_BlendState; }

	inline Camera* GetCamera() const { return m_Camera; }

	RasterzierState* SetRasterzierState(RasterzierStateType type);

	std::shared_ptr<VertexBuffer> CreateVertexBuffer(VertexData* data, int count);
	std::shared_ptr<IndexBuffer> CreateIndexBuffer(UINT* indices, int count);
	
	std::shared_ptr<Shader> CreateShader(LPCWSTR vertexFilePath, LPCWSTR pixelFilePath);
	
	std::shared_ptr<Model> CreateModel(std::string filePath);

	std::shared_ptr<Texture> CreateTexture(std::string filePath);
	std::shared_ptr<Texture> CreateTexture(std::string filePath, TextureType type);

	void BeginFrame();
	void EndFrame();


private:
	Renderer() { }

	void InitD3D11();
	void InitRenderTargetView();
	void InitDepthStencilState();
	void InitRasterzierState();
	void InitSamplerState();
	void InitBlendState();

	void InitCamera();

private:
	static Renderer* m_Instance;
	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_Context;
	IDXGISwapChain* m_Swapchain;

	RenderTargetView* m_RenderTargetView;
	DepthStencilState* m_DepthStencilState;
	RasterzierState* m_RasterizerState;
	SamplerState* m_SamplerState;
	BlendState* m_BlendState;

	Camera* m_Camera;

	std::unordered_map<std::string, std::shared_ptr<Model>> m_LoadedModelCache;
};