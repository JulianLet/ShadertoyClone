#include "TestGrayScale.h"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>

namespace test
{
	TestGrayScale::TestGrayScale()
		: positions{
			-1.f,	-1.f,
			1.f,	-1.f,
			1.f,	1.f,
			-1.f,	1.f},

			indices{
			0,1,2,
			2,3,0},

			vb(positions, sizeof(positions)),
			ib(indices, 18),
			timer(0),
			timeDirection(1),
			grayScale(0.5f),
			color(0.3f, 0.5f, 0.0f, 1.0f),
			shader("Source/Resources/Shaders/GrayScale.shader")

	{
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		shader.Bind();
		shader.SetUniform1f("u_GrayScale", grayScale);
		shader.Unbind();

		vb.Unbind();
		ib.Unbind();
	}

	TestGrayScale::~TestGrayScale()
	{

	}

	void TestGrayScale::OnUpdate(float deltaTime)
	{
		timer += deltaTime;

		shader.Bind();
		shader.SetUniform1f("u_GrayScale", grayScale);
		shader.Unbind();
	}

	void TestGrayScale::OnRender(Renderer renderer)
	{
		renderer.Draw(va, ib, shader);
	}

	void TestGrayScale::OnImGuiRender()
	{		
		ImGui::SliderFloat("Gray Scale", &grayScale, 0.f, 1.f);
		ImGui::ColorPicker4("Color", &color.x);
	}
}