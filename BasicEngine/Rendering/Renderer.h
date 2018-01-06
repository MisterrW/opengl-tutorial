/*
=================
The renderer handles the actual drawing of a model.
It maintains the projection and view matrices.
It determines whether or not a model should be drawn in this call.
=================
*/

#pragma once
#include "Models\Model.h"

using namespace BasicEngine::Rendering;
using namespace BasicEngine::Rendering::Models;

namespace BasicEngine
{
	namespace Rendering
	{
		class Renderer
		{
		public:
			Renderer();
			~Renderer();
			void setProjectionMatrix(glm::mat4 projection_matrix);
			void setViewMatrix(glm::mat4 view_matrix);
			void draw(Model* model);
		private:
			bool shouldDraw(const Model& model);
			//frustrum culler - owned class
			glm::mat4 viewMatrix;
			glm::mat4 projectionMatrix;
		};
	}
}