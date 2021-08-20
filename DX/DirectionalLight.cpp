#include "DirectionalLight.h"
#include "Renderer.h"

DirectionalLight::DirectionalLight(ID3D11Device* device, ID3D11DeviceContext* context)
	: device(device), context(context)
{
	m_ConstantBuffer = Renderer::Get()->CreateConstantBuffer<Directional_Light>(ShaderStage::PS);
	m_Color = XMFLOAT4(1, 1, 1, 1);
	m_Ambient = XMFLOAT3(1, 1, 1);
	m_Diffuse = XMFLOAT3(1, 1, 1);
	m_Specular = XMFLOAT3(1, 1, 1);
	m_Direction = XMFLOAT3(0, 0, -1);
}

DirectionalLight::DirectionalLight(XMFLOAT4 color, XMFLOAT3 direction, ID3D11Device* device, ID3D11DeviceContext* context)
{
	m_ConstantBuffer = Renderer::Get()->CreateConstantBuffer<Directional_Light>(ShaderStage::PS);
	m_Color = color;
	m_Ambient = XMFLOAT3(1, 1, 1);
	m_Diffuse = XMFLOAT3(1, 1, 1);
	m_Specular = XMFLOAT3(1, 1, 1);
	m_Direction = direction;
}

void DirectionalLight::Bind(unsigned int slot)
{
	m_ConstantBuffer->GetData().Direction = m_Direction;
	m_ConstantBuffer->GetData().Color = m_Color;
	m_ConstantBuffer->GetData().Ambient = m_Ambient;
	m_ConstantBuffer->GetData().Specular = m_Specular;
	m_ConstantBuffer->GetData().Diffuse = m_Diffuse;
	m_ConstantBuffer->Bind(slot);
}

void DirectionalLight::SetDirection(XMFLOAT3 r)
{
	m_Direction = r;
}