#pragma once

namespace BasicEngine
{
	namespace Core {

		class IListener
		{
		public:
			virtual ~IListener() = 0;

			//drawing functions
			virtual void notifyBeginFrame() = 0;
			virtual void notifyDisplayFrame() = 0;
			virtual void notifyEndFrame() = 0;
			virtual void notifyReshape(int width,
				int height,
				int previous_width,
				int previous_height) = 0;
			virtual void notifyKeyPress(char key, int x, int y) = 0;
			virtual void notifyKeyUp(char key, int x, int y) = 0;

		};

		inline IListener::~IListener() {
			//implementation of pure virtual destructor
		}
	}
}