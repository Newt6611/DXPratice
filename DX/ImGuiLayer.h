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


	// test 
	static float alpha;
private:
	void Logic();

private:
	static bool wire_frame;
	static float clear_color[4];

	static const char* current_BlendState;
	const char* blend_state[2] = { "None", "Transparency"};
};