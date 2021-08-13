#include <iostream>
#include "Display.h"
#include "Renderer.h"

static Display* display = nullptr;
static Renderer* renderer = nullptr;



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	display = Display::Get();
	renderer = Renderer::Get();
	
	display->Init(800, 600);
	renderer->Init();

	
	//     TEST  Draw Square  /////////////////////////////////
	VertexData vertex[] = {
		{ XMFLOAT3(-0.5f, -0.5f, 0.f), XMFLOAT4(1, 0, 0, 1) },
		{ XMFLOAT3(-0.5f,  0.5f, 0.f), XMFLOAT4(0, 1, 0, 1) },
		{ XMFLOAT3( 0.5f,  0.5f, 0.f), XMFLOAT4(0, 0, 1, 1) },
		{ XMFLOAT3( 0.5f, -0.5f, 0.f), XMFLOAT4(1, 1, 1, 1) }
	};

	UINT indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	std::shared_ptr<VertexBuffer> vertexbuffer = renderer->CreateVertexBuffer(vertex, 4);
	std::shared_ptr<IndexBuffer> indexbuffer = renderer->CreateIndexBuffer(indices, 6);

	std::shared_ptr<Shader> shader = renderer->CreateShader(L"Shaders/Vertex.hlsl", L"Shaders/Pixel.hlsl");

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



		shader->Bind();
		vertexbuffer->Bind();
		indexbuffer->Bind();
		renderer->DrawIndexed(indexbuffer->GetCount());




		renderer->EndFrame();
	}


	delete display;
	delete renderer;
}