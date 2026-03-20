#pragma once
#include "Test.h"
#include "FrameBuffer.h"
#include "Texture.h"

namespace test
{
	class TestShadow : public Test
	{
	private:
		//object
		float positions[24];
		unsigned int indices[6];
		glm::vec3 positionA;
		float angleA;
		glm::vec3 positionB;
		float angleB;
		glm::vec4 objectColorA;
		glm::vec4 objectColorB;

		//transform
		glm::vec3 cameraPos;
		glm::mat4 proj;
		glm::mat4 view;
		glm::mat4 model;
		glm::mat4 mvp;

		//light
		glm::vec3 lightPos;
		glm::vec3 lightDirection;
		glm::vec4 lightColor;
		glm::mat4 lightProjection;
		glm::mat4 lightView;
		glm::mat4 lightSpaceMatrix;
		

		VertexArray va;
		VertexBuffer vb;
		VertexBufferLayout layout;
		IndexBuffer ib;
		Texture texture;
		FrameBuffer fb;

		Shader shadowShader;
		Shader cameraShader;

	public:
		TestShadow();
		~TestShadow();

		void OnUpdate(float deltaTime) override;
		void OnRender(Renderer renderer) override;
		void OnImGuiRender() override;
	};
}