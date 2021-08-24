#include "Model.h"
#include "Mesh.h"
#include "Log.h"
#include "Renderer.h"

Model::Model(std::string filePath)
{
	this->m_FilePath = filePath;
	this->directory = filePath.substr(0, filePath.find_last_of('/'));
	LoadMesh(filePath);
}

Model::~Model()
{

}

void Model::Draw()
{
	for (unsigned int i = 0; i < m_Meshs.size(); i++)
	{
		m_Meshs[i].Draw();
	}
}

void Model::LoadMesh(std::string filePath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, 
		aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_ConvertToLeftHanded | aiProcess_CalcTangentSpace);

	if (!scene || !scene->mRootNode)
	{
		LogError("Failed When Loading Model !");
	}
	else 
	{
		ProccessNode(scene, scene->mRootNode);
	}
}

void Model::ProccessNode(const aiScene* scene, aiNode* node)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshs.push_back(ProccessMesh(scene, mesh));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProccessNode(scene, node->mChildren[i]);
	}
}

Mesh Model::ProccessMesh(const aiScene* scene, aiMesh* mesh)
{
	std::vector<VertexData> vertices;
	std::vector<UINT> indices;
	std::vector<std::shared_ptr<Texture>> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		VertexData vertex_data;
		XMFLOAT3 temp;

		temp.x = mesh->mVertices[i].x;
		temp.y = mesh->mVertices[i].y;
		temp.z = mesh->mVertices[i].z;
		vertex_data.pos = temp;

		if (mesh->HasNormals())
		{
			temp.x = mesh->mNormals[i].x;
			temp.y = mesh->mNormals[i].y;
			temp.z = mesh->mNormals[i].z;
			vertex_data.normal = temp;
		}

		if (mesh->mTextureCoords[0])
		{
			temp.x = mesh->mTextureCoords[0][i].x;
			temp.y = mesh->mTextureCoords[0][i].y;

			vertex_data.texcoord.x = temp.x;
			vertex_data.texcoord.y = temp.y;
		
			temp.x = mesh->mTangents[i].x;
			temp.y = mesh->mTangents[i].y;
			temp.z = mesh->mTangents[i].z;
			vertex_data.tangent = temp;

			temp.x = mesh->mBitangents[i].x;
			temp.y = mesh->mBitangents[i].y;
			temp.z = mesh->mBitangents[i].z;
			vertex_data.bitangent = temp;
		}
		else
		{
			vertex_data.texcoord.x = 0;
			vertex_data.texcoord.y = 0;
		}

		vertices.push_back(vertex_data);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	// diffuse
	std::vector<std::shared_ptr<Texture>> diffuseTextures = LoadMaterialTexture(material, aiTextureType_DIFFUSE, TextureType::Diffuse);
	textures.insert(textures.end(), diffuseTextures.begin(), diffuseTextures.end());

	// specular
	std::vector<std::shared_ptr<Texture>> specularTextures = LoadMaterialTexture(material, aiTextureType_SPECULAR, TextureType::Specular);
	textures.insert(textures.end(), specularTextures.begin(), specularTextures.end());

	// normal
	std::vector<std::shared_ptr<Texture>> normalTextures = LoadMaterialTexture(material, aiTextureType_NORMALS, TextureType::Normal);
	textures.insert(textures.end(), normalTextures.begin(), normalTextures.end());

	return Mesh(vertices, indices, textures);
}

std::vector<std::shared_ptr<Texture>> Model::LoadMaterialTexture(aiMaterial* material, aiTextureType type, TextureType texture_type)
{
	std::vector<std::shared_ptr<Texture>> textures;
	for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString str;
		material->GetTexture(type, i, &str);
		bool skip = false;

		for (unsigned int j = 0; j < loaded_texture_cache.size(); j++)
		{
			if (std::strcmp(loaded_texture_cache[j]->GetPath().data(), str.C_Str()) == 0)
			{
				textures.push_back(loaded_texture_cache[j]);
				skip = true;
				break;
			}
		}

		if (!skip)
		{
			std::string p = str.C_Str();
			std::string fullPath = this->directory + '/' + p;
			std::shared_ptr<Texture> t = Renderer::Get()->CreateTexture(fullPath, texture_type);

			textures.push_back(t);
			loaded_texture_cache.push_back(t);
		}
	}

	return textures;
}
