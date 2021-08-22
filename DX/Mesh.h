#pragma once

#include <vector>
#include <memory>
#include "Texture.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Base.h"


class Mesh
{
public:
	Mesh(std::vector<VertexData> vertices, std::vector<UINT> indices, std::vector<std::shared_ptr<Texture>> textures);
	~Mesh();

	void Draw();


private:
	Ref<VertexBuffer> m_VertexBuffer;
	Ref<IndexBuffer> m_IndexBuffer;
	Ref<Texture> m_DefaultTexture;

	std::vector<VertexData> vertices;
	std::vector<UINT> indices;
	std::vector<Ref<Texture>> textures;
};