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

			void UpdateViewMatrix();

		private:
			glm::mat4 ViewMatrix;
			bool* KeyStates;
			bool* OldKeyStates;
			
			glm::mat4 GetMoveMatrix();
			glm::mat4 GetOrientationMatrix();
			glm::mat4 GetXYZRotMat(float x, float y, float z);

		};
	}
}