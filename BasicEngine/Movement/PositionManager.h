/*
=====
The position manager calculates movement based on player input.
It returns to the movementManager matrices used to modify the old position and rotation matrices.
=====
*/

#pragma once
#include "../../../Dependencies/include/glm/glm.hpp"

namespace BasicEngine {
	namespace Movement {
		class PositionManager {

		public:
			PositionManager();
			~PositionManager();
			//glm::mat4 GetViewMatrix(glm::mat4 oldViewMatrix);
			void notifyKeyPress(char key, int x, int y);
			void notifyKeyUp(char key, int x, int y);
			glm::mat4 GetMoveMatrix();
			glm::mat4 GetOrientationMatrix();

		private:
			bool* KeyStates;
			bool* OldKeyStates;

			
			glm::mat4 GetXYZRotMat(float x, float y, float z);
			float lookScaleFactor;
			float moveScaleFactor;
		};
	}
}