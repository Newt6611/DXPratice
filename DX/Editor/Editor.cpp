#include "Editor.h"
#include "../World.h"
#include "../Display.h"
#include "../Renderer.h"
#include "../DirectionalLight.h"

Editor::Editor()
{
	// Init ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	if (!ImGui_ImplWin32_Init(Display::Get()->GetHandle()))
	{
		LogError("Error When Init Win32");
	}

	if (!ImGui_ImplDX11_Init(Renderer::Get()->GetDevice(), Renderer::Get()->GetContext()))
	{
		LogError("Error When Init ImGui DX11");
	}
	ImGui::StyleColorsDark();
}

Editor::~Editor()
{
	ImGui_ImplWin32_Shutdown();
	ImGui_ImplDX11_Shutdown();
}

void Editor::SetWorld(World* world)
{
	this->current_World = world;
}

void Editor::OnImGuiRender()
{
	GUIBegin();

	ImGui::Begin("Hierarchy");
	for (int i = 0; i < current_World->m_GameObjects.size(); i++)
	{
		DrawGameObjectNode(current_World->m_GameObjects[i]);
	}
	ImGui::End();


	ImGui::Begin("Component");
	DrawComponent();
	ImGui::End();

	ImGui::Begin("Setting");
	DrawSettingAndInfo();
	ImGui::End();

	GUIEnd();
}

void Editor::DrawGameObjectNode(IGameObject* obj)
{
	if (ImGui::Selectable(obj->m_Name.c_str(), obj->selected) && !obj->selected)
	{
		if(m_SeletedObj != nullptr)
			m_SeletedObj->selected = false;

		m_SeletedObj = obj;
		obj->selected = true;
	}
}

void Editor::DrawComponent()
{
	
	if (m_SeletedObj)
	{
		// Postition
		float* temp[3];
		temp[0] = &m_SeletedObj->m_Position.x;
		temp[1] = &m_SeletedObj->m_Position.y;
		temp[2] = &m_SeletedObj->m_Position.z;
		ImGui::DragFloat3("Position", *temp, 0.1f);

		// Rotation
		temp[0] = &m_SeletedObj->m_Rotation.x;
		temp[1] = &m_SeletedObj->m_Rotation.y;
		temp[2] = &m_SeletedObj->m_Rotation.z;
		ImGui::DragFloat3("Rotation", *temp, 0.1f);

		// Rotation
		temp[0] = &m_SeletedObj->m_Scale.x;
		temp[1] = &m_SeletedObj->m_Scale.y;
		temp[2] = &m_SeletedObj->m_Scale.z;
		ImGui::DragFloat3("Scale", *temp, 0.1f);

		// Color
		temp[0] = &m_SeletedObj->m_Color.x;
		temp[1] = &m_SeletedObj->m_Color.y;
		temp[2] = &m_SeletedObj->m_Color.z;
		ImGui::ColorPicker3("Color", *temp);

		// Alpha
		ImGui::DragFloat("Alpha", &m_SeletedObj->alpha, 0.01f, 0, 1);



		// Directional Light
		DirectionalLight* d_Light = dynamic_cast<DirectionalLight*>(m_SeletedObj);
		if (d_Light)
		{
			ImGui::Text("Direcional Light");
			temp[0] = &d_Light->m_Ambient.x;
			temp[1] = &d_Light->m_Ambient.y;
			temp[2] = &d_Light->m_Ambient.z;
			ImGui::DragFloat3("Ambient", *temp, 0.01f, 0.f, 1.f);

			temp[0] = &d_Light->m_Diffuse.x;
			temp[1] = &d_Light->m_Diffuse.y;
			temp[2] = &d_Light->m_Diffuse.z;
			ImGui::DragFloat3("Diffuse", *temp, 0.01f, 0.f, 1.f);

			temp[0] = &d_Light->m_Specular.x;
			temp[1] = &d_Light->m_Specular.y;
			temp[2] = &d_Light->m_Specular.z;
			ImGui::DragFloat3("Specular", *temp, 0.01f, 0.f, 1.f);
		}
	}
}

void Editor::DrawSettingAndInfo()
{
	Renderer* renderer = Renderer::Get();
	ImGui::ColorPicker4("ClearColor", renderer->GetRenderTargetView()->m_ClearColor);

	ImGui::Checkbox("WireFrame", &renderer->wire_frame);

	ImGui::Checkbox("Transparency", &renderer->transparency);
}

void Editor::GUIBegin()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void Editor::GUIEnd()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}