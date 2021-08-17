#include <iostream>
#include <cstdlib>
#include "Display.h"
#include "Renderer.h"
#include "Log.h"
#include "Command.h"
#include "ImGuiLayer.h"

static Display* display = nullptr;
static Renderer* renderer = nullptr;

int main()
{
	AllocConsole();
	Log::Init();

	LogInfo("Engine Start");

	display = Display::Get();
	renderer = Renderer::Get();

	HRESULT result = CoInitialize(NULL);
	if (result != S_OK)
		LogError("Erro CoInit !");

	display->Init(1280, 760);
	renderer->Init();

	ImGuiLayer* imgui_Layer = new ImGuiLayer();


	//     TEST  Draw Square  /////////////////////////////////
	std::shared_ptr<Texture> texture = renderer->CreateTexture(L"Textures/wall.jpg");
	std::shared_ptr<Texture> texture2 = renderer->CreateTexture(L"Textures/window.png");

	ConstantBuffer* constant_buffer = new ConstantBuffer();

	VertexData vertex[] = {
		{ XMFLOAT3(-0.5f, -0.5f, 0.f), XMFLOAT4(1, 0, 0, 1), XMFLOAT2(0, 0) },
		{ XMFLOAT3(-0.5f,  0.5f, 0.f), XMFLOAT4(0, 1, 0, 1), XMFLOAT2(1, 0) },
		{ XMFLOAT3( 0.5f,  0.5f, 0.f), XMFLOAT4(0, 0, 1, 1), XMFLOAT2(1, 1) },
		{ XMFLOAT3( 0.5f, -0.5f, 0.f), XMFLOAT4(1, 1, 1, 1), XMFLOAT2(1, 0) }
	};


	UINT indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	std::shared_ptr<VertexBuffer> vertexbuffer = renderer->CreateVertexBuffer(vertex, 4);
	std::shared_ptr<IndexBuffer> indexbuffer = renderer->CreateIndexBuffer(indices, 6);

	std::shared_ptr<Shader> shader = renderer->CreateShader(L"Shaders/Vertex.hlsl", L"Shaders/Pixel.hlsl");

	XMMATRIX obj_one = XMMatrixIdentity();
	obj_one = XMMatrixTranslation(-0.3, 0,  0);
	XMMATRIX obj_two = XMMatrixIdentity();
	obj_two = XMMatrixTranslation( 0.3, 0,  0);
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
		constant_buffer->GetPixelObj()->alpha = 1;
		texture->Bind(0);
		constant_buffer->BindPerObj();
		constant_buffer->BindPixel();
		vertexbuffer->Bind();
		indexbuffer->Bind();
		Command::DrawIndexed(indexbuffer->GetCount());

		// texture two
		shader->Bind();
		constant_buffer->GetPerObj()->Projection = XMMatrixTranspose(Renderer::Get()->GetCamera()->GetProjection());
		constant_buffer->GetPerObj()->View = XMMatrixTranspose(Renderer::Get()->GetCamera()->GetView());
		constant_buffer->GetPerObj()->World = XMMatrixTranspose(obj_two);
		constant_buffer->GetPixelObj()->alpha = imgui_Layer->alpha;
		texture2->Bind(0);
		constant_buffer->BindPerObj();
		constant_buffer->BindPixel();
		vertexbuffer->Bind();
		indexbuffer->Bind();
		Command::DrawIndexed(indexbuffer->GetCount());
		

		imgui_Layer->Draw();
		renderer->EndFrame();
	}


	delete display;
	delete renderer;
	delete imgui_Layer;
}