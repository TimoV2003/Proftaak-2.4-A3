#pragma once
#include "DrawComponent.h"
#include "tigl.h"
using tigl::Vertex;

#include <vector>
class CubeDrawComponent : public DrawComponent
{
	float size;
public:
	CubeDrawComponent(float size) : size(size) {};
	~CubeDrawComponent() = default;
	virtual void draw() override;
};

