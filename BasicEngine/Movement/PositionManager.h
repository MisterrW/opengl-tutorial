#pragma once
#include "../../../Dependencies/include/glm/glm.hpp"

namespace BasicEngine {
	namespace Movement {
		class PositionManager {
		
		public:
			PositionManager();
			~PositionManager();
			glm::mat4 GetViewMatrix();
			void SetViewMatrix(glm::mat4 viewMatrix);
			void notifyKeyPress(char key, int x, int y);
			void notifyKeyUp(char key, int x, int y);

		private:
			glm::mat4 ViewMatrix;
		};
	}
}