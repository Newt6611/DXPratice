#pragma once

#include "../IGameObject.h"

class World;

class Sponza : public IGameObject
{
public:
	Sponza(World* world);
	virtual ~Sponza();
	void Init();
	void Update();
	void Render(Camera* camera);

private:
	float r;

	Ref<Model> m_Model;
	Ref<Shader> m_Shader;
	Ref<ConstantBuffer<VS_Object>> m_ConstantBuffer;
};