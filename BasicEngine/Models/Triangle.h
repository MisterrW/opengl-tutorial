#pragma once
#include <vector>
#include "../../../Dependencies/include/glm/glm.hpp"

namespace BasicEngine
{
	namespace Models //create another namespace
	{
		class Triangle
		{
		public:
			Triangle(std::vector<glm::vec3> vertices);
			Triangle(std::vector<glm::vec3> vertices, glm::vec3 normal);
			Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
			Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 normal);
			std::vector<glm::vec3> getVertices();
			glm::vec3 getV0();
			glm::vec3 getV1();
			glm::vec3 getV2();
			glm::vec3 getNormal();

		private:
			void setNormal(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
		    glm::vec3 normal;
			glm::vec3 v0;
			glm::vec3 v1;
			glm::vec3 v2;

		};
	}
}