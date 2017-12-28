#pragma once
#include<map>;
#include <fstream>;
#include <vector>;
#include <iostream>
#include "../Dependencies/glew/glew.h"
#include "../Dependencies/freeglut/freeglut.h"

// this is the header file for the shader loader class, 
// which loads shaders and creates shader programs
namespace Managers
{

	class Shader_Manager
	{
	public:
		Shader_Manager(void);
		~Shader_Manager(void);

		void CreateProgram(const std::string& ShaderName, 
			const std::string& VertexShaderFilename,
			const std::string& FragmentShaderFilename);
		static const GLuint GetProgram(const std::string&);
		void DeleteProgram(const std::string&);

	private:

		std::string ReadShader(const std::string& filename);
		GLuint CreateShader(GLenum shaderType,
			const std::string&  source,
			const std::string& shaderName);
		static std::map<std::string, GLuint> programs;

	};
}