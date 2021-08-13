#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

struct VertexData {
	XMFLOAT3 pos;
	XMFLOAT4 color;
};

class VertexBuffer 
{
public:
	VertexBuffer(VertexData* data, int count);
	~VertexBuffer();

	inline ID3D11Buffer* GetBuffer() const { return m_VertexBuffer; }
	inline int GetCount() const { return m_Count; }

	void Bind();
	
private:
	int m_Count;
	ID3D11Buffer* m_VertexBuffer;
};