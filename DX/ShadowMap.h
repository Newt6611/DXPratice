#pragma once

#include <d3d11.h>

class Editor;

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();

	void Clear();
	void Bind();
	void BindDetphSRV();

	void Init(float width, float height);
private:


private:
	float m_Width;
	float m_Height;

	ID3D11DepthStencilView* m_ShadowView;
	ID3D11ShaderResourceView* m_ShadowSRV;
	ID3D11Texture2D* m_Texture;

	friend class Editor;
};
