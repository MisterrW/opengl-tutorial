#include "GenericModel.h"

#define PI 3.14159265

GenericModel::GenericModel(std::vector<std::vector<glm::vec3>> vertexArrays)
{
	VertexArrays = vertexArrays;
	//DrawType = drawType
}

GenericModel::~GenericModel()
{
}

void GenericModel::Create()
{
	time(&timer);

	for (int i = 0; i < VertexArrays.size(); i++) {
		GLuint vao;
		GLuint vbo;
		std::vector<glm::vec3> Vertices = VertexArrays[i];
		std::vector<VertexFormat> vertices;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		for (unsigned i = 0; i < Vertices.size(); i++) {
			vertices.push_back(VertexFormat(Vertices[i],
				glm::vec4(1.0, 1.0, 1.0, 1.0)));
		}

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * Vertices.size(), &vertices[0], GL_STATIC_DRAW);
		/*glEnableVertexAttribArray(i * 2);
		glVertexAttribPointer((i * 2), 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
		glEnableVertexAttribArray((i * 2) + 1);
		glVertexAttribPointer((i * 2) + 1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));*/

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));

		glBindVertexArray(0);
		this->vbos.push_back(vbo);
		this->Vaos.push_back(vao);
	}

}

void GenericModel::Update()
{

}

void GenericModel::Draw(const glm::mat4& projection_matrix,
	const glm::mat4& view_matrix)
{
	rotation = 0.0005f * rotation_speed + rotation;

	glm::vec3 rotation_sin = glm::vec3(rotation.x * PI / 180, rotation.y * PI / 180, rotation.z * PI / 180);

	glUseProgram(program);
	glUniform3f(glGetUniformLocation(program, "rotation"),
		rotation_sin.x,
		rotation_sin.y,
		rotation_sin.z);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1,
		false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);

	for (int i = 0; i < Vaos.size(); i++) {
		glBindVertexArray(Vaos[i]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, VertexArrays[i].size());
	}
}

