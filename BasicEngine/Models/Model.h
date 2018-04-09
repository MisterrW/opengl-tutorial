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
			Model(std::vector<std::vector<glm::vec3>> vertexArrays, bool canMove);

			virtual ~Model();
			// methods from interface
			virtual void Draw() override;
			virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override;
			virtual void Update() override;
			virtual void SetProgram(GLuint shaderName) override;
			virtual void Destroy() override;

			virtual GLuint GetVao() const override;
			std::vector<glm::vec3> getBoundingBoxModelSpace();
			std::vector<glm::vec3> getBoundingBoxWorldSpace();
			std::vector<Triangle> getBoundingBoxTriangles();
			virtual const std::vector<GLuint>& GetVbos() const override;
			bool shouldCollisionCheck();
			void toggleCollisionCheck(bool shouldCheck);

			bool canMove;
			void makeMoveable();
			glm::mat4 getThisFrameMoveMatrix();
			glm::mat4 getPositionMatrix();
			void setPositionMatrix(glm::mat4 positionMatrix);
			void setInitialPositionMatrix(glm::mat4 positionMatrix);
			void setEachFrameMoveMatrix(glm::mat4 moveMatrix);

		protected:

			void initialise(std::vector<std::vector<glm::vec3>> vertexArrays);
			std::vector<glm::vec3> setBoundingBox(std::vector<std::vector<glm::vec3>> vertexArrays);
			GLuint vao;
			GLuint program;
			std::vector<GLuint> vbos;
			std::vector<glm::vec3> boundingBox;
			std::vector<Triangle> boundingBoxTriangles;
			std::vector<Triangle> setBoundingBoxTriangles(std::vector<glm::vec3> boundingBoxMinMax);
			bool collisionCheck;
			glm::mat4 eachFrameMoveMatrix;
			glm::mat4 positionMatrix;
		};
	}
}