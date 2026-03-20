#pragma once
#include "Test.h"
#include "Texture.h"

namespace test
{
	class TestGrayScale : public Test
	{
	private:
		float positions[8];
		unsigned int indices[6];

		float timer;
		int timeDirection;

		float grayScale;
		glm::vec4 color;

		VertexArray va;
		VertexBuffer vb;
		VertexBufferLayout layout;
		IndexBuffer ib;

		Shader shader;

	public:
		TestGrayScale();
		~TestGrayScale();

		void OnUpdate(float deltaTime) override;
		void OnRender(Renderer renderer) override;
		void OnImGuiRender() override;
	};
}