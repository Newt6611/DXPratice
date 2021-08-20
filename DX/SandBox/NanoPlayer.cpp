#include "NanoPlayer.h"
#include "../World.h"
#include "../ImGuiLayer.h"

NanoPlayer::NanoPlayer(World* world)
{
	world->PushGameObjetToWorld(this);
}

NanoPlayer::~NanoPlayer()
{
}

void NanoPlayer::Init()
{
	camera = Renderer::Get()->GetCamera();
	m_Shader = Renderer::Get()->CreateShader(L"Shaders/Vertex.hlsl", L"Shaders/Pixel.hlsl");
	m_Model = Renderer::Get()->CreateModel("Models/nanosuit/nanosuit.obj");
	
	m_ConstantBuffer = Renderer::Get()->CreateConstantBuffer<VS_Object>(ShaderStage::VS);

	m_World = XMMatrixIdentity();
	m_Position = XMFLOAT3(0, -8, 0);
	m_Rotation = XMFLOAT3(0, 0, 0);
	m_Scale = XMFLOAT3(0.5, 0.5, 0.5);
	r = 0;
}

void NanoPlayer::Update()
{
	r += 2;
	if (r > 360)
		r = 0;
	m_Rotation.y = r;

	IGameObject::Update();
}

void NanoPlayer::Render()
{
	m_Shader->Bind();

	m_ConstantBuffer->GetData().World = XMMatrixTranspose(m_World);
	m_ConstantBuffer->GetData().View = XMMatrixTranspose(camera->GetView());
	m_ConstantBuffer->GetData().Projection = XMMatrixTranspose(camera->GetProjection());
	m_ConstantBuffer->GetData().color = XMFLOAT3(1, 1, 1);
	m_ConstantBuffer->Bind(0);
	
	m_Model->Draw();
}
