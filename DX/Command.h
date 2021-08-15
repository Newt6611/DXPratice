#pragma once

#include "Renderer.h"

class Command
{
public:
	static void DrawIndexed(int indexCount)
	{
		Renderer::Get()->GetContext()->DrawIndexed(indexCount, 0, 0);
	}

	static void Draw(int vertexCount)
	{
		Renderer::Get()->GetContext()->Draw(vertexCount, 0);
	}
};