#pragma once
#include <d3d11.h>

class Editor;

class DepthStencilState
{
public:
	DepthStencilState();
	~DepthStencilState();

	inline ID3D11DepthStencilState* GetCurrentState() { return m_DepthStencilState; }
	inline ID3D11DepthStencilView* GetDepthStencilView() { return m_DepthStencilView; }

	void Clear();
	void Bind();

	void BindShadow();
	void ClearShadow();

private:
	void InitDepthStencilState();
	void InitDepthStencilView(float width, float height); // Editor Call For Resize
	void InitShadow();

private:
	ID3D11DepthStencilView* m_DepthStencilView;
	ID3D11DepthStencilState* m_DepthStencilState;

	ID3D11DepthStencilView* m_ShadowView;
	ID3D11ShaderResourceView* m_ShadowSRV;

	float m_Width;
	float m_Height;
	friend class Editor;
};