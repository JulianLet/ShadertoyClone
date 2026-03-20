#pragma once
#include "Test.h"

namespace test
{
	class TestDoughnut : public Test
	{
	private:
		float positions[8];
		unsigned int indices[6];
		float center[2];
		float radius;
		float width;

		VertexArray va;
		VertexBuffer vb;
		VertexBufferLayout layout;
		IndexBuffer ib;

		Shader shader;

	public:
		TestDoughnut();
		~TestDoughnut();

		void OnUpdate(float deltaTime) override;
		void OnRender(Renderer renderer) override;
		void OnImGuiRender() override;
	};
}