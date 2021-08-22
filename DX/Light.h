#pragma once

#include <DirectXMath.h>

class Light
{
public:
	virtual void Bind(unsigned int slot) = 0;
};