#pragma once

#ifdef _WIN32
	#include <windows.h>
#endif

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <gl_render.h>

#include "config.h"

#include "ui.h"

const char* gl_version = "#version 330";

void main_loop(
	GLFWwindow* window,
	const Renderer& render,
	UIHandle& ui
);

int windows() {
	// Initialize GLFW
	if (!glfwInit())
		return -1;

	// Create a windowed mode window and its OpenGL context
	GLFWwindow* window = glfwCreateWindow(
		Config::window_width, Config::window_height,
		"Hello World",
		NULL,
		NULL
	);
	
	if (!window) {
		glfwTerminate();
		return -1;
	}

	// We have this scope so we don't have to make everything pointers or new and then delete
	{
		/* Make the window's context current */
		glfwMakeContextCurrent(window);
		gladLoadGL(glfwGetProcAddress);
		// 0: uncaped
		// 1: 60fps cap
		glfwSwapInterval(0);

		// Make the window's context current
		glfwMakeContextCurrent(window);

		Renderer render;
		UIHandle ui;

		ui.setup(window, gl_version);

		main_loop(window, render, ui);
	}

	// Clean up
	glfwTerminate();

	return 0;
}

void main_loop(
	GLFWwindow* window,
	const Renderer& render,
	UIHandle& ui
) {
	Shader s_quad(
		"F:/cpp/school_engine/src/render/shader/vertex/v_quad.shader",
		"F:/cpp/school_engine/src/render/shader/fragment/f_quad.shader",
		""
	);

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {

		render.clear();
		render.clearColor();

		ui.newframe();

		{
			render.drawQuad(s_quad, GL_TRIANGLES);
			ui.content();
		}

		ui.render();

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	ui.shutdown();
}
