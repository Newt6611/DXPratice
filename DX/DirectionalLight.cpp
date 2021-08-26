#include "DirectionalLight.h"
#include "Renderer.h"
#include "World.h"

DirectionalLight::DirectionalLight(World* world, ID3D11Device* device, ID3D11DeviceContext* context)
	: device(device), context(context)
{
	world->PushGameObjetToWorld(this);
	m_ConstantBuffer = Renderer::Get()->CreateConstantBuffer<Directional_Light>(ShaderStage::PS);
	m_Color = XMFLOAT3(1, 1, 1);
	m_Rotation = XMFLOAT3(0, -0.3, 1);
	Init();
}

DirectionalLight::DirectionalLight(World* world, XMFLOAT3 color, XMFLOAT3 direction, ID3D11Device* device, ID3D11DeviceContext* context)
{
	world->PushGameObjetToWorld(this);
	m_ConstantBuffer = Renderer::Get()->CreateConstantBuffer<Directional_Light>(ShaderStage::PS);
	m_Color = color;
	m_Rotation = direction;
	Init();
}

void DirectionalLight::SetDirection(XMFLOAT3 r)
{
	m_Rotation = r;
}

void DirectionalLight::Init()
{
	m_Name = "Directional Light";
	m_Position = XMFLOAT3(1, 1, 1);
	m_Scale = XMFLOAT3(1, 1, 1);
	m_Ambient = XMFLOAT3(1, 1, 1);
	m_Diffuse = XMFLOAT3(1, 1, 1);
	m_Specular = XMFLOAT3(1, 1, 1);
}

void DirectionalLight::Update()
{
	IGameObject::Update();
}

void DirectionalLight::Render(Camera* camera)
{
	XMVector3Normalize(XMLoadFloat3(&m_Rotation));
	m_ConstantBuffer->GetData().Direction = XMFLOAT3(-m_Rotation.x, -m_Rotation.y, -m_Rotation.z);
	m_ConstantBuffer->GetData().Color = XMFLOAT4(m_Color.x, m_Color.y, m_Color.z, 1);
	m_ConstantBuffer->GetData().Ambient = m_Ambient;
	m_ConstantBuffer->GetData().Specular = m_Specular;
	m_ConstantBuffer->GetData().Diffuse = m_Diffuse;
	m_ConstantBuffer->Bind(0);
}
