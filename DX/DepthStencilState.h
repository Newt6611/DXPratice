#pragma once
#include <d3d11.h>


class DepthStencilState
{
public:
	DepthStencilState();
	~DepthStencilState();

	inline ID3D11DepthStencilState* GetCurrentState() { return m_DepthStencilState; }
	inline ID3D11DepthStencilView* GetDepthStencilView() { return m_DepthStencilView; }

	void Clear();
	void Bind();

private:
	void InitDepthStencilView();
	void InitDepthStencilState();

private:
	ID3D11DepthStencilView* m_DepthStencilView;
	ID3D11DepthStencilState* m_DepthStencilState;
};