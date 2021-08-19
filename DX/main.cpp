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


	MSG msg = { };
	while (true)
	{
		if (PeekMessage(&msg, display->GetHandle(), 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT) break;
		}

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