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

	std::shared_ptr<ConstantBuffer<PS_Object>> pixel_const = std::make_shared<ConstantBuffer<PS_Object>>();
	pixel_const->Init(ShaderStage::PS, renderer->GetDevice(), renderer->GetContext());

	MSG msg = { };
	while (true)
	{
		if (PeekMessage(&msg, display->GetHandle(), 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT) break;
		}

		PS_Object o;
		o.alpha = ImGuiLayer::alpha;
		pixel_const->SetData(o);
		pixel_const->Bind(0);
		///////////////     UPDATE      /////////////////////////
		world->Update();

		/////////////////////////////////////////////////////////


		//////////////      Render      ////////////////////////
		renderer->BeginFrame();

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