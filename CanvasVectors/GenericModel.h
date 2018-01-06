#pragma once

#include <BasicEngine\Rendering\Models\Model.h>
#include<time.h>
#include<stdarg.h>

using namespace BasicEngine::Rendering;
using namespace BasicEngine::Rendering::Models;

class GenericModel : public Model
{
public:
	GenericModel(std::vector<std::vector<glm::vec3>> vertexArrays, GLenum renderFormat);
	GenericModel(std::vector<std::vector<glm::vec3>> vertexArrays);
	~GenericModel();

	void Create();
	virtual void Draw(const glm::mat4& projection_matrix,
		const glm::mat4& view_matrix)
		override final;
	virtual void Update() override final;

private:
	std::vector<glm::vec3> getBoundingBox(std::vector<std::vector<glm::vec3>> vertexArrays);
	std::vector<std::vector<glm::vec3>> GetNormals(std::vector<std::vector<glm::vec3>> vertexArrays, GLenum renderFormat);

	std::vector<std::vector<glm::vec3>> VertexArrays;
	std::vector<std::vector<glm::vec3>> NormalsArrays;
	std::vector<glm::vec3> boundingBox;
	time_t timer;
	glm::vec3 rotation, rotation_speed;
	std::vector<GLuint> Vaos;
	GLenum RenderFormat;
	bool UseNormals;
};