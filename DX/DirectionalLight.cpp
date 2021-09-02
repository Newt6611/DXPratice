#include "DirectionalLight.h"
#include "Renderer.h"
#include "World.h"

DirectionalLight::DirectionalLight(World* world, ID3D11Device* device, ID3D11DeviceContext* context)
	: device(device), context(context)
{
	world->PushGameObjetToWorld(this);
	m_Color = XMFLOAT3(1, 1, 1);
	m_Rotation = XMFLOAT3(-1, -0.9, 1);
}

DirectionalLight::DirectionalLight(World* world, XMFLOAT3 color, XMFLOAT3 direction, ID3D11Device* device, ID3D11DeviceContext* context)
{
	world->PushGameObjetToWorld(this);
	m_Color = color;
	m_Rotation = direction;
}

void DirectionalLight::SetDirection(XMFLOAT3 r)
{
	m_Rotation = r;
}

void DirectionalLight::SetAmbient(XMFLOAT3 color)
{
	this->m_Ambient = color;
}

void DirectionalLight::SetDiffuse(XMFLOAT3 color)
{
	this->m_Diffuse = color;
}

void DirectionalLight::SetSpecular(XMFLOAT3 color)
{
	this->m_Specular = color;
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
	XMVector3Normalize(XMLoadFloat3(&m_Rotation));
	m_LightData.Direction = XMFLOAT3(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_LightData.Color = XMFLOAT4(m_Color.x, m_Color.y, m_Color.z, 1);
	m_LightData.Ambient = m_Ambient;
	m_LightData.Diffuse = m_Diffuse;
	m_LightData.Specular = m_Specular;

	IGameObject::Update();
}

void DirectionalLight::Render(Camera* camera)
{
}
