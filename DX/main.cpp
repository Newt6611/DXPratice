#include <iostream>
#include <cstdlib>
#include "Display.h"
#include "Renderer.h"
#include "Log.h"
#include "Command.h"

static Display* display = nullptr;
static Renderer* renderer = nullptr;

int main()
{
	AllocConsole();
	Log::Init();

	LogInfo("Engine Start");

	display = Display::Get();
	renderer = Renderer::Get();


	display->Init(800, 600);
	renderer->Init();


	//     TEST  Draw Square  /////////////////////////////////
	std::shared_ptr<Texture> texture = renderer->CreateTexture(L"Textures/wall.jpg");
	
	ConstantBuffer* constant_buffer = new ConstantBuffer();

	VertexData vertex[] = {
		{ XMFLOAT3(-0.5f, -0.5f, 0.f), XMFLOAT4(1, 0, 0, 1), XMFLOAT2(0, 0) },
		{ XMFLOAT3(-0.5f,  0.5f, 0.f), XMFLOAT4(0, 1, 0, 1), XMFLOAT2(1, 0) },
		{ XMFLOAT3(0.5f,   0.5f, 0.f), XMFLOAT4(0, 0, 1, 1), XMFLOAT2(1, 1) },
		{ XMFLOAT3(0.5f,  -0.5f, 0.f), XMFLOAT4(1, 1, 1, 1), XMFLOAT2(1, 0) }
	};

	//VertexData vertex[] = {
	//	{ XMFLOAT3(-100.f, -100.f, 0.f), XMFLOAT4(1, 0, 0, 1) },
	//	{ XMFLOAT3(-100.f,  100.f, 0.f), XMFLOAT4(0, 1, 0, 1) },
	//	{ XMFLOAT3( 100.f,  100.f, 0.f), XMFLOAT4(0, 0, 1, 1) },
	//	{ XMFLOAT3( 100.f, -100.f, 0.f), XMFLOAT4(1, 1, 1, 1) }
	//};

	UINT indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	std::shared_ptr<VertexBuffer> vertexbuffer = renderer->CreateVertexBuffer(vertex, 4);
	std::shared_ptr<IndexBuffer> indexbuffer = renderer->CreateIndexBuffer(indices, 6);

	std::shared_ptr<Shader> shader = renderer->CreateShader(L"Shaders/Vertex.hlsl", L"Shaders/Pixel.hlsl");

	float r = 0;
	XMMATRIX world = XMMatrixIdentity();
	/////////////////////////////////////////

	MSG msg = { };
	while (true)
	{
		if (PeekMessage(&msg, display->GetHandle(), 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT) break;
		}

		renderer->BeginFrame();

		r += 0.0001;
		if (r > 360)
			r = 0;
		world = XMMatrixRotationY(r);


		shader->Bind();
		constant_buffer->GetPerObj()->Projection = XMMatrixTranspose( Renderer::Get()->GetCamera()->GetProjection() );
		constant_buffer->GetPerObj()->View = XMMatrixTranspose( Renderer::Get()->GetCamera()->GetView() );
		constant_buffer->GetPerObj()->World = XMMatrixTranspose( world );
		
		texture->Bind(0);

		constant_buffer->BindPerObj();
		vertexbuffer->Bind();
		indexbuffer->Bind();
		
		Command::DrawIndexed(indexbuffer->GetCount());


		renderer->EndFrame();
	}


	delete display;
	delete renderer;
}