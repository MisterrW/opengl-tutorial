#pragma once

#include <BasicEngine\Models\Model.h>
#include<time.h>
#include<stdarg.h>

using namespace BasicEngine::Models;

namespace LocalModels {
	class MeshStrip : public Model
	{
	public:
		// MeshStrip(); 
		MeshStrip();
		~MeshStrip();

		void Create();
		virtual void Draw(const glm::mat4& projection_matrix,
			const glm::mat4& view_matrix)
			override final;
		virtual void Update() override final;

	private:
		int width;
		int height;
		float* vertices;
		int* indices;

		int getVerticesCount(int width, int height);
		int getIndicesCount(int width, int height);
		float* getVertices(int width, int height);
		int* getIndices(int width, int height);
	};
}