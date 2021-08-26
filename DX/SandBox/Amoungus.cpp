#include "Amoungus.h"
#include "../World.h"

Amoungus::Amoungus(World* world)
{
	world->PushGameObjetToWorld(this);
	m_Name = "Amoungus";
}

Amoungus::~Amoungus()
{
}

void Amoungus::Init()
{
	m_Shader = Renderer::Get()->CreateShader(L"Shaders/Vertex.hlsl", L"Shaders/Pixel.hlsl", 1);
	m_Model = Renderer::Get()->CreateModel("Models/Amoungus/amoungus.obj");

	m_ConstantBuffer = Renderer::Get()->CreateConstantBuffer<VS_Object>(ShaderStage::VS);

	m_World = XMMatrixIdentity();

	m_Position = XMFLOAT3(2, 0, 0);
	m_Rotation = XMFLOAT3(0, 0, 0);
	m_Scale = XMFLOAT3(1, 1, 1);
	r = 0;
}

void Amoungus::Update()
{
	r += 0.5;
	if (r > 360)
		r = 0;
	m_Rotation.y = r;

	IGameObject::Update();
}

void Amoungus::Render(Camera* camera)
{
	m_Shader->Bind();

	m_ConstantBuffer->GetData().World = m_World;
	m_ConstantBuffer->GetData().View = camera->GetView();
	m_ConstantBuffer->GetData().Projection = camera->GetProjection();
	m_ConstantBuffer->GetData().color = XMFLOAT4(m_Color.x, m_Color.y, m_Color.z, alpha);
	m_ConstantBuffer->Bind(0);

	m_Model->Draw();
}
