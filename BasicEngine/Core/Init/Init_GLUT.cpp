#include "Init_GLUT.h"

using namespace BasicEngine::Core::Init;

BasicEngine::Core::IListener* Init_GLUT::listener = NULL;
BasicEngine::Core::WindowInfo Init_GLUT::windowInformation;

void Init_GLUT::init(const BasicEngine::Core::WindowInfo& windowInfo,
	const BasicEngine::Core::ContextInfo& contextInfo,
	const BasicEngine::Core::FramebufferInfo& framebufferInfo)
{
	//we need to create these fake arguments
	int fakeargc = 1;
	char *fakeargv[] = { "fake", NULL };
	glutInit(&fakeargc, fakeargv);

	windowInformation = windowInfo;

	if (contextInfo.core)
	{
		glutInitContextVersion(contextInfo.major_version,
			contextInfo.minor_version);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
	{
		//As I said in part II, version doesn't matter
		// in Compatibility mode
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}

	//these functions were called in the old main.cpp
	//Now we use info from the structures
	glutInitDisplayMode(framebufferInfo.flags);
	glutInitWindowPosition(windowInfo.position_x,
		windowInfo.position_y);
	glutInitWindowSize(windowInfo.width, windowInfo.height);

	glutInitContextFlags(GLUT_DEBUG);
	glutCreateWindow(windowInfo.name.c_str());
	std::cout << "GLUT:initialized" << std::endl;

	glEnable(GL_DEBUG_OUTPUT);

	//init GLEW, this can be called in main.cpp
	Init::Init_GLEW::Init();

	glDebugMessageCallback(DebugOutput::myCallback, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
		GL_DONT_CARE, 0, NULL, GL_TRUE);

	//these callbacks are used for rendering
	glutIdleFunc(idleCallback);
	glutCloseFunc(closeCallback);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);

	//this callback gets keyboard information from glut

	glutKeyboardFunc(KeyPressCallback);
	glutKeyboardUpFunc(KeyUpCallback);

	//cleanup
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//our method to display some info. Needs contextInfo and windowinfo
	printOpenGLInfo(windowInfo, contextInfo);

}

//starts the rendering Loop
void Init_GLUT::Run()
{
	std::cout << "GLUT:\t Start Running " << std::endl;
	glutFullScreen();
	glutMainLoop();
}

void Init_GLUT::close()
{
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void Init_GLUT::idleCallback(void)
{
	//do nothing, just redisplay
	glutPostRedisplay();
}

void Init_GLUT::displayCallback()
{
	if (listener)
	{
		listener->notifyBeginFrame();
		listener->notifyDisplayFrame();

		glutSwapBuffers();

		listener->notifyEndFrame();
	}
}

void Init_GLUT::reshapeCallback(int width, int height)
{
	if (windowInformation.isReshapable == true)
	{
		if (listener)
		{
			listener->notifyReshape(width,
				height,
				windowInformation.width,
				windowInformation.height);
		}
		windowInformation.width = width;
		windowInformation.height = height;
	}
}

void Init_GLUT::KeyPressCallback(unsigned char key, int x, int y) {
	listener->notifyKeyPress(key, x, y);
}

void Init_GLUT::KeyUpCallback(unsigned char key, int x, int y) {
	listener->notifyKeyUp(key, x, y);
}

void Init_GLUT::SetListener(BasicEngine::Core::IListener* iListener)
{
	listener = iListener;
}

void Init_GLUT::closeCallback()
{
	close();
}

void Init_GLUT::enterFullscreen()
{
	glutFullScreen();
}

void Init_GLUT::exitFullscreen()
{
	glutLeaveFullScreen();
}

void Init_GLUT::printOpenGLInfo(const BasicEngine::Core::WindowInfo& windowInfo,
	const BasicEngine::Core::ContextInfo& contextInfo) {

	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "******************************************************               ************************" << std::endl;
	std::cout << "GLUT:Initialise" << std::endl;
	std::cout << "GLUT:\tVendor : " << vendor << std::endl;
	std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
	std::cout << "GLUT:\tOpenGl version: " << version << std::endl;
}