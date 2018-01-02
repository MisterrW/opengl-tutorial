#pragma once
#include <BasicEngine\Makers\ModelMaker.h>
#include <vector>

namespace ModelMakers {
	class TreeMaker : public BasicEngine::Makers::ModelMaker {
	public:
		TreeMaker();
		~TreeMaker();

		std::vector<std::vector<glm::vec3>> GetTree(glm::vec3 root);

	private:
		float GetRandom();
		int BranchCount;
		std::vector<std::vector<glm::vec3>> GetBranch(std::vector<std::vector<glm::vec3>> tree, std::vector<glm::vec3> rootCoordinates, float radius, float maxLength, int branchingFactor, float spread, int maxBranchingFactor);
	};
}