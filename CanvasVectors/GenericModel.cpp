#include "GenericModel.h"

#define PI 3.14159265


std::vector<std::vector<glm::vec3>> GenericModel::GetNormals(std::vector<std::vector<glm::vec3>> vertexArrays, GLenum renderFormat) {
	std::vector<std::vector<glm::vec3>> normalsArrays = std::vector<std::vector<glm::vec3>>();
	if (renderFormat == GL_TRIANGLES) {

	}
	else if (renderFormat == GL_TRIANGLE_STRIP) {
		UseNormals = true;
		for (unsigned i = 0; i < vertexArrays.size(); i++) {
			std::vector<glm::vec3> normalsArray = std::vector<glm::vec3>();

			int size = vertexArrays[i].size();

			std::vector<glm::vec3> vertexArray = vertexArrays[i];
			for (unsigned j = 0; j < size; j++) {
				std::vector<glm::vec3> triangleNormals = std::vector<glm::vec3>();
				if (j > 1) {
					glm::vec3 edge1 = glm::vec3(vertexArray[j - 2] - vertexArray[j - 1]);
					glm::vec3 edge2 = glm::vec3(vertexArray[j - 1] - vertexArray[j]);
					triangleNormals.push_back(glm::normalize(glm::cross(edge1, edge2)));
				}
				if (j > 0 && j < size - 1) {
					glm::vec3 edge1 = glm::vec3(vertexArray[j - 1] - vertexArray[j]);
					glm::vec3 edge2 = glm::vec3(vertexArray[j] - vertexArray[j + 1]);
					triangleNormals.push_back(glm::normalize(glm::cross(edge1, edge2)));
				}
				if (j < size - 2) {
					glm::vec3 edge1 = glm::vec3(vertexArray[j] - vertexArray[j + 1]);
					glm::vec3 edge2 = glm::vec3(vertexArray[j + 1] - vertexArray[j + 2]);
					triangleNormals.push_back(glm::normalize(glm::cross(edge1, edge2)));
				}
				glm::vec3 vertexNormal = glm::vec3(0, 0, 0);
				for (unsigned k = 0; k < triangleNormals.size(); k++) {
					vertexNormal = vertexNormal + triangleNormals[k];
				}
				vertexNormal = glm::normalize(vertexNormal);
				normalsArray.push_back(vertexNormal);
			}
			normalsArrays.push_back(normalsArray);
		}
	}
	else {
		//can't calculate normals
	}
	return normalsArrays;
}

GenericModel::GenericModel(std::vector<std::vector<glm::vec3>> vertexArrays, GLenum renderFormat = GL_TRIANGLE_STRIP)
{
	VertexArrays = vertexArrays;
	RenderFormat = renderFormat;
	NormalsArrays = GetNormals(VertexArrays, RenderFormat);
}

GenericModel::GenericModel(std::vector<std::vector<glm::vec3>> vertexArrays)
{
	VertexArrays = vertexArrays;
	RenderFormat = GL_TRIANGLE_STRIP;
	NormalsArrays = GetNormals(VertexArrays, RenderFormat);
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
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(VertexFormat),
			(void*)0
		);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			1,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(VertexFormat),
			(void*)(offsetof(VertexFormat,
				VertexFormat::color))
		);

		if (UseNormals == true) {
			GLuint normalbuffer;
			glGenBuffers(1, &normalbuffer);
			glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
			glBufferData(GL_ARRAY_BUFFER, NormalsArrays[i].size() * sizeof(glm::vec3), &NormalsArrays[i][0], GL_STATIC_DRAW);

			// 3rd attribute buffer : normals
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
			glVertexAttribPointer(
				2,                                // attribute
				3,                                // size
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)0                          // array buffer offset
			);
		}

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

	glm::mat4 Model = glm::mat4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, &projection_matrix[0][0]);



	for (int i = 0; i < Vaos.size(); i++) {
		glBindVertexArray(Vaos[i]);
		glDrawArrays(RenderFormat, 0, VertexArrays[i].size());
		//glDrawArrays(RenderFormat, 0, 100); - adds lines to origin when GL_TRIANGLE_STRIP - quite a nice effect :)
	}
}

