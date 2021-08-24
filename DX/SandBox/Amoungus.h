#pragma once

#include "../IGameObject.h"

class World;

class Amoungus : public IGameObject
{
public:
	Amoungus(World* world);
	virtual ~Amoungus();
	void Init();
	void Update();
	void Render(Camera* camera);

private:
	float r;

	Ref<Model> m_Model;
	Ref<Shader> m_Shader;
	Ref<ConstantBuffer<VS_Object>> m_ConstantBuffer;
};