#pragma once

#include <DirectXMath.h>

using namespace DirectX;

class Camera
{
public:
	Camera(float angle, float width, float height, float nearZ, float farZ);
	Camera(float width, float height, float nearZ, float farZ);
	~Camera();

	XMMATRIX GetView()const;
	XMMATRIX GetViewProjection() const;
	XMMATRIX GetProjection() const;


private:
	void UpdateCamera();

private:
	XMVECTOR m_LookAt;
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Up;
	XMFLOAT3 m_Right;

	float m_Angle;
	float m_Width;
	float m_Height;
	float m_NearZ;
	float m_FarZ;

	XMMATRIX m_View;
	XMMATRIX m_Projection;

	const XMVECTOR WORLD_UP = XMVectorSet(0, 1, 0, 1);
	const XMVECTOR WORLD_FORWARD = XMVectorSet(0, 0, 1, 1);
};
