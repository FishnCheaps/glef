#include <iostream>
#include "Glef.hpp"
int main() {
	Glef::use().CreateAndMakeActiveWindow();
	GfModel obj;
	//Testim
	std::vector<GLfloat> vec = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  0.5f, 0.0f, };
	auto shader = GfShaderFactory::use().loadShader("shaders/SimpleVertexShader.vertexshader", "shaders/SimpleFragmentShader.fragmentshader");
	obj.setVertices(vec);
	obj.setShader(&shader);
	Glef::use().addObject(obj);
	GfCamera cam=GfCameraFactory::use().getCamera(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0));
	//Uzhe net
	Glef::use().Proceed(&cam);
}