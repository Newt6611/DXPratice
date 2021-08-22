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
	ID3D11RenderTargetView* m_RenderTargetView;

	float m_ClearColor[4] = { 0.5f, 0.2f, 0.2f, 1.f };

	friend class Editor;
};