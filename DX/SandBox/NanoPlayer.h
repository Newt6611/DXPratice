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
	Ref<Model> m_Model;
	Ref<Shader> m_Shader;
	Ref<ConstantBuffer<VS_Object>> m_ConstantBuffer;
};