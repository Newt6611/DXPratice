#include "Mesh.h"
#include "Command.h"

Mesh::Mesh(std::vector<VertexData> vertices, std::vector<UINT> indices, std::vector<std::shared_ptr<Texture>> textures)
{
	Renderer* renderer = Renderer::Get();
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	this->m_DefaultTexture = renderer->CreateTexture("Textures/Default.png");

	m_VertexBuffer = renderer->CreateVertexBuffer(vertices.data(), vertices.size());
	m_IndexBuffer = renderer->CreateIndexBuffer(indices.data(), indices.size());
}

Mesh::~Mesh()
{

}

void Mesh::Draw()
{
	m_VertexBuffer->Bind();
	m_IndexBuffer->Bind();

	bool d_bound = false;
	bool s_bound = false;
	bool n_bound = false;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		switch (textures[i]->GetType())
		{
		case TextureType::Diffuse:
			if (!d_bound)
			{
				textures[i]->Bind(0);
				d_bound = true;
			}
			break;
		case TextureType::Specular:
			if (!s_bound)
			{
				textures[i]->Bind(1);
				s_bound = true;
			}
			break;
		case TextureType::Normal:
			if (!n_bound)
			{
				textures[i]->Bind(2);
				n_bound = true;
			}
			break;
		}
	}

	if (!d_bound)
	{ 
		this->m_DefaultTexture->Bind(0);
	}
	
	if (!s_bound)
	{
		this->m_DefaultTexture->Bind(1);
	}
	
	if (!n_bound)
	{
		this->m_DefaultTexture->Bind(2);
	}

	Command::DrawIndexed(m_IndexBuffer->GetCount());
}