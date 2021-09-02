#include "PointLight.h"
#include "World.h"
#include "Renderer.h"

PointLight::PointLight(World* world, ID3D11Device* device, ID3D11DeviceContext* context)
{
	world->PushGameObjetToWorld(this);
	this->device = device;
	this->context = context;
}

PointLight::~PointLight()
{

}

void PointLight::Init()
{
	m_Name = "PointLight";
	m_Position = XMFLOAT3(0, 0, 0);
	m_Rotation = XMFLOAT3(0, 0, 0);
	m_Scale = XMFLOAT3(1, 1, 1);
	m_Color = XMFLOAT3(1, 1, 1);
	m_Ambient = XMFLOAT3(1, 1, 1);
	m_Diffuse = XMFLOAT3(1, 1, 1);
	m_Specular = XMFLOAT3(1, 1, 1);
	m_Constant = 1;
	m_Linear = 0.14;
	m_Quadratic = 0.07;
}

void PointLight::Update()
{
	m_LightData.Position = m_Position;
	m_LightData.Ambient = m_Ambient;
	m_LightData.Diffuse = m_Diffuse;
	m_LightData.Specular = m_Specular;
	m_LightData.Color = XMFLOAT4(m_Color.x, m_Color.y, m_Color.z, 1);
	m_LightData.Constant = m_Constant;
	m_LightData.Linear = m_Linear;
	m_LightData.Quadratic = m_Quadratic;


	IGameObject::Update();
}

void PointLight::Render(Camera* camera)
{
}
