#pragma once

#include <d3d11.h>
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "imgui.h"

class ImGuiLayer
{
public:
	ImGuiLayer();
	~ImGuiLayer();

	void Draw();

private:
	void Logic();

private:
	static bool wire_frame;
	static float clear_color[4];
};