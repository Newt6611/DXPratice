#pragma once

#include <d3d11.h>
#include "Log.h"

class Editor;

class RenderTargetView 
{
public:
	RenderTargetView();
	~RenderTargetView();

	inline ID3D11RenderTargetView* GetRenderTargetView() const { return m_RenderTargetView; }

	void SetClearColor(float color[4]);

	void Bind();
	void Clear();

private:
	void InitTextureSRV();

private:
	ID3D11RenderTargetView* m_RenderTargetView;
	ID3D11RenderTargetView* m_SecondRTV;
	ID3D11ShaderResourceView* m_TextureSRV;
	ID3D11Texture2D* m_Texture;

	float m_ClearColor[4] = { 0.5f, 0.2f, 0.2f, 1.f };

	friend class Editor;
};