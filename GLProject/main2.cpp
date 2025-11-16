// GLProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_m.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Polygon.cpp"

using namespace glm;

int width = 800;
int height = 600;

vec3 cameraPos = vec3(0.0f, 0.0f, 4.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

void processInput(GLFWwindow* window);

int main()
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(width, height, "Lecture 3", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glEnable(GL_DEPTH_TEST);

	Shader ourShader("./shaders/vs/L3.vs", "./shaders/fs/L3.fs");

	std::vector<vec3> rodFront = {
	vec3(-0.05f,  0.5f,  0.05f),
	vec3(0.05f,  0.5f,  0.05f),
	vec3(0.05f, -0.5f,  0.05f),
	vec3(-0.05f, -0.5f,  0.05f)
	};
	Polygon rodF = Polygon(rodFront, vec3(0.9f, 0.9f, 0.2f));

	std::vector<vec3> rodBack = {
		vec3(-0.05f,  0.5f, -0.05f),
		vec3(0.05f,  0.5f, -0.05f),
		vec3(0.05f, -0.5f, -0.05f),
		vec3(-0.05f, -0.5f, -0.05f)
	};
	Polygon rodB = Polygon(rodBack, vec3(0.8f, 0.8f, 0.15f));

	std::vector<vec3> rodLeft = {
		vec3(-0.05f,  0.5f, -0.05f),
		vec3(-0.05f,  0.5f,  0.05f),
		vec3(-0.05f, -0.5f,  0.05f),
		vec3(-0.05f, -0.5f, -0.05f)
	};
	Polygon rodL = Polygon(rodLeft, vec3(0.85f, 0.85f, 0.18f));

	std::vector<vec3> rodRight = {
		vec3(0.05f,  0.5f, -0.05f),
		vec3(0.05f,  0.5f,  0.05f),
		vec3(0.05f, -0.5f,  0.05f),
		vec3(0.05f, -0.5f, -0.05f)
	};
	Polygon rodR = Polygon(rodRight, vec3(0.85f, 0.85f, 0.18f));

	std::vector<vec3> rodTop = {
		vec3(-0.05f, 0.5f, -0.05f),
		vec3(0.05f, 0.5f, -0.05f),
		vec3(0.05f, 0.5f,  0.05f),
		vec3(-0.05f, 0.5f,  0.05f),
	};
	Polygon rodT = Polygon(rodTop, vec3(0.95f, 0.95f, 0.25f));

	std::vector<vec3> rodBottom = {
		vec3(-0.05f, -0.5f, -0.05f),
		vec3(0.05f, -0.5f, -0.05f),
		vec3(0.05f, -0.5f,  0.05f),
		vec3(-0.05f, -0.5f,  0.05f),
	};
	Polygon rodD = Polygon(rodBottom, vec3(0.95f, 0.95f, 0.25f));

	std::vector<vec3> circle;
	int segments = 30;
	float radius = 0.12f;

	for (int i = 0; i < segments; i++) {
		float a = (float)i / segments * 2.0f * 3.14159f;
		circle.push_back(vec3(cos(a) * radius, -0.65f, sin(a) * radius));
	}
	Polygon circlePoly = Polygon(circle, vec3(1.0f, 0.8f, 0.3f));

	ourShader.use();

	mat4 projection = mat4(1.0f);
	projection = perspective(radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	//projection = ortho(-(float)width, (float)width, -(float)height, (float)height, 0.01f, 100.0f);;
	ourShader.setMat4("projection", projection);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mat4 view = mat4(1.0f);
		//view = translate(view, vec3(0.0f, 0.0f, -4.0f));
		view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		ourShader.setMat4("view", view);

		// Pendulum movement
		float angle = sin(glfwGetTime() * 2.0f) * radians(30.0f);

		mat4 pendulumTransform = mat4(1.0f);

		pendulumTransform = translate(pendulumTransform, vec3(0.0f, 1.5f, 0.0f));
		pendulumTransform = rotate(pendulumTransform, angle, vec3(0.0f, 0.0f, 1.0f));
		pendulumTransform = translate(pendulumTransform, vec3(0.0f, -0.5f, 0.0f));

		rodF.transformation(pendulumTransform);
		rodB.transformation(pendulumTransform);
		rodL.transformation(pendulumTransform);
		rodR.transformation(pendulumTransform);
		rodT.transformation(pendulumTransform);
		rodD.transformation(pendulumTransform);

		rodF.draw(ourShader);
		rodB.draw(ourShader);
		rodL.draw(ourShader);
		rodR.draw(ourShader);
		rodT.draw(ourShader);
		rodD.draw(ourShader);

		circlePoly.transformation(pendulumTransform);
		circlePoly.draw(ourShader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	const float cameraSpeed = 0.02f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		cameraPos += cross(cameraFront, normalize(cross(cameraFront, cameraUp))) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		cameraPos -= cross(cameraFront, normalize(cross(cameraFront, cameraUp))) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		mat4 rotationMatrix = glm::rotate(mat4(1.0f), 0.001f, vec3(0.0f, 1.0f, 0.0f));
		vec4 rotatedVectorHomogeneous = rotationMatrix * vec4(cameraFront, 1.0f);
		cameraFront = vec3(rotatedVectorHomogeneous);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		mat4 rotationMatrix = glm::rotate(mat4(1.0f), 0.001f, vec3(0.0f, -1.0f, 0.0f));
		vec4 rotatedVectorHomogeneous = rotationMatrix * vec4(cameraFront, 1.0f);
		cameraFront = vec3(rotatedVectorHomogeneous);
	}
}