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

	inline ID3D11ShaderResourceView* GetDepthSRV() const { return m_ShadowSRV; }

	void BindDepthSRV();

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

	float m_ShadowWidth;
	float m_ShadowHeight;

	friend class Editor;
};