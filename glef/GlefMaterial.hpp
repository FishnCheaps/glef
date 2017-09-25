#pragma once
#include "common/commonIncludes.h"

class GfMaterial
{
public:
	float material_specular_factor; // should be >= 1.0
	float material_specular_intensity;
	glm::vec3 material_emission;

	 GLint uniformMaterialSpecularFactor;
	 GLint uniformMaterialSpecularIntensity;
	 GLint uniformMaterialEmission;
	 void registerMaterials(GLuint programId)
	{
		GLint uniformMaterialSpecularFactor = getUniformLocation(programId, "materialSpecularFactor");
		GLint uniformMaterialSpecularIntensity = getUniformLocation(programId, "materialSpecularIntensity");
		GLint uniformMaterialEmission = getUniformLocation(programId, "materialEmission");
	}
private:

};
