#include "NanoPlayer.h"
#include "../World.h"

NanoPlayer::NanoPlayer(World* world)
{
	world->PushGameObjetToWorld(this);
	m_Name = "NanoPlayer";
	enable = true;
}

NanoPlayer::~NanoPlayer()
{
}

void NanoPlayer::Init()
{
	m_Shader = Renderer::Get()->CreateShader("Normal", L"Shaders/NormalMappingVertex.hlsl", L"Shaders/NormalMappingPixel.hlsl", 2);
	m_Model = Renderer::Get()->CreateModel("Models/nanosuit/nanosuit.obj");
	
	m_ConstantBuffer = Renderer::Get()->CreateConstantBuffer<VS_Object>(ShaderStage::VS);

	m_World = XMMatrixIdentity();

	m_Position = XMFLOAT3(-2, -4, 0);
	m_Rotation = XMFLOAT3(0, 0, 0);
	m_Scale = XMFLOAT3(0.5, 0.5, 0.5);
	r = 0;
}

void NanoPlayer::Update()
{
	if (!enable)
		return;
	r += 25 * Timer::DeltaTime;
	if (r > 360)
		r = 0;
	m_Rotation.y = r;

	IGameObject::Update();
}

void NanoPlayer::Render(Camera* camera)
{
	if (!enable)
		return;
	if (!is_BindShadow)
		m_Shader->Bind();

	m_ConstantBuffer->GetData().World = m_World;
	m_ConstantBuffer->GetData().View = camera->GetView();
	m_ConstantBuffer->GetData().Projection = camera->GetProjection();
	m_ConstantBuffer->GetData().color = XMFLOAT4(m_Color.x, m_Color.y, m_Color.z, alpha);
	m_ConstantBuffer->Bind(0);
	
	m_Model->Draw();
}
