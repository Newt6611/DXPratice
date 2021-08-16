#pragma once

#include <d3d11.h>
#include "Log.h"

class RenderTargetView 
{
public:
	RenderTargetView();
	~RenderTargetView();

	inline ID3D11RenderTargetView* GetRenderTargetView() const { return m_RenderTargetView; }
	inline ID3D11DepthStencilView* GetDepthStencilView() const { return m_DepthStencilView; }

	void SetClearColor(float color[4]);

	void Bind();
	void Clear();

private:
	void InitDepthStencilView();

private:
	ID3D11RenderTargetView* m_RenderTargetView;
	ID3D11DepthStencilView* m_DepthStencilView;

	float m_ClearColor[4] = { 0.1f, 0.2f, 0.3f, 1.f };
};