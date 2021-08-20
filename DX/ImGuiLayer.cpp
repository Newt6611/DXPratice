#include "ImGuiLayer.h"
#include "Display.h"
#include "Renderer.h"
#include "Log.h"

bool ImGuiLayer::wire_frame;
float ImGuiLayer::clear_color[4] = { 0.5f, 0.1f, 0.2f, 1.f };

float ImGuiLayer::alpha = 1;

const char* ImGuiLayer::current_BlendState = "None";

float ImGuiLayer::lightDir[3] = { 0 ,0 ,-1 };

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

	// Clear Color
	ImGui::SliderFloat("Alpha", &alpha, 0, 1);
	
	// WireFrame
	ImGui::Checkbox("WireFrame", &wire_frame);
	ImGui::ColorEdit4("ClearColor", clear_color);
	
	
	// BlendState
	if (ImGui::BeginCombo("BlendState", current_BlendState))
	{
		for (int i = 0; i < 2; i++)
		{
			bool is_selected = (current_BlendState == blend_state[i]);
			if (ImGui::Selectable(blend_state[i], is_selected))
				current_BlendState = blend_state[i];
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	// Light Direction
	ImGui::DragFloat3("Light Direction", lightDir, 0.1, -360, 360);

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


	BlendState* blendState = Renderer::Get()->GetBlendState();
	if (current_BlendState == "None")
	{
		blendState->SetBlendState(BlendStateType::None);
	}
	else if (current_BlendState == "Transparency")
	{
		blendState->SetBlendState(BlendStateType::Transparency);
	}
}