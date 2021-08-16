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
	std::shared_ptr<Texture> texture2 = renderer->CreateTexture(L"Textures/t.jpg");

	ConstantBuffer* constant_buffer = new ConstantBuffer();

	VertexData vertex[] = {
		{ XMFLOAT3(-0.5f, -0.5f, 0.f), XMFLOAT4(1, 0, 0, 1), XMFLOAT2(0, 0) },
		{ XMFLOAT3(-0.5f,  0.5f, 0.f), XMFLOAT4(0, 1, 0, 1), XMFLOAT2(1, 0) },
		{ XMFLOAT3(0.5f,   0.5f, 0.f), XMFLOAT4(0, 0, 1, 1), XMFLOAT2(1, 1) },
		{ XMFLOAT3(0.5f,  -0.5f, 0.f), XMFLOAT4(1, 1, 1, 1), XMFLOAT2(1, 0) }
	};


	UINT indices[] = {
		0, 3, 2,
		2, 1, 0
	};

	std::shared_ptr<VertexBuffer> vertexbuffer = renderer->CreateVertexBuffer(vertex, 4);
	std::shared_ptr<IndexBuffer> indexbuffer = renderer->CreateIndexBuffer(indices, 6);

	std::shared_ptr<Shader> shader = renderer->CreateShader(L"Shaders/Vertex.hlsl", L"Shaders/Pixel.hlsl");

	XMMATRIX obj_one = XMMatrixIdentity();
	XMMATRIX obj_two = XMMatrixIdentity();
	obj_one = XMMatrixTranslation( 0.3, 0, 1);
	obj_two = XMMatrixTranslation(-0.3, 0, 0);
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

		// texture one
		shader->Bind();
		constant_buffer->GetPerObj()->Projection = XMMatrixTranspose( Renderer::Get()->GetCamera()->GetProjection() );
		constant_buffer->GetPerObj()->View = XMMatrixTranspose( Renderer::Get()->GetCamera()->GetView() );
		constant_buffer->GetPerObj()->World = XMMatrixTranspose(obj_one );
		texture->Bind(0);
		constant_buffer->BindPerObj();
		vertexbuffer->Bind();
		indexbuffer->Bind();
		Command::DrawIndexed(indexbuffer->GetCount());


		// texture two
		shader->Bind();
		constant_buffer->GetPerObj()->Projection = XMMatrixTranspose(Renderer::Get()->GetCamera()->GetProjection());
		constant_buffer->GetPerObj()->View = XMMatrixTranspose(Renderer::Get()->GetCamera()->GetView());
		constant_buffer->GetPerObj()->World = XMMatrixTranspose(obj_two);
		texture2->Bind(0);
		constant_buffer->BindPerObj();
		vertexbuffer->Bind();
		indexbuffer->Bind();
		Command::DrawIndexed(indexbuffer->GetCount());


		renderer->EndFrame();
	}


	delete display;
	delete renderer;
}