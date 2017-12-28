#ifndef  VertexFormat_H_
#define VertexFormat_H_

#include "glm\glm.hpp" //installed with NuGet

struct VertexFormat
{
	glm::vec3 position;//our first vertex attribute
	glm::vec4 color;//our first vertex attribute

	VertexFormat(const glm::vec3 &pos, const glm::vec4 &col)
	{
		position = pos;
		color = col;
	}
};

#endif