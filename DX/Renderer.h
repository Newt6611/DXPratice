#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <memory>
#include "Display.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

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
	inline ID3D11RasterizerState* GetRasterizerState() const { return m_RasterizerState; }
	inline ID3D11RenderTargetView* GetRenderTargetView() const { return m_RenderTargetView; }


	void DrawIndexed(int count);
	void Draw(int vertexCount);


	std::shared_ptr<VertexBuffer> CreateVertexBuffer(VertexData* data, int count);
	std::shared_ptr<IndexBuffer> CreateIndexBuffer(UINT* indices, int count);
	std::shared_ptr<Shader> CreateShader(LPCWSTR vertexFilePath, LPCWSTR pixelFilePath);

	void BeginFrame();
	void EndFrame();


private:
	Renderer() { }

	void InitD3D11(Display* display);
	void InitRenderTargetView();
	void InitRasterzierState();

private:
	static Renderer* m_Instance;
	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_Context;
	IDXGISwapChain* m_Swapchain;
	ID3D11RenderTargetView* m_RenderTargetView;
	ID3D11RasterizerState* m_RasterizerState;
	
};