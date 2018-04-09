#pragma once
#include <vector>
#include "../Models/Triangle.h"
namespace BasicEngine
{
	namespace Emitters
	{
		class Emitter
		{
		public:
			void Emitter();
			void draw();

		private:
			std::vector<Models::Triangle> particles;
			glm::mat4 position;

		};
	}
}
/*
====
Emitters are used for all kinds of particle effects.
They create particles, determine their path, update and draw them each frame, and remove remove them when they're done.
====
*/
