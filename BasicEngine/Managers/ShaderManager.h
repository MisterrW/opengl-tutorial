#pragma once
#include<map>
#include <fstream>
#include <vector>
#include <iostream>
#include "../../Dependencies/include/glew/glew.h"
#include "../../Dependencies/include/freeglut/freeglut.h"

// this is the header file for the shader loader class, 
// which loads shaders and creates shader programs
namespace BasicEngine
{
	namespace Managers
	{

		class ShaderManager
		{
		public:
			ShaderManager(void);
			~ShaderManager(void);

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
}