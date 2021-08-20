#include <iostream>
#include <cstdlib>
#include "Display.h"
#include "Renderer.h"
#include "Log.h"
#include "Command.h"
#include "ImGuiLayer.h"
#include "World.h"

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
	



	World* world = new World;
	
	world->Init();

	Ref<ConstantBuffer<PS_PerFrame>> pixel_const = renderer->CreateConstantBuffer<PS_PerFrame>(ShaderStage::PS);
	Ref<DirectionalLight> direction_light = renderer->CreateDirectionalLight();

	MSG msg = { };
	while (true)
	{
		if (PeekMessage(&msg, display->GetHandle(), 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT) break;
		}

		pixel_const->GetData().alpha = ImGuiLayer::alpha;
		pixel_const->GetData().eyePos = renderer->GetCamera()->GetPosition();
		pixel_const->Bind(0);
		///////////////     UPDATE      /////////////////////////
		world->Update();

		/////////////////////////////////////////////////////////


		//////////////      Render      ////////////////////////
		renderer->BeginFrame();

		direction_light->SetDirection(XMFLOAT3(ImGuiLayer::lightDir));
		direction_light->Bind(1);

		world->Render();
		
		imgui_Layer->Draw();
		
		renderer->EndFrame();
		////////////////////////////////////////////////////////
		
		
	}


	delete display;
	delete renderer;
	delete imgui_Layer;
	delete world;
}