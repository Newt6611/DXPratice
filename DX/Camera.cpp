#include "Camera.h"
#include "Log.h"

Camera::Camera(float angle, float width, float height, float nearZ, float farZ)
	: m_Angle(angle), m_Width(width), m_Height(height), m_NearZ(nearZ), m_FarZ(farZ),
	m_Position(0, 0, -10), m_Rotation(0, 0, 0)
{
	m_Projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(angle), static_cast<float>(width) / static_cast<float>(height), nearZ, farZ);

	m_View = XMMatrixIdentity();
	UpdateCamera();
}

Camera::Camera(float width, float height, float nearZ, float farZ)
	: m_Angle(45), m_Width(width), m_Height(height), m_NearZ(nearZ), m_FarZ(farZ),
	m_Position(0, 0, -10), m_Rotation(0, 0, 0)
{
	m_Projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(45), static_cast<float>(width) / static_cast<float>(height), nearZ, farZ);

	m_View = XMMatrixIdentity();
	UpdateCamera();
}

Camera::~Camera()
{

}

XMMATRIX Camera::GetView() const
{
	return m_View;
}

XMMATRIX Camera::GetViewProjection() const
{
	return XMMatrixMultiply(m_View, m_Projection);
}

XMMATRIX Camera::GetProjection() const
{
	return m_Projection;
}

void Camera::UpdateCamera()
{
	XMMATRIX rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	
	//XMVECTOR target = XMVector3TransformCoord(WORLD_FORWARD, rot);
	//target += XMVectorSet(m_Position.x, m_Position.y, m_Position.z, 1);

	XMVECTOR look_vec = XMVector3Transform(WORLD_FORWARD, rot);

	m_LookAt = XMVectorSet( m_Position.x, m_Position.y, m_Position.z, 1 ) + look_vec;

	XMVECTOR up = XMVector3TransformCoord(WORLD_UP, rot);
	m_View = XMMatrixLookAtLH(XMVectorSet(m_Position.x, m_Position.y, m_Position.z, 1), m_LookAt, up);
}
