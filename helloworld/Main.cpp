#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "Core/GameModels.h";
#include "Managers/Shader_Manager.h";

Managers::Shader_Manager* shaderManager;

// using namespace Core;

Models::GameModels* gameModels;
GLuint program;

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.3, 0.3, 1.0);

	glBindVertexArray(gameModels->GetModel("triangle1"));
	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(gameModels->GetModel("triangle2"));
	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(gameModels->GetModel("triangle3"));
	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

void closeCallback() {

	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void Init() {

	glEnable(GL_DEPTH_TEST);

	gameModels = new Models::GameModels();
	gameModels->CreateTriangleModel("triangle1");
	gameModels->CreateTriangleModel("triangle2");
	gameModels->CreateTriangleModel("triangle3");

	// load and compile shaders
	shaderManager = new Managers::Shader_Manager();
	shaderManager->CreateProgram("myProgram",
	"Shaders\\Vertex_Shader.glsl",
	"Shaders\\Fragment_Shader.glsl"
	);
	program = shaderManager->GetProgram("myProgram");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("My First Triangle");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_3")) {
		std::cout << " GLEW Version is 3.3\n ";
	}
	else {
		std::cout << "GLEW 3.3 not supported\n ";
	}

	Init();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutCloseFunc(closeCallback);
	glutMainLoop();

	delete gameModels;
	delete shaderManager;
	glDeleteProgram(program);

	return 0;
}