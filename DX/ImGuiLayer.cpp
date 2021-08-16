#include "ImGuiLayer.h"
#include "Display.h"
#include "Renderer.h"
#include "Log.h"

bool ImGuiLayer::wire_frame;
float ImGuiLayer::clear_color[4];

ImGuiLayer::ImGuiLayer()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	if (!ImGui_ImplWin32_Init(Display::Get()->GetHandle()))
	{
		LogError("Error When Init Win32");
	}

	if(!ImGui_ImplDX11_Init(Renderer::Get()->GetDevice(), Renderer::Get()->GetContext()))
	{
		LogError("Error When Init ImGui DX11");
	}
	ImGui::StyleColorsDark();
}

ImGuiLayer::~ImGuiLayer()
{
	ImGui_ImplWin32_Shutdown();
	ImGui_ImplDX11_Shutdown();
}

void ImGuiLayer::Draw()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("DXPratice");

	ImGui::Checkbox("WireFrame", &wire_frame);
	ImGui::ColorPicker4("ClearColor", clear_color);



	Logic();
	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}

void ImGuiLayer::Logic()
{
	RasterzierState* rasterizerState = Renderer::Get()->GetRasterizerState();
	if (wire_frame && rasterizerState->GetType() == RasterzierStateType::Solid)
		rasterizerState->SetState(RasterzierStateType::WireFrame);
	else if (!wire_frame && rasterizerState->GetType() == RasterzierStateType::WireFrame)
		rasterizerState->SetState(RasterzierStateType::Solid);

	RenderTargetView* renderTargetView = Renderer::Get()->GetRenderTargetView();
	renderTargetView->SetClearColor(clear_color);
}