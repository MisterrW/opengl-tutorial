//Init_GLUT.h
#pragma once
#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "WindowInfo.h"
#include <iostream>
#include "Init_GLEW.h"
#include "../../Managers/SceneManager.h"
#include "DebugOutput.h"

namespace BasicEngine
{
	namespace Core {
		namespace Init { //two namespaces

			class Init_GLUT {

			private:
				static BasicEngine::Managers::SceneManager* listener;
				static Core::WindowInfo windowInformation;

			public:
				static void init(
					const Core::WindowInfo& window,
					const Core::ContextInfo& context,
					const Core::FramebufferInfo& framebufferInfo);

				static void Run();
				static void close();

				void enterFullscreen();
				void exitFullscreen();

				//used to print info about GL
				static void printOpenGLInfo(
					const Core::WindowInfo& windowInfo,
					const Core::ContextInfo& context);

				static void SetListener(BasicEngine::Managers::SceneManager* aListener);

			private:
				static void idleCallback(void);
				static void displayCallback(void);
				static void reshapeCallback(int width, int height);
				static void KeyPressCallback(unsigned char key, int x, int y);
				static void KeyUpCallback(unsigned char key, int x, int y);
				static void closeCallback();
			};
		}
	}
}