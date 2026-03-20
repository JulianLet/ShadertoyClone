#pragma once
#include "Test.h"

namespace test
{
	class TestLight : public Test
	{
	private:
		//object
		float positions[24];
		unsigned int indices[6];
		float angle;
		glm::vec4 objectColor;

		//transform
		glm::vec3 cameraPos;
		glm::mat4 proj;
		glm::mat4 view;
		glm::mat4 model;
		glm::mat4 mvp;

		//light
		glm::vec3 lightPos;
		glm::vec4 lightColor;
		

		VertexArray va;
		VertexBuffer vb;
		VertexBufferLayout layout;
		IndexBuffer ib;

		Shader shader;

	public:
		TestLight();
		~TestLight();

		void OnUpdate(float deltaTime) override;
		void OnRender(Renderer renderer) override;
		void OnImGuiRender() override;
	};
}