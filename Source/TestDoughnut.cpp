#include "TestDoughnut.h"
#include "imgui.h"

namespace test
{
	TestDoughnut::TestDoughnut()
		: positions{
			-1.0f,	-1.0f,
			1.0f,	-1.0f,
			1.0f,	1.0f,
			-1.0f,	1.0f },

			indices{
			0,1,2,
			2,3,0 },

			center{ 300, 300 },
			radius(50),
			width(10),
			vb(positions, sizeof(positions)),
			ib(indices, 6),
			shader("Source/Resources/Shaders/Doughnut.shader")

	{
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		shader.Bind();
		shader.SetUniform2f("u_Center", center[0], center[1]);
		shader.SetUniform1f("u_Radius", radius);
		shader.SetUniform1f("u_InnerCircle", radius - width/2);
		shader.SetUniform1f("u_OuterCircle", radius + width/2);

		shader.Unbind();
		vb.Unbind();
		ib.Unbind();
	}

	TestDoughnut::~TestDoughnut()
	{

	}

	void TestDoughnut::OnUpdate(float deltaTime)
	{
		shader.Bind();
		shader.SetUniform2f("u_Center", center[0], center[1]);
		shader.SetUniform1f("u_Radius", radius);
		shader.SetUniform1f("u_InnerCircle", radius - width / 2);
		shader.SetUniform1f("u_OuterCircle", radius + width / 2);
	}

	void TestDoughnut::OnRender(Renderer renderer)
	{
		renderer.Draw(va, ib, shader);
	}

	void TestDoughnut::OnImGuiRender()
	{
		ImGui::SliderFloat2("Position", &center[0], 0, 960);
		ImGui::SliderFloat("Radius", &radius, 50.f, 400.f);
		ImGui::SliderFloat("Width", &width, 5.f, 2 * radius);
	}
}