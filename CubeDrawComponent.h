#pragma once
#include "DrawComponent.h"
#include "tigl.h"
using tigl::Vertex;

#include <vector>
class CubeDrawComponent : public DrawComponent
{
	std::vector<Vertex> verts;
public:
	CubeDrawComponent(const std::string id, float size);
	~CubeDrawComponent() = default;

	virtual void draw() override;
};

