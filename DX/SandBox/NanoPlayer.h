#pragma once

#include "../IGameObject.h"

class World;

class NanoPlayer : public IGameObject
{
public:
	NanoPlayer(World* world);
	virtual ~NanoPlayer();
	void Init();
	void Update();
	void Render();

private:
	float r;

	Camera* camera;
	std::shared_ptr<Model> m_Model;
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<ConstantBuffer<VS_Object>> m_ConstantBuffer;
};