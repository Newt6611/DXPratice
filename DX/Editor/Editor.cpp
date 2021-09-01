#include "Editor.h"
#include "../World.h"
#include "../Display.h"
#include "../Renderer.h"
#include "../DirectionalLight.h"
#include "../Timer.h"
#include "../ThirdParty/ImGui/ImGuizmo.h"

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

	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 1.f));

}

Editor::~Editor()
{
	ImGui_ImplWin32_Shutdown();
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();
}

void Editor::SetWorld(World* world)
{
	this->current_World = world;
}

void Editor::OnImGuiRender()
{
	GUIBegin();
	
	DrawViewport();

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
		if (ImGui::RadioButton("Translation", m_GuizmosOperation == ImGuizmo::OPERATION::TRANSLATE))
			m_GuizmosOperation = ImGuizmo::OPERATION::TRANSLATE;
		ImGui::SameLine();
		
		//if (ImGui::RadioButton("Rotation", m_GuizmosOperation == ImGuizmo::OPERATION::ROTATE))
		//	m_GuizmosOperation = ImGuizmo::OPERATION::ROTATE;
		//ImGui::SameLine();
		
		if (ImGui::RadioButton("SCALE", m_GuizmosOperation == ImGuizmo::OPERATION::SCALE))
			m_GuizmosOperation = ImGuizmo::OPERATION::SCALE;

		// Postition
		ImGui::DragFloat3("Position", &m_SeletedObj->m_Position.x, 0.1f);

		// Rotation
		ImGui::DragFloat3("Rotation", &m_SeletedObj->m_Rotation.x, 0.05f);

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
	ImGui::Text("FPS %d", Timer::FPS);

	ImGui::ColorPicker4("ClearColor", renderer->GetRenderTargetView()->m_ClearColor);

	ImGui::Checkbox("WireFrame", &renderer->wire_frame);

	ImGui::Checkbox("Transparency", &renderer->transparency);
}

void Editor::DrawViewport()
{
	ImGui::Begin("viewport", NULL, ImGuiWindowFlags_NoScrollbar);

	Renderer::Get()->GetCamera()->SetWidthAndHeight(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
	Renderer::Get()->GetRenderTargetView()->InitEditorTextureSRV(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
	Renderer::Get()->GetDepthStencilState()->InitDepthStencilView(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
	ImTextureID viewportTexture = Renderer::Get()->GetRenderTargetView()->m_TextureSRV;
	Renderer::Get()->GetCamera()->SetWidthAndHeight(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
	ImGui::Image(viewportTexture, ImGui::GetWindowSize());
	
	DrawGuizmos();

	D3D11_VIEWPORT viewport;
	viewport.MaxDepth = 1;
	viewport.MinDepth = 0;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = ImGui::GetWindowWidth();
	viewport.Height = ImGui::GetWindowHeight();
	Renderer::Get()->GetContext()->RSSetViewports(1, &viewport);

	ImGui::End();
}

void Editor::DrawGuizmos()
{
	// Guizmo
	ImGuizmo::SetOrthographic(false);
	ImGuizmo::Enable(true);
	if (m_SeletedObj)
	{
		Camera* camera = Renderer::Get()->GetCamera();
		XMFLOAT4X4 view;
		XMFLOAT4X4 projection;
		XMFLOAT4X4 world;
		XMStoreFloat4x4(&view, camera->GetView());
		XMStoreFloat4x4(&projection, camera->GetProjection());
		XMStoreFloat4x4(&world, m_SeletedObj->m_World);

		ImGuizmo::SetDrawlist();
		ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

		ImGuizmo::Manipulate(*view.m, *projection.m, m_GuizmosOperation, ImGuizmo::MODE::WORLD, *world.m);

		float matrixTranslation[3], matrixRotation[3], matrixScale[3];
		ImGuizmo::DecomposeMatrixToComponents(*world.m, matrixTranslation, matrixRotation, matrixScale);
		if(m_GuizmosOperation == ImGuizmo::OPERATION::TRANSLATE)
			m_SeletedObj->SetPosition(XMFLOAT3(matrixTranslation[0], matrixTranslation[1], matrixTranslation[2]));
		//if(m_GuizmosOperation == ImGuizmo::OPERATION::ROTATE)
		//	m_SeletedObj->SetRotation(XMFLOAT3(matrixRotation[0], matrixRotation[1], matrixRotation[2]));
		if(m_GuizmosOperation == ImGuizmo::OPERATION::SCALE)
			m_SeletedObj->SetScale(XMFLOAT3(matrixScale[0], matrixScale[1], matrixScale[2]));
	}
}

void Editor::GUIBegin()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport();

	Renderer::Get()->GetRenderTargetView()->Bind();

	auto viewport = CD3D11_VIEWPORT(0.f, 0.f, Display::Get()->GetWidth(), Display::Get()->GetHeight());
	Renderer::Get()->GetContext()->RSSetViewports(1, &viewport);
}

void Editor::GUIEnd()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}