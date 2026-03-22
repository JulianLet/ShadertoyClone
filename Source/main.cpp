#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Common.h"
#include "Test.h"
#include "TestDoughnut.h"
#include "TestPyramid.h"
#include "TestLight.h"
#include "TestShadow.h"
#include "TestAnimating.h"
#include "TestHeart.h"
#include "TestGrayScale.h"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow( 750, 750, "ShaderProgramming", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    ///* Set the framerate of primary monitor */
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
    int frameRate = videoMode->refreshRate; //get refreshRate of monitor


    int swapInterval = 1;
    if (swapInterval < 1)
    {
        swapInterval = 1; // Minimum allowed value
    }

    const float deltaTime = (float)swapInterval / frameRate;
    glfwSwapInterval(swapInterval);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
    }

    float clearBlack[4] = { 0.0f, 0.0f, 0.0f, 1.0f };


    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        //Init of everything
        GLCall(glEnable(GL_BLEND));     
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        
        Renderer renderer;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();

        //setup of the tests
        test::Test* currentTest = nullptr;
        test::TestMenu* menu = new test::TestMenu(currentTest);
        currentTest = menu;

        menu->RegisterTest<test::TestDoughnut>("Doughnut");
        menu->RegisterTest<test::TestPyramid>("Pyramid");
        menu->RegisterTest<test::TestLight>("Light");
        menu->RegisterTest<test::TestShadow>("Shadow");
        menu->RegisterTest<test::TestAnimating>("Animating");
        menu->RegisterTest<test::TestHeart>("Heart");
        menu->RegisterTest<test::TestGrayScale>("GrayScale");

        while (!glfwWindowShouldClose(window))
        {
            //regular rendering
            renderer.Clear(clearBlack);

            //imGui rendering stuff
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (currentTest)
            {
                currentTest->OnUpdate(deltaTime);
                currentTest->OnRender(renderer);
                ImGui::Begin("Test");

                if (currentTest != menu && ImGui::Button("<-")) //this button function creates the button and checks if it is pressed
                {
                    delete currentTest;
                    currentTest = menu;
                }

                currentTest->OnImGuiRender();
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        if (currentTest != menu)
        {
            delete menu;
        }

        delete currentTest;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}