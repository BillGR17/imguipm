#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

static void glfw_error_callback(int error, const char *description) { fprintf(stderr, "GLFW Error %d: %s\n", error, description); }

int main(int, char **) {
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
    return 1;

  const char *glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  // Window properties
  glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  GLFWwindow *window = glfwCreateWindow(400, 50, "imguipm", nullptr, nullptr);
  if (window == nullptr)
    return 1;
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.IniFilename = NULL;

  ImFont *font = io.Fonts->AddFontFromFileTTF("/usr/share/fonts/noto/NotoSans-Bold.ttf", 20.0f);
  if (font) {
    io.FontDefault = font;
  }

  ImGui::StyleColorsDark();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

    ImGui::Begin("imguiPM", nullptr,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);

    const ImVec4 textColor = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
    ImGui::PushStyleColor(ImGuiCol_Text, textColor);

    float spacing = ImGui::GetStyle().ItemSpacing.x;
    float buttonWidth = (ImGui::GetContentRegionAvail().x - spacing * 3.0f) / 4.0f;
    float buttonHeight = ImGui::GetContentRegionAvail().y;

    // Logout Button (Yellow)
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.922f, 0.796f, 0.545f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.942f, 0.816f, 0.565f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.962f, 0.836f, 0.585f, 1.0f));
    if (ImGui::Button("Logout", ImVec2(buttonWidth, buttonHeight))) {
      system("loginctl terminate-user $(whoami)");
    }
    ImGui::PopStyleColor(3);

    ImGui::SameLine();

    // Shutdown Button (Red)
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.749f, 0.380f, 0.416f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.769f, 0.400f, 0.436f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.789f, 0.420f, 0.456f, 1.0f));
    if (ImGui::Button("Shutdown", ImVec2(buttonWidth, buttonHeight))) {
      system("shutdown now");
    }
    ImGui::PopStyleColor(3);

    ImGui::SameLine();

    // Restart Button (Cyan)
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.533f, 0.753f, 0.816f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.553f, 0.773f, 0.836f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.573f, 0.793f, 0.856f, 1.0f));
    if (ImGui::Button("Restart", ImVec2(buttonWidth, buttonHeight))) {
      system("reboot");
    }
    ImGui::PopStyleColor(3);

    ImGui::SameLine();

    // Close Button (Grey)
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.298f, 0.337f, 0.416f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.318f, 0.357f, 0.436f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.338f, 0.377f, 0.456f, 1.0f));
    if (ImGui::Button("Close", ImVec2(buttonWidth, buttonHeight))) {
      glfwSetWindowShouldClose(window, true);
    }
    ImGui::PopStyleColor(3);

    ImGui::End();

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
