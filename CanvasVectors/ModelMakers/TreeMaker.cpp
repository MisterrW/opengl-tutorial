#include "TreeMaker.h"

ModelMakers::TreeMaker::TreeMaker() {
	BranchCount = 0;
}

ModelMakers::TreeMaker::~TreeMaker() {

}

float ModelMakers::TreeMaker::GetRandom() {
	return (std::rand() % 10) / 10.0;
}

std::vector<std::vector<glm::vec3>> ModelMakers::TreeMaker::GetBranch(std::vector<std::vector<glm::vec3>> tree, std::vector<glm::vec3> rootCoordinates, float radius, float maxLength, int branchingFactor, float spread, int maxBranchingFactor) {
	if (BranchCount < 100) {
		//   branchCount++
		// console.log(branchCount)
		glm::vec3 branchEnd = glm::vec3(
			rootCoordinates[0][0] + (-spread + (GetRandom() * 2 * spread)),
			rootCoordinates[0][1] + ((0.5 * maxLength) + (GetRandom() * 0.5 * maxLength)),
			rootCoordinates[0][2] + (-spread + (GetRandom() * 2 * spread))
		);
		float tipRadius = radius * 0.5;
		std::vector<glm::vec3> tipCoordinates = std::vector<glm::vec3>();
			
		tipCoordinates.push_back(branchEnd);
		tipCoordinates.push_back(glm::vec3(branchEnd[0] + tipRadius, branchEnd[1], branchEnd[2]));
		tipCoordinates.push_back(glm::vec3(branchEnd[0], branchEnd[1], branchEnd[2] + tipRadius));

		std::vector<glm::vec3> branch = std::vector<glm::vec3>();

		branch.reserve(rootCoordinates.size() + tipCoordinates.size()); // preallocate memory
		branch.insert(branch.end(), rootCoordinates.begin(), rootCoordinates.end());
		branch.insert(branch.end(), tipCoordinates.begin(), tipCoordinates.end());

		tree.push_back(branch);

			if (branchingFactor < maxBranchingFactor && tree.size() < 200) {
				for (int i = 0; i < branchingFactor; i++) {
					tree = GetBranch(tree, tipCoordinates, tipRadius, maxLength * 0.7, branchingFactor + 2, spread * 1.2, maxBranchingFactor);
				}
			}
	}
	return tree;
}



std::vector<std::vector<glm::vec3>> ModelMakers::TreeMaker::GetTree(glm::vec3 root) {
	BranchCount = 0;
	float radius = 3;
	std::vector<glm::vec3> rootCoordinates = std::vector<glm::vec3>();
	rootCoordinates.push_back(root);
	rootCoordinates.push_back(glm::vec3(root[0] + radius, root[1], root[2]));
	rootCoordinates.push_back(glm::vec3(root[0], root[1], root[2] + radius));

	std::vector<std::vector<glm::vec3>> tree = std::vector<std::vector<glm::vec3>>();
	float trunkLength = 30 + (GetRandom() * 3);
	float spread = (trunkLength / 5) + GetRandom() * (trunkLength / 40);
	int branchingFactor = 1 + std::round(GetRandom() * 7);
	int maxBranchingFactor = 10;

	return GetBranch(tree, rootCoordinates, radius, trunkLength, branchingFactor, spread, maxBranchingFactor);
};
