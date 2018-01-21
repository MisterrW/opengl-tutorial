#pragma once
#include <vector>
#include "IGameObject.h"
#include "Triangle.h"
namespace BasicEngine
{
		namespace Models //create another namespace
		{
			class Model :public IGameObject
			{
			public:
				Model();
				Model(std::vector<std::vector<glm::vec3>> vertexArrays);
				
				virtual ~Model();
				// methods from interface
				virtual void Draw() override;
				virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
				virtual void Update() override;
				virtual void SetProgram(GLuint shaderName) override;
				virtual void Destroy() override;

				virtual GLuint GetVao() const override;
				std::vector<glm::vec3> getBoundingBox();
				std::vector<Triangle> getBoundingBoxTriangles();
				virtual const std::vector<GLuint>& GetVbos() const override;
				bool shouldCollisionCheck();
				void toggleCollisionCheck(bool shouldCheck);

			protected:
				std::vector<glm::vec3> setBoundingBox(std::vector<std::vector<glm::vec3>> vertexArrays);
				GLuint vao;
				GLuint program;
				std::vector<GLuint> vbos;
				std::vector<glm::vec3> boundingBox;
				std::vector<Triangle> boundingBoxTriangles;
				std::vector<Triangle> setBoundingBoxTriangles(std::vector<glm::vec3> boundingBoxMinMax);
				bool collisionCheck;
			};
		}
}