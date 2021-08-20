#pragma once

#include "Base.h"
#include "ConstantBuffer.h"


class DirectionalLight
{
public:
	DirectionalLight(ID3D11Device* device, ID3D11DeviceContext* context);
	DirectionalLight(XMFLOAT4 color, XMFLOAT3 direction, ID3D11Device* device, ID3D11DeviceContext* context);

	void Bind(unsigned int slot);
	void SetDirection(XMFLOAT3 d);

private:
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	Ref<ConstantBuffer<Directional_Light>> m_ConstantBuffer;
	XMFLOAT4 m_Color;
	XMFLOAT3 m_Ambient;
	XMFLOAT3 m_Diffuse;
	XMFLOAT3 m_Specular;
	XMFLOAT3 m_Direction;
};
