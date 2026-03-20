#include "TestLight.h"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>

namespace test
{
	TestLight::TestLight()
		: positions{
			-0.5f,	-0.5f,  0.0f,  0.0f, 0.0f, -1.0f,
			 0.5f,	-0.5f,  0.0f,  0.0f, 0.0f, -1.0f,
			 0.5f,	 0.5f,  0.0f,  0.0f, 0.0f, -1.0f,
			-0.5f,	 0.5f,  0.0f,  0.0f, 0.0f, -1.0f },

			indices{
			0,1,2,
			2,3,0 },

			angle(0),
			vb(positions, sizeof(positions)),
			ib(indices, 6),
			objectColor(1.0f, 0.0f, 0.0f, 1.0f),
			cameraPos(0.0f, 0.0f, -1.0f),
			lightPos(0.0f, 0.0f, -0.2f),
			lightColor(1.0f, 1.0f, 1.0f, 1.0f),
			shader("Source/Resources/Shaders/Light.shader")

	{
		layout.Push<float>(3); //positions
		layout.Push<float>(3); //normals
		va.AddBuffer(vb, layout);

		//start transform
		proj = glm::ortho(-1.0f, 1.0f, -1.f, 1.f, -1.0f, 1.0f);
		view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		model = glm::mat4(1.0f);
		model = glm::rotate(model, angle, glm::vec3(0, 1, 0));
		mvp = proj * view * model;

		shader.Bind();
		shader.SetUniformMat4f("u_MVP", mvp);
		shader.SetUniformMat4f("u_Model", model);
		shader.SetUniform4f("u_ObjectColor", objectColor);
		shader.SetUniform3f("u_CameraPos", cameraPos);
		shader.SetUniform3f("u_LightPos", lightPos);
		shader.SetUniform4f("u_LightColor", lightColor);
		shader.Unbind();

		vb.Unbind();
		ib.Unbind();
	}

	TestLight::~TestLight()
	{

	}

	void TestLight::OnUpdate(float deltaTime)
	{
		model = glm::mat4(1.0f);
		model = glm::rotate(model, angle, glm::vec3(0, 1, 0));
		mvp = proj * view * model;

		shader.Bind();
		shader.SetUniformMat4f("u_MVP", mvp);
		shader.SetUniformMat4f("u_Model", model);
		shader.SetUniform3f("u_LightPos", lightPos);
	}

	void TestLight::OnRender(Renderer renderer)
	{
		renderer.Draw(va, ib, shader);
	}

	void TestLight::OnImGuiRender()
	{
		ImGui::SliderFloat3("Light Position", &lightPos.x, -1.f, 1.f);
		ImGui::SliderFloat("Angle", &angle, 0, 2 * PI);
	}
}