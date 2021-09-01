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
	inline ID3D11RenderTargetView* GetEditorRenderTargetView() const { return m_EditorRenderTargetView; }

	void SetClearColor(float color[4]);


	void Bind();
	void Clear();

	void BindEditor();
	void ClearEditor();

private:
	void InitEditorTextureSRV(float width, float height); // Editor Call For Resize

private:
	ID3D11RenderTargetView* m_RenderTargetView;
	ID3D11RenderTargetView* m_EditorRenderTargetView;
	ID3D11ShaderResourceView* m_TextureSRV;
	ID3D11Texture2D* m_Texture;

	float m_ClearColor[4] = { 0.5f, 0.2f, 0.2f, 1.f };

	float m_ViewportWidth;
	float m_ViewportHeight;

	friend class Editor;
};