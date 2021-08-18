#include "Mesh.h"
#include "Command.h"

Mesh::Mesh(std::vector<VertexData> vertices, std::vector<UINT> indices, std::vector<std::shared_ptr<Texture>> textures)
{
	Renderer* renderer = Renderer::Get();
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	m_VertexBuffer = renderer->CreateVertexBuffer(vertices.data(), vertices.size());
	m_IndexBuffer = renderer->CreateIndexBuffer(indices.data(), indices.size());
}

Mesh::~Mesh()
{

}

void Mesh::Draw()
{
	for (int i = 0; i < textures.size(); i++)
	{
		
		switch (textures[i]->GetType())
		{
		case TextureType::Diffuse:
			textures[i]->Bind(0);
			break;
		case TextureType::Specular:
			textures[i]->Bind(1);
			break;
		case TextureType::Normal:
			textures[i]->Bind(2);
			break;
		}
	}

	m_VertexBuffer->Bind();
	m_IndexBuffer->Bind();

	//Command::DrawIndexed(m_IndexBuffer->GetCount());
	Command::Draw(m_VertexBuffer->GetCount());
}