#pragma once

#include <d3d11.h>

class IndexBuffer
{
public:
	IndexBuffer(UINT* indices, int count, ID3D11Device* device, ID3D11DeviceContext* context);
	~IndexBuffer();

	inline ID3D11Buffer* GetBuffer() const { return m_Buffer; }
	inline int GetCount() const { return m_Count; }

	void Bind();

private:
	int m_Count;
	ID3D11Buffer* m_Buffer;
	ID3D11Device* device;
	ID3D11DeviceContext* context;
};