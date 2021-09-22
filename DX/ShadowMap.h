#pragma once

#include <d3d11.h>

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();

	void Clear();
	void Bind();
	void BindDetphSRV();

private:
	void Init();


private:
	float m_Widht;
	float m_Height;

	ID3D11DepthStencilView* m_ShadowView;
	ID3D11ShaderResourceView* m_ShadowSRV;
};
