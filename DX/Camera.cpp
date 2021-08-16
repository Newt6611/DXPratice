#include "Camera.h"
#include "Log.h"

Camera::Camera(float angle, float width, float height, float nearZ, float farZ)
	: m_Angle(angle), m_Width(width), m_Height(height), m_NearZ(nearZ), m_FarZ(farZ),
	m_Position(0, 0, -1), m_LookAt(0, 0, 0)
{
	m_Projection = XMMatrixPerspectiveFovRH(XMConvertToRadians(angle), static_cast<float>(width) / static_cast<float>(height), nearZ, farZ);

	m_View = XMMatrixIdentity();
	UpdateCamera();
}

Camera::Camera(float width, float height, float nearZ, float farZ)
	: m_Angle(45), m_Width(width), m_Height(height), m_NearZ(nearZ), m_FarZ(farZ),
	m_Position(0, 0, -1), m_LookAt(0, 0, 0)
{
	m_Projection = XMMatrixPerspectiveFovRH(XMConvertToRadians(90), static_cast<float>(width) / static_cast<float>(height), nearZ, farZ);

	m_View = XMMatrixIdentity();
	UpdateCamera();
}

Camera::~Camera()
{

}

XMMATRIX Camera::GetView() const
{
	return XMMatrixLookAtRH(XMLoadFloat3(&m_Position), XMLoadFloat3(&m_LookAt), XMLoadFloat3(&WROLD_UP));
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
	XMVECTOR forward = XMVector3Normalize( XMLoadFloat3(&m_LookAt) - XMLoadFloat3(&m_Position) );

	XMStoreFloat3( &m_Right, XMVector3Cross(forward, XMLoadFloat3(&WROLD_UP)) );
	XMStoreFloat3( &m_Up, XMVector3Cross(forward, XMLoadFloat3(&m_Right)) );
}
