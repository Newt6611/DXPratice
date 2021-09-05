#pragma once
#include "Renderer.h"
#include <vector>
#include "Base.h"
#include "Timer.h"

class Editor;
class World;
class Camera;

class IGameObject
{
public:
	virtual void Init() = 0;
	virtual void Update()
	{
		m_World = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z)*
				  XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_Rotation.x), XMConvertToRadians(m_Rotation.y), XMConvertToRadians(m_Rotation.z))*
				  XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	}

	virtual void Render(Camera* camera) = 0;

	void SetPosition(XMFLOAT3 p)
	{
		m_Position = p;
	}

	void SetRotation(XMFLOAT3 r)
	{
		m_Rotation = r;
	}

	void SetScale(XMFLOAT3 s)
	{
		m_Scale = s;
	}

	void SetName(std::string name)
	{
		m_Name = name;
	}

	inline XMFLOAT3 GetPosition() const { return m_Position; }
	inline XMFLOAT3 GetRotation() const { return m_Rotation; }
	inline XMFLOAT3 GetScale() const { return m_Scale; }

protected:
	std::string m_Name;
	XMMATRIX m_World;
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;
	XMFLOAT3 m_Color = XMFLOAT3(1, 1, 1);
	float alpha = 1;
	bool enable = true;

	// For Editor
	friend class Editor;
	bool selected = false;
};