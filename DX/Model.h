#pragma once

#include <string>
#include "Mesh.h"
#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "Shader.h"

class Model 
{
public:
	Model(std::string filePath);
	~Model();

	void Draw(Shader& shader);

private:
	void LoadMesh(std::string filePath);
	void ProccessNode(const aiScene* scene, aiNode* node);
	Mesh ProccessMesh(const aiScene* scene, aiMesh* mesh);
	std::vector<std::shared_ptr<Texture>> LoadMaterialTexture(aiMaterial* material, aiTextureType type, TextureType texture_type);

private:
	std::string directory;
	std::string m_FilePath;
	std::vector<Mesh> m_Meshs;

	std::vector<std::shared_ptr<Texture>> loaded_texture_cache;
};