#include "TestHeart.h"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>

namespace test
{
	TestHeart::TestHeart()
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
			shader("Source/Resources/Shaders/Heart.shader")

	{
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		shader.Bind();
		shader.Unbind();

		vb.Unbind();
		ib.Unbind();
	}

	TestHeart::~TestHeart()
	{

	}

	void TestHeart::OnUpdate(float deltaTime)
	{
		timer += deltaTime;

		shader.Bind();
		shader.SetUniform1f("u_Timer", timer);
		shader.Unbind();
	}

	void TestHeart::OnRender(Renderer renderer)
	{
		renderer.Draw(va, ib, shader);
	}

	void TestHeart::OnImGuiRender()
	{

	}
}