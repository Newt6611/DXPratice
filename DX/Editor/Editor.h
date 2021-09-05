#pragma once

#include "../ImGui/imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_sdl.h"
#include "../ThirdParty/ImGui/ImGuizmo.h"
#include "../IGameObject.h"

class Editor 
{
public:
	Editor();
	~Editor();
	void SetWorld(World* world);

	void OnImGuiRender();

private:
	void DrawGameObjectNode(IGameObject* obj);
	void DrawComponent();
	void DrawSettingAndInfo();
	void DrawViewport();
	void DrawGuizmos();


	void GUIBegin();
	void GUIEnd();

private:
	ImGuizmo::OPERATION m_GuizmosOperation = ImGuizmo::OPERATION::TRANSLATE;

	World* current_World;
	IGameObject* m_SeletedObj = nullptr;
};