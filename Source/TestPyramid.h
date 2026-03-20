#pragma once
#include "Test.h"

namespace test
{
	class TestPyramid : public Test
	{
	private:
		float positions[15];
		unsigned int indices[18];
		float angleY;
		float angleX;
		float angleZ;
		float timer;
		int timeDirection;

		glm::mat4 proj;
		glm::mat4 view;
		glm::mat4 model;
		glm::mat4 mvp;

		VertexArray va;
		VertexBuffer vb;
		VertexBufferLayout layout;
		IndexBuffer ib;

		Shader shader;

	public:
		TestPyramid();
		~TestPyramid();

		void OnUpdate(float deltaTime) override;
		void OnRender(Renderer renderer) override;
		void OnImGuiRender() override;
	};
}