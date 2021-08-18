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
	std::shared_ptr<Texture> texture = renderer->CreateTexture("Textures/wall.jpg");
	std::shared_ptr<Texture> texture2 = renderer->CreateTexture("Textures/window.png");
	std::shared_ptr<Texture> t = renderer->CreateTexture("Textures/t.jpg");

	ConstantBuffer* constant_buffer = new ConstantBuffer();

	VertexData cube_vertices[] = {
		// pos                                       texcoord          normals
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(-1.0f, -1.0f, -1.0f),  },
		{ XMFLOAT3(-1.0f,  1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(-1.0f,  1.0f, -1.0f),  },
		{ XMFLOAT3(1.0f,  1.0f, -1.0f),  XMFLOAT2(1.0f, 0.0f), XMFLOAT3(1.0f,  1.0f, -1.0f),   },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f),  XMFLOAT2(1.0f, 1.0f), XMFLOAT3(1.0f, -1.0f, -1.0f),   },
															 
		{ XMFLOAT3(-1.0f, -1.0f, 1.0f),  XMFLOAT2(1.0f, 1.0f), XMFLOAT3(-1.0f, -1.0f, 1.0f),   },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f),   XMFLOAT2(0.0f, 1.0f), XMFLOAT3(1.0f, -1.0f, 1.0f),    },
		{ XMFLOAT3(1.0f,  1.0f, 1.0f),   XMFLOAT2(0.0f, 0.0f), XMFLOAT3(1.0f,  1.0f, 1.0f),    },
		{ XMFLOAT3(-1.0f,  1.0f, 1.0f),  XMFLOAT2(1.0f, 0.0f), XMFLOAT3(-1.0f,  1.0f, 1.0f),   },
															  
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f),  XMFLOAT2(0.0f, 1.0f), XMFLOAT3(-1.0f, 1.0f, -1.0f),   },
		{ XMFLOAT3(-1.0f, 1.0f,  1.0f),  XMFLOAT2(0.0f, 0.0f), XMFLOAT3(-1.0f, 1.0f,  1.0f),   },
		{ XMFLOAT3(1.0f, 1.0f,  1.0f),   XMFLOAT2(1.0f, 0.0f), XMFLOAT3(1.0f, 1.0f,  1.0f),    },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f),   XMFLOAT2(1.0f, 1.0f), XMFLOAT3(1.0f, 1.0f, -1.0f),    },
															  
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(-1.0f, -1.0f, -1.0f),  },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f),  XMFLOAT2(0.0f, 1.0f), XMFLOAT3(1.0f, -1.0f, -1.0f),   },
		{ XMFLOAT3(1.0f, -1.0f,  1.0f),  XMFLOAT2(0.0f, 0.0f), XMFLOAT3(1.0f, -1.0f,  1.0f),   },
		{ XMFLOAT3(-1.0f, -1.0f,  1.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(-1.0f, -1.0f,  1.0f),  },
															  
		{ XMFLOAT3(-1.0f, -1.0f,  1.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(-1.0f, -1.0f,  1.0f),  },
		{ XMFLOAT3(-1.0f,  1.0f,  1.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(-1.0f,  1.0f,  1.0f),  },
		{ XMFLOAT3(-1.0f,  1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(-1.0f,  1.0f, -1.0f),  },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(-1.0f, -1.0f, -1.0f),  },
															  
		{ XMFLOAT3(1.0f, -1.0f, -1.0f),  XMFLOAT2(0.0f, 1.0f), XMFLOAT3(1.0f, -1.0f, -1.0f),   },
		{ XMFLOAT3(1.0f,  1.0f, -1.0f),  XMFLOAT2(0.0f, 0.0f), XMFLOAT3(1.0f,  1.0f, -1.0f),   },
		{ XMFLOAT3(1.0f,  1.0f,  1.0f),  XMFLOAT2(1.0f, 0.0f), XMFLOAT3(1.0f,  1.0f,  1.0f),   },
		{ XMFLOAT3(1.0f, -1.0f,  1.0f),  XMFLOAT2(1.0f, 1.0f), XMFLOAT3(1.0f, -1.0f,  1.0f),   }
	};
	UINT cube_indices[] = {
		0,  1,  2,
		0,  2,  3,

		4,  5,  6,
		4,  6,  7,

		8,  9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23
	};

	VertexData window_vertices[] = {
		{ XMFLOAT3(-1, -1, 0), XMFLOAT2(0, 0), XMFLOAT3(1, 1, 1) },
		{ XMFLOAT3(-1,  1, 0), XMFLOAT2(0, 1), XMFLOAT3(1, 1, 1) },
		{ XMFLOAT3( 1,  1, 0), XMFLOAT2(1, 1), XMFLOAT3(1, 1, 1) },
		{ XMFLOAT3( 1, -1, 0), XMFLOAT2(1, 0), XMFLOAT3(1, 1, 1) },
	};
	
	UINT window_indices[] = {
		0, 3, 2,
		2, 1, 0
	};

	std::shared_ptr<VertexBuffer> vertexbuffer = renderer->CreateVertexBuffer(cube_vertices, 24);
	std::shared_ptr<IndexBuffer> indexbuffer = renderer->CreateIndexBuffer(cube_indices, 36);

	std::shared_ptr<VertexBuffer> window_vertexBuffer = renderer->CreateVertexBuffer(window_vertices, 4);
	std::shared_ptr<IndexBuffer> window_indicesBuffer = renderer->CreateIndexBuffer(window_indices, 6);

	std::shared_ptr<Shader> shader = renderer->CreateShader(L"Shaders/Vertex.hlsl", L"Shaders/Pixel.hlsl");

	std::shared_ptr<Model> backpack = renderer->CreateModel("Models/nanosuit/nanosuit.obj");

	XMMATRIX cube = XMMatrixIdentity();

	XMMATRIX obj_two = XMMatrixIdentity();
	obj_two = XMMatrixTranslation( 10, 0,  1);
	float r = 0;
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

		r += 0.001;
		if (r > 360)
			r = 0;
		cube = XMMatrixTranslation(0, -8, 0) * XMMatrixRotationY(r) * XMMatrixScaling(1, 1, 1);

		renderer->BeginFrame();

		// texture one
		shader->Bind();
		constant_buffer->GetPerObj()->Projection = XMMatrixTranspose( Renderer::Get()->GetCamera()->GetProjection() );
		constant_buffer->GetPerObj()->View = XMMatrixTranspose( Renderer::Get()->GetCamera()->GetView() );
		constant_buffer->GetPerObj()->World = XMMatrixTranspose(cube);
		constant_buffer->GetPixelObj()->alpha = ImGuiLayer::alpha;
		constant_buffer->BindPerObj();
		constant_buffer->BindPixel();
		backpack->Draw(*shader);

		imgui_Layer->Draw();
		renderer->EndFrame();
	}


	delete display;
	delete renderer;
	delete imgui_Layer;
}