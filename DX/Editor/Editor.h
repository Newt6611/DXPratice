#pragma once

#include "../ImGui/imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

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

	void GUIBegin();
	void GUIEnd();

private:
	World* current_World;
	IGameObject* m_SeletedObj;
};