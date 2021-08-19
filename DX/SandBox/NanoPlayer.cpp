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
	m_ConstantBuffer = std::make_shared<ConstantBuffer<VS_Object>>(ShaderStage::VS);

	m_World = XMMatrixIdentity();
	m_Position = XMFLOAT3(0, -8, 0);
	m_Rotation = XMFLOAT3(0, 0, 0);
	m_Scale = XMFLOAT3(0.5, 0.5, 0.5);

	r = 0;
}

void NanoPlayer::Update()
{
	r += 0.05;
	if (r > 360)
		r = 0;
	m_Rotation.y = r;

	IGameObject::Update();
}

void NanoPlayer::Render()
{
	m_Shader->Bind();

	//VS_Object obj;
	//obj.World = XMMatrixTranspose( m_World );
	//obj.View = XMMatrixTranspose( camera->GetView() );
	//obj.Projection = XMMatrixTranspose( camera->GetProjection() );
	//
	//m_ConstantBuffer->SetData(obj);
	
	//m_ConstantBuffer->m_Data.World = XMMatrixTranspose(m_World);
	//m_ConstantBuffer->m_Data.View = XMMatrixTranspose(camera->GetView());
	//m_ConstantBuffer->m_Data.Projection = XMMatrixTranspose(camera->GetProjection());
	//m_ConstantBuffer->Bind(0);
	//
	//m_Model->Draw();
}
