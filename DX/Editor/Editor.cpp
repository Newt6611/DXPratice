#include "Editor.h"
#include "../World.h"
#include "../Display.h"
#include "../Renderer.h"
#include "../DirectionalLight.h"
#include "ImGuizmo.h"

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

	//ImGui::Begin("viewport");
	//ImTextureID viewportTexture = static_cast<void*>(Renderer::Get()->GetRenderTargetView()->m_RenderTargetView);
	//ImGui::Image(viewportTexture, ImVec2{960, 600});
	//ImGui::End();

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

	/*
	ImGui::Begin("D");
	if (m_SeletedObj)
	{
		Camera* camera = Renderer::Get()->GetCamera();
		XMFLOAT4X4 view;
		XMFLOAT4X4 projection;
		XMFLOAT4X4 world;
		XMStoreFloat4x4(&view, camera->GetView());
		XMStoreFloat4x4(&projection, camera->GetProjection());
		XMStoreFloat4x4(&world, m_SeletedObj->m_World);

		ImGuizmo::Enable(true);
		ImGuizmo::SetOrthographic(false);
		ImGuizmo::SetDrawlist();
		ImGuiIO& io = ImGui::GetIO();
		//ImGuizmo::SetRect(200, 200, Display::Get()->GetWidth(), Display::Get()->GetHeight());
		ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());
		ImGuizmo::DrawCubes(*view.m, *projection.m, *world.m, 1);
		ImGuizmo::Manipulate(*view.m, *projection.m, ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::MODE::LOCAL, *world.m);
	}
	ImGui::End();
	*/


	GUIEnd();
}

void Editor::DrawGameObjectNode(IGameObject* obj)
{
	if (ImGui::Selectable(obj->m_Name.c_str(), obj->selected) && !obj->selected)
	{
		if (m_SeletedObj != nullptr)
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
		ImGui::DragFloat3("Position", &m_SeletedObj->m_Position.x, 0.1f);

		// Rotation
		ImGui::DragFloat3("Rotation", &m_SeletedObj->m_Rotation.x, 0.1f);

		// Rotation
		ImGui::DragFloat3("Scale", &m_SeletedObj->m_Scale.x, 0.1f);

		// Color
		ImGui::ColorEdit3("Color", &m_SeletedObj->m_Color.x);

		// Alpha
		ImGui::DragFloat("Alpha", &m_SeletedObj->alpha, 0.01f, 0, 1);



		// Directional Light
		DirectionalLight* d_Light = dynamic_cast<DirectionalLight*>(m_SeletedObj);
		if (d_Light)
		{
			ImGui::Text("Direcional Light");
			ImGui::ColorEdit3("Ambient", &d_Light->m_Ambient.x);

			ImGui::ColorEdit3("Diffuse", &d_Light->m_Diffuse.x);

			ImGui::ColorEdit3("Specular", &d_Light->m_Specular.x);
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
	ImGuizmo::BeginFrame();
}

void Editor::GUIEnd()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}