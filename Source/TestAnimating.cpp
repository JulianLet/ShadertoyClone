#include "TestAnimating.h"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>

namespace test
{
	TestAnimating::TestAnimating()
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
			shader("Source/Resources/Shaders/Animating.shader")

	{
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		shader.Bind();
		shader.SetUniform4f("u_Color", 0.3f, 0.5f, 0.0f, 1.0f);
		shader.Unbind();

		vb.Unbind();
		ib.Unbind();
	}

	TestAnimating::~TestAnimating()
	{

	}

	void TestAnimating::OnUpdate(float deltaTime)
	{
		timer += deltaTime;

		shader.Bind();
		shader.SetUniform1f("u_Timer", timer);
		shader.Unbind();
	}

	void TestAnimating::OnRender(Renderer renderer)
	{
		renderer.Draw(va, ib, shader);
	}

	void TestAnimating::OnImGuiRender()
	{

	}
}