#pragma once

#include <BasicEngine\Rendering\Models\Model.h>
#include<time.h>
#include<stdarg.h>

using namespace BasicEngine::Rendering;
using namespace BasicEngine::Rendering::Models;

class GenericModel : public Model
{
public:
	GenericModel(std::vector<std::vector<glm::vec3>> vertexArrays);
	~GenericModel();

	void Create();
	virtual void Draw(const glm::mat4& projection_matrix,
		const glm::mat4& view_matrix)
		override final;
	virtual void Update() override final;

private:
	glm::vec3 rotation, rotation_speed;
	std::vector<std::vector<glm::vec3>> VertexArrays;
	time_t timer;
	std::vector<GLuint> Vaos;
};