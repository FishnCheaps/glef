#include <iostream>
#include "Glef.hpp"
int main() {
	Glef::use().CreateAndMakeActiveWindow();
	GfObject obj;
	//Testim
	std::vector<GLfloat> vec = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  0.5f, 0.0f, };
	auto shader = GfShaderFactory::use().loadShader("shaders/SimpleVertexShader.vertexshader", "shaders/SimpleFragmentShader.fragmentshader");
	obj.setMesh(vec);
	obj.setShader(shader);
	Glef::use().addObject(obj);
	//Uzhe net
	Glef::use().Proceed();
}