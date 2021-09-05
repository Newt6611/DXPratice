#include "Sponza.h"
#include "../World.h"

Sponza::Sponza(World* world)
{
	world->PushGameObjetToWorld(this);
	m_Name = "Sponza";
	enable = true;
}

Sponza::~Sponza()
{
}

void Sponza::Init()
{
	m_Shader = Renderer::Get()->CreateShader("Phong", L"Shaders/Vertex.hlsl", L"Shaders/Pixel.hlsl", 1);
	//m_Model = Renderer::Get()->CreateModel("Models/sponza/sponza.obj");
	m_Model = Renderer::Get()->CreateModel("Models/plane/plane.obj");

	m_ConstantBuffer = Renderer::Get()->CreateConstantBuffer<VS_Object>(ShaderStage::VS);

	m_World = XMMatrixIdentity();

	m_Position = XMFLOAT3(0, -4, 15);
	m_Rotation = XMFLOAT3(0, 90, 0);
	m_Scale = XMFLOAT3(1, 1, 1);
	//m_Position = XMFLOAT3(0, -7, 0);
	//m_Scale = XMFLOAT3(0.1, 0.1, 0.1);
}

void Sponza::Update()
{
	if (!enable)
		return;

	IGameObject::Update();
}

void Sponza::Render(Camera* camera)
{
	if (!enable)
		return;
	m_Shader->Bind();

	m_ConstantBuffer->GetData().World = m_World;
	m_ConstantBuffer->GetData().View = camera->GetView();
	m_ConstantBuffer->GetData().Projection = camera->GetProjection();
	m_ConstantBuffer->GetData().color = XMFLOAT4(m_Color.x, m_Color.y, m_Color.z, alpha);
	m_ConstantBuffer->Bind(0);

	m_Model->Draw();
}
