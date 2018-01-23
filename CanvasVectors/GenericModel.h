#pragma once

#include <BasicEngine\Models\Model.h>
#include<time.h>
#include<stdarg.h>

using namespace BasicEngine::Models;

class GenericModel : public Model
{
public:
	GenericModel(std::vector<std::vector<glm::vec3>> vertexArrays, GLenum renderFormat, glm::vec4 color);
	GenericModel(std::vector<Triangle> triangles, std::vector<std::vector<glm::vec3>> vertexArrays, GLenum renderFormat, glm::vec4 color);
	GenericModel(std::vector<std::vector<glm::vec3>> vertexArrays, glm::vec4 color);
	~GenericModel();

	void Create();
	virtual void Draw(const glm::mat4& projection_matrix,
		const glm::mat4& view_matrix)
		override final;
	virtual void Update() override final;

private:
	void init(std::vector<std::vector<glm::vec3>> vertexArrays, GLenum renderFormat, glm::vec4 color);
	std::vector<std::vector<glm::vec3>> GetNormals(std::vector<std::vector<glm::vec3>> vertexArrays, GLenum renderFormat);
	glm::vec4 color;
	std::vector<std::vector<glm::vec3>> VertexArrays;
	std::vector<std::vector<glm::vec3>> NormalsArrays;
	time_t timer;
	glm::vec3 rotation, rotation_speed;
	std::vector<GLuint> Vaos;
	GLenum RenderFormat;
	bool UseNormals;
};