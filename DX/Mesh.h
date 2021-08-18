#pragma once

#include <vector>
#include <memory>
#include "Texture.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"


class Mesh
{
public:
	Mesh(std::vector<VertexData> vertices, std::vector<UINT> indices, std::vector<std::shared_ptr<Texture>> textures);
	~Mesh();

	void Draw(Shader& shader);


private:
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;

	std::vector<VertexData> vertices;
	std::vector<UINT> indices;
	std::vector<std::shared_ptr<Texture>> textures;
};