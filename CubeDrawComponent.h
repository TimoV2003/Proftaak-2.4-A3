#pragma once
#include "DrawComponent.h"
#include "tigl.h"
using tigl::Vertex;

#include <vector>
class CubeDrawComponent : public DrawComponent
{
	std::vector<Vertex> verts;
public:
	CubeDrawComponent(float size);
	~CubeDrawComponent();


	virtual void draw() override;

};

