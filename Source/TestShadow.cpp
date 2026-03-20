#include "TestShadow.h"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>

namespace test
{
	TestShadow::TestShadow()
		: positions{
			-0.5f,	-0.5f,  0.0f,  0.0f, 0.0f, -1.0f,
			 0.5f,	-0.5f,  0.0f,  0.0f, 0.0f, -1.0f,
			 0.5f,	 0.5f,  0.0f,  0.0f, 0.0f, -1.0f,
			-0.5f,	 0.5f,  0.0f,  0.0f, 0.0f, -1.0f },

			indices{
			0,1,2,
			2,3,0 },

			positionA(-0.5f, 0.f, 0.f),
			angleA(0),
			positionB(0.5f, 0.f, 0.f),
			angleB(0),
			vb(positions, sizeof(positions)),
			ib(indices, 6),
			texture(),
			fb(texture.GetID()),
			objectColorA(1.0f, 0.0f, 0.0f, 1.0f),
			objectColorB(0.0f, 0.0f, 1.0f, 1.0f),
			cameraPos(0.0f, 0.0f, -5.0f),
			lightPos(0.0f, 0.0f, -3.f),
			lightDirection(-0.3f, 0.0f, 1.0f),
			lightColor(1.0f, 1.0f, 1.0f, 1.0f),
			shadowShader("Source/Resources/Shaders/ShadowMap.shader"),
			cameraShader("Source/Resources/Shaders/Shadow.shader")

	{
		GLCall(glEnable(GL_DEPTH_TEST));  // Enable depth testing
		glDepthFunc(GL_LESS);     // Use GL_LESS depth function

		layout.Push<float>(3); //positions
		layout.Push<float>(3); //normals
		va.AddBuffer(vb, layout);

		//light transform
		lightProjection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 0.f, 100.0f);
		lightView = glm::lookAt(lightPos, lightPos + glm::normalize(lightDirection), glm::vec3(0.f, 1.f, 0.f));

		//start transform
		proj = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 0.f, 100.f);
		//view = glm::lookAt(cameraPos, glm::vec3(0.f,0.f,0.f), glm::vec3(0.f, 1.f, 0.f));
		view = lightView;

		//set up camera shader
		cameraShader.Bind();
		cameraShader.SetUniform3f("u_CameraPos", cameraPos);
		cameraShader.SetUniform4f("u_LightColor", lightColor);
		cameraShader.Unbind();

		vb.Unbind();
		ib.Unbind();
	}

	TestShadow::~TestShadow()
	{
		GLCall(glDisable(GL_DEPTH_TEST));  // Enable depth testing
		glDepthFunc(GL_LESS);     // Use GL_LESS depth function
	}

	void TestShadow::OnUpdate(float deltaTime)
	{

	}

	void TestShadow::OnRender(Renderer renderer)
	{
		float clearWhite[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		renderer.Clear(clearWhite);

		//draw from light perspective
		lightView = glm::lookAt(lightPos, lightPos + glm::normalize(lightDirection), glm::vec3(0.0f, 1.0f, 0.0f));
		lightSpaceMatrix = lightProjection * lightView;


		fb.Bind();
		shadowShader.Bind();

		model = glm::translate(glm::mat4(1.0f), -positionA);
		model = glm::rotate(model, angleA, glm::vec3(0, 1, 0));
		mvp = lightSpaceMatrix * model;
		shadowShader.SetUniformMat4f("u_MVP", mvp);
		renderer.Draw(va, ib, shadowShader);

		model = glm::translate(glm::mat4(1.0f), -positionB);
		model = glm::rotate(model, angleB, glm::vec3(0, 1, 0));
		mvp = lightSpaceMatrix * model;
		shadowShader.SetUniformMat4f("u_MVP", mvp);
		renderer.Draw(va, ib, shadowShader);

		fb.Unbind();


		//draw from camera perpective
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		cameraShader.Bind();
		cameraShader.SetUniformMat4f("u_LightMatrix", lightSpaceMatrix);
		cameraShader.SetUniform3f("u_LightDirection", glm::normalize(lightDirection));

		texture.Bind();
		cameraShader.SetUniform1i("u_DepthMap", 0);

		model = glm::translate(glm::mat4(1.0f), -positionA);
		model = glm::rotate(model, angleA, glm::vec3(0, 1, 0));
		mvp = proj * view * model;
		cameraShader.SetUniformMat4f("u_MVP", mvp);
		cameraShader.SetUniformMat4f("u_Model", model);
		cameraShader.SetUniform4f("u_ObjectColor", objectColorA);
		renderer.Draw(va, ib, cameraShader);

		model = glm::translate(glm::mat4(1.0f), -positionB);
		model = glm::rotate(model, angleB, glm::vec3(0, 1, 0));
		mvp = proj * view * model;
		cameraShader.SetUniformMat4f("u_MVP", mvp);
		cameraShader.SetUniformMat4f("u_Model", model);
		cameraShader.SetUniform4f("u_ObjectColor", objectColorB);
		renderer.Draw(va, ib, cameraShader);
	}

	void TestShadow::OnImGuiRender()
	{
		ImGui::SliderFloat3("Light Direction", &lightDirection.x, -5.f, 5.f);
		ImGui::SliderFloat3("PositionA", &positionA.x, -1.f, 1.f);
		ImGui::SliderFloat("AngleA", &angleA, -PI, PI);
		ImGui::SliderFloat3("PositionB", &positionB.x, -1.f, 1.f);
		ImGui::SliderFloat("AngleB", &angleB, -PI, PI);
	}
}