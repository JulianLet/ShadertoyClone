#pragma once
#include "Test.h"

namespace test
{
	class TestAnimating : public Test
	{
	private:
		float positions[8];
		unsigned int indices[6];

		float timer;
		int timeDirection;

		VertexArray va;
		VertexBuffer vb;
		VertexBufferLayout layout;
		IndexBuffer ib;

		Shader shader;

	public:
		TestAnimating();
		~TestAnimating();

		void OnUpdate(float deltaTime) override;
		void OnRender(Renderer renderer) override;
		void OnImGuiRender() override;
	};
}