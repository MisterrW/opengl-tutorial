#include "GenericModel.h"

std::vector<std::vector<glm::vec3>> GenericModel::GetNormals(std::vector<std::vector<glm::vec3>> vertexArrays, GLenum renderFormat) {
	std::vector<std::vector<glm::vec3>> normalsArrays = std::vector<std::vector<glm::vec3>>();
	if (renderFormat == GL_TRIANGLES) {

	}
	else if (renderFormat == GL_TRIANGLE_STRIP) {
		UseNormals = true;
		glm::vec3 edge1;
		glm::vec3 edge2;
		glm::vec3 edge3;
		glm::vec3 edge4;
		bool haveEdge1;
		bool haveEdge2;
		bool haveEdge3;
		bool haveEdge4;
		std::vector<glm::vec3> vertexArray;
		int size;

		glm::vec3 not_normalised;
		
		glm::vec3 nullVector = glm::vec3();
		for (unsigned i = 0; i < vertexArrays.size(); i++) {
			std::vector<glm::vec3> normalsArray = std::vector<glm::vec3>();

			size = vertexArrays[i].size();
			vertexArray = vertexArrays[i];

			for (unsigned j = 0; j < size; j++) {
				haveEdge1 = false;
				haveEdge2 = false;
				haveEdge3 = false;
				haveEdge4 = false;
				if (j > 1) {
					edge1 = glm::vec3(vertexArray[j - 2] - vertexArray[j - 1]);
					edge2 = glm::vec3(vertexArray[j - 1] - vertexArray[j]);
					haveEdge1 = true;
					haveEdge2 = true;
				}
				if (j > 0 && j < size - 1) {
					edge3 = glm::vec3(vertexArray[j] - vertexArray[j + 1]);
					haveEdge3 = true;
				}
				if (j < size - 2) {
					edge4 = glm::vec3(vertexArray[j + 1] - vertexArray[j + 2]);
					haveEdge4 = true;
				}

				std::vector<glm::vec3> triangleNormals = std::vector<glm::vec3>();
				if (haveEdge1 && haveEdge2) {
					not_normalised = glm::cross(edge1, edge2);
					if (not_normalised.x != 0 || not_normalised.y != 0 || not_normalised.z != 0) {
						glm::vec3 normalised = glm::normalize(not_normalised);
						triangleNormals.push_back(normalised);
					}
				}
				if (haveEdge2 && haveEdge3) {
					not_normalised = glm::cross(edge2, edge3);
					if (not_normalised.x != 0 || not_normalised.y != 0 || not_normalised.z != 0) {
						glm::vec3 normalised = glm::normalize(not_normalised);
						triangleNormals.push_back(normalised);
					}
				}
				if (haveEdge3 && haveEdge4) {
					not_normalised = glm::cross(edge3, edge4);
					if (not_normalised.x != 0 || not_normalised.y != 0 || not_normalised.z != 0) {
						glm::vec3 normalised = glm::normalize(not_normalised);
						triangleNormals.push_back(normalised);
					}
				}
				glm::vec3 vertexNormal = glm::vec3(0, 0, 0);
				for (unsigned k = 0; k < triangleNormals.size(); k++) {
					vertexNormal = vertexNormal + triangleNormals[k];
				}
				if (vertexNormal != nullVector) {
					vertexNormal = glm::normalize(vertexNormal);
				}

				// this is nonsense
				vertexNormal = glm::vec3(0.0, 1.0, 0.0);
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

// move this to the base model class
std::vector<glm::vec3> GenericModel::getBoundingBox(std::vector<std::vector<glm::vec3>> vertexArrays) {
	std::vector<glm::vec3> boundingBox = std::vector<glm::vec3>();
	
	// actually we don't need a box, just 2 vectors representing the smallest and largest xyz corners of a box containing the model, for basic axis-aligned AABB collision / frustrum checks
	glm::vec3 minXYZ = vertexArrays[0][0];
	glm::vec3 maxXYZ = vertexArrays[0][0];

	for (unsigned i = 0; i < vertexArrays.size(); i++) {
		for (unsigned y = 0; y < vertexArrays[i].size(); y++) {
			if (vertexArrays[i][y].x < minXYZ.x) {
				minXYZ.x = vertexArrays[i][y].x;
			} else if (vertexArrays[i][y].x > maxXYZ.x) {
				maxXYZ.x = vertexArrays[i][y].x;
			}
			if (vertexArrays[i][y].y < minXYZ.y) {
				minXYZ.y = vertexArrays[i][y].y;
			}
			else if (vertexArrays[i][y].y > maxXYZ.y) {
				maxXYZ.y = vertexArrays[i][y].y;
			}
			if (vertexArrays[i][y].z < minXYZ.z) {
				minXYZ.z = vertexArrays[i][y].z;
			}
			else if (vertexArrays[i][y].z > maxXYZ.z) {
				maxXYZ.z = vertexArrays[i][y].z;
			}
		}
	}

	boundingBox.push_back(minXYZ);
	boundingBox.push_back(maxXYZ);

	return boundingBox;
}

GenericModel::GenericModel(std::vector<std::vector<glm::vec3>> vertexArrays, GLenum renderFormat)
{
	VertexArrays = vertexArrays;
	RenderFormat = renderFormat;
	boundingBox = getBoundingBox(vertexArrays);
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

void GenericModel::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{

 	glUseProgram(program);

	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, &modelMatrix[0][0]);



	for (int i = 0; i < Vaos.size(); i++) {
		glBindVertexArray(Vaos[i]);
		glDrawArrays(RenderFormat, 0, VertexArrays[i].size());
		//glDrawArrays(RenderFormat, 0, 100); - adds lines to origin when GL_TRIANGLE_STRIP - quite a nice effect :)
	}
}

