#include "TestPyramid.h"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>

namespace test
{
	TestPyramid::TestPyramid()
		: positions{
			-0.5f,	-0.5f,	0.5f,
			0.5f,	-0.5f,	0.5f,
			0.5f,	-0.5f,	-0.5f,
			-0.5f,	-0.5f,	-0.5f,
			0.0f,	0.5f,	0.0f },

			indices{
			0,1,2,
			2,3,0,
			0,1,4,
			1,2,4,
			2,3,4,
			3,0,4 },

			vb(positions, sizeof(positions)),
			ib(indices, 18),
			angleY(0),
			angleX(0),
			angleZ(0),
			timer(0),
			timeDirection(1),
			shader("Source/Resources/Shaders/Pyramid.shader")

	{
		layout.Push<float>(3);
		va.AddBuffer(vb, layout);

		proj = glm::ortho(-1.0f, 1.0f, -1.f, 1.f, -1.0f, 1.0f);          
		view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		model = glm::mat4(1.0f);
		model = glm::rotate(model, angleX, glm::vec3(1, 0, 0));
		model = glm::rotate(model, angleY, glm::vec3(0, 1, 0));
		model = glm::rotate(model, angleZ, glm::vec3(0, 0, 1));
		mvp = proj * view * model;

		shader.Unbind();
		vb.Unbind();
		ib.Unbind();
	}

	TestPyramid::~TestPyramid()
	{

	}

	void TestPyramid::OnUpdate(float deltaTime)
	{
		if (timer > 1 || timer < 0)
		{
			timeDirection = -timeDirection;
		}

		timer += timeDirection * deltaTime;

		shader.Bind();
		model = glm::mat4(1.0f);
		model = glm::rotate(model, angleX, glm::vec3(1, 0, 0));
		model = glm::rotate(model, angleY, glm::vec3(0, 1, 0));
		model = glm::rotate(model, angleZ, glm::vec3(0, 0, 1));
		mvp = proj * view * model;
		shader.SetUniform4f("u_Color", timer, 0.0f, 0.0f, 1.0f);
		shader.SetUniformMat4f("u_MVP", mvp);
	}

	void TestPyramid::OnRender(Renderer renderer)
	{
		renderer.Draw(va, ib, shader);
	}

	void TestPyramid::OnImGuiRender()
	{
		ImGui::SliderFloat("AngleX", &angleX, 0.f, 2 * PI);
		ImGui::SliderFloat("AngleY", &angleY, 0.f, 2 * PI);
		ImGui::SliderFloat("AngleZ", &angleZ, 0.f, 2 * PI);
	}
}