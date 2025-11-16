#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <learnopengl/shader_m.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
using namespace std;

class Polygon {
public:
	Polygon(vector<vec3> v, vec3 c) {
		vertices = v;
		head = v.at(0);
		color = c;
		model = mat4(1.0f);

		GLuint VBO, VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);

		// position attribute
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
		glEnableVertexAttribArray(0);
		this->VAO = VAO;
	}

	void transformation(mat4 t) {
		model = t;
	}

	void draw(Shader &shader)
	{
		shader.setVec3("objectColor", color);
		shader.setMat4("model", model);
		glBindVertexArray(this->VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());
	}

	void deleteBuffers() {
		glDeleteVertexArrays(1, &VAO);
		//glDeleteBuffers(1, &VBO);
	}

private:
	vec3 head;
	vector<vec3> vertices;
	vec3 color;
	mat4 model;
	GLuint VAO;
	Polygon();
};

