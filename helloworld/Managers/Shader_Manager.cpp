#include "Shader_Manager.h" 
#include<iostream>
#include<fstream>
#include<vector>
#include<map>

using namespace Managers;

// this is the Shader_Manager class file. It contains functions related to reading shaders from files,
// and creating programs from those shaders.

std::map<std::string, GLuint> Shader_Manager::programs;

// ctor and dtor
Shader_Manager::Shader_Manager(void) {}
Shader_Manager::~Shader_Manager(void) {
	std::map<std::string, GLuint>::iterator i;
	for (i = programs.begin(); i != programs.end(); ++i)
	{
		GLuint pr = i->second;
		glDeleteProgram(pr);
	}
	programs.clear();
}

std::string Shader_Manager::ReadShader(const std::string& filename)
{

	std::string shaderCode;
	std::ifstream file(filename, std::ios::in);

	if (!file.good())
	{
		std::cout << "Can't read file " << filename.c_str() << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint Shader_Manager::CreateShader(GLenum shaderType, const std::string&
	source, const std::string& shaderName)
{

	int compile_result = 0;
    
	// glCreateShader creates an empty shader of the specified type
	GLuint shader = glCreateShader(shaderType);

	// gets a pointer to a c string (kind of a char array) representing the source code string
	const char *shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();

	// glShaderSource replaces the source code in a shader object,
	// with the contents of an array of strings containing the new source code
	// params:
	//   shader to replace contents of
	//   the number of strings in the provided array (ie the length of the arrays which are the 3rd and 4th params, normally 1)
	//   an array of pointers to strings containing shader code
	//   an array of GLints representing the length of each string in the strings array (normally left at NULL, so the function just reads each string to completion)
	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	
	// this checks for errors in the shader and outputs them to the console
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	//check for errors
	if (compile_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "ERROR compiling shader: " << shaderName.c_str() << std::endl << &shader_log[0] << std::endl;
		return 0;
	}
	return shader;
}

void Shader_Manager::CreateProgram(const std::string& ShaderName,
	const std::string& vertexShaderFilename,
	const std::string& fragmentShaderFilename)
{

	//read the shader files and save the code
	std::string vertex_shader_code = ReadShader(vertexShaderFilename);
	std::string fragment_shader_code = ReadShader(fragmentShaderFilename);

	GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
	GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

	int link_result = 0;
	//create the program handle, attatch the shaders and link it
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	//check for link errors
	if (link_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
		return;
	}
	programs[ShaderName] = program;
}

const GLuint Shader_Manager::GetProgram(const std::string& programName) {
	return programs.at(programName);
}

void Shader_Manager::DeleteProgram(const std::string& programName) {
	GLuint pr = programs.at(programName);
	glDeleteProgram(pr);
	programs.erase(programName);
}