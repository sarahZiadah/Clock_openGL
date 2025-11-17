
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
using namespace std;

int width = 1200;
int height = 720;

vec3 cameraPos = vec3(2.0f, 1.0f, 6.0f);
vec3 cameraFront = normalize(vec3(0.0f, 0.0f, 0.0f) - cameraPos);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

void processInput(GLFWwindow* window);


Polygon createCircle(float radius, int segments, vec3 color, float zPos = 0.26f)
{
    vector<vec3> vertices;
    float step = 2 * 3.1415926f / segments;

    for (int i = 0; i < segments; i++)
    {
        float theta1 = i * step;
        float theta2 = (i + 1) * step;

        vertices.push_back(vec3(0.0f, 0.0f, zPos));
        vertices.push_back(vec3(radius * cos(theta1), radius * sin(theta1), zPos));
        vertices.push_back(vec3(radius * cos(theta2), radius * sin(theta2), zPos));
    }

    return Polygon(vertices, color);
}

int main()
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(width, height, "Clock", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);

    Shader ourShader("./shaders/vs/L3.vs", "./shaders/fs/L3.fs");
    ourShader.use();

    float boxW = 2.0f, boxH = 3.0f, boxDeapth = 0.5f;
    float hw = boxW / 2, hh = boxH / 2, hd = boxDeapth / 2;


    Polygon boxF({ 
        vec3(-hw, hh, hd), 
        vec3(hw, hh, hd), 
        vec3(hw, -hh, hd), 
        vec3(-hw, -hh, hd) }, 
        vec3(0.7f, 0.4f, 0.2f));
    Polygon boxB({ 
        vec3(-hw, hh, -hd), 
        vec3(hw, hh, -hd), 
        vec3(hw, -hh, -hd), 
        vec3(-hw, -hh, -hd) }, 
        vec3(0.6f, 0.3f, 0.15f));
    Polygon boxL({ 
        vec3(-hw, hh, -hd), 
        vec3(-hw, hh, hd), 
        vec3(-hw, -hh, hd), 
        vec3(-hw, -hh, -hd) }, 
        vec3(0.6f, 0.3f, 0.15f));
    Polygon boxR({ 
        vec3(hw, hh, -hd), 
        vec3(hw, hh, hd), 
        vec3(hw, -hh, hd), 
        vec3(hw, -hh, -hd) }, 
        vec3(0.6f, 0.3f, 0.15f));
    Polygon boxT({ 
        vec3(-hw, hh, -hd), 
        vec3(hw, hh, -hd), 
        vec3(hw, hh, hd), 
        vec3(-hw, hh, hd) }, 
        vec3(0.6f, 0.3f, 0.15f));
    Polygon boxD({ 
        vec3(-hw, -hh, -hd), 
        vec3(hw, -hh, -hd), 
        vec3(hw, -hh, hd), 
        vec3(-hw, -hh, hd) }, 
        vec3(0.6f, 0.3f, 0.15f));


    float rodLength = 2.0f;
    vector<vec3> rodFront = { 
        vec3(-0.1f, rodLength / 2, 0.1f), 
        vec3(0.1f, rodLength / 2, 0.1f), 
        vec3(0.1f, -rodLength / 2, 0.1f), 
        vec3(-0.1f, -rodLength / 2, 0.1f) };
    vector<vec3> rodBack = { 
        vec3(-0.1f, rodLength / 2, -0.1f), 
        vec3(0.1f, rodLength / 2, -0.1f), 
        vec3(0.1f, -rodLength / 2, -0.1f), 
        vec3(-0.1f, -rodLength / 2, -0.1f) };
    vector<vec3> rodLeft = { 
        vec3(-0.1f, rodLength / 2, -0.1f), 
        vec3(-0.1f, rodLength / 2, 0.1f), 
        vec3(-0.1f, -rodLength / 2, 0.1f), 
        vec3(-0.1f, -rodLength / 2, -0.1f) };
    vector<vec3> rodRight = { 
        vec3(0.1f, rodLength / 2, -0.1f), 
        vec3(0.1f, rodLength / 2, 0.1f), 
        vec3(0.1f, -rodLength / 2, 0.1f), 
        vec3(0.1f, -rodLength / 2, -0.1f) };
    vector<vec3> rodTop = { 
        vec3(-0.1f, rodLength / 2, -0.1f), 
        vec3(0.1f, rodLength / 2, -0.1f), 
        vec3(0.1f, rodLength / 2, 0.1f), 
        vec3(-0.1f, rodLength / 2, 0.1f) };
    vector<vec3> rodBottom = { 
        vec3(-0.1f, -rodLength / 2, -0.1f), 
        vec3(0.1f, -rodLength / 2, -0.1f), 
        vec3(0.1f, -rodLength / 2, 0.1f), 
        vec3(-0.1f, -rodLength / 2, 0.1f) };
   
    Polygon rodD(rodBottom, vec3(0.6f, 0.3f, 0.15f));
    Polygon rodF(rodFront, vec3(0.5f, 0.2f, 0.1f));
    Polygon rodB(rodBack, vec3(0.5f, 0.3f, 0.15f));
    Polygon rodL(rodLeft, vec3(0.5f, 0.3f, 0.15f)); 
    Polygon rodR(rodRight, vec3(0.6f, 0.3f, 0.15f));
    Polygon rodT(rodTop, vec3(0.6f, 0.3f, 0.15f));


    Polygon clockFace = createCircle(0.8f, 60, vec3(1.0f, 1.0f, 1.0f), hd + 0.01f);
    mat4 clockFaceTransform = translate(mat4(1.0f), vec3(0.0f, hh - 1.2f, 0.0f));
    clockFace.transformation(clockFaceTransform);

    float handLength = 0.7f;   
    float handWidth = 0.03f;  

    vector<vec3> handFront = {
    vec3(-handWidth, 0.0f, 0.3f),   
    vec3(handWidth,  0.0f, 0.3f),
    vec3(handWidth,  handLength, 0.3f),
    vec3(-handWidth, handLength, 0.3f)
    };


    Polygon clockHand(handFront, vec3(0.2f, 0.2f, 0.2f));

    mat4 handTransform = translate(mat4(1.0f), vec3(0.0f, hh - 1.2f, 0.0f));
    clockHand.transformation(handTransform);


    mat4 projection = perspective(radians(45.0f), (float)width / height, 0.1f, 100.0f);
    ourShader.setMat4("projection", projection);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2, 0.2, 0.2, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mat4 view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        ourShader.setMat4("view", view);

        mat4 sceneTransform = mat4(1.0f);
        sceneTransform = translate(sceneTransform, vec3(0.0f, 0.0f, -2.0f));

        boxF.transformation(sceneTransform);
        boxB.transformation(sceneTransform);
        boxL.transformation(sceneTransform);
        boxR.transformation(sceneTransform);
        boxT.transformation(sceneTransform);
        boxD.transformation(sceneTransform);

        clockFace.transformation(sceneTransform);
        clockHand.transformation(sceneTransform);


        float angle = sin(glfwGetTime() * 2.0f) * radians(25.0f);
        mat4 pendulumTransform = mat4(1.0f);
        pendulumTransform = translate(pendulumTransform, vec3(0.0f, -hh, 0.0f)); 
        pendulumTransform = rotate(pendulumTransform, angle, vec3(0, 0, 1));
        pendulumTransform = translate(pendulumTransform, vec3(0.0f, -rodLength / 2, 0.0f));
        pendulumTransform = sceneTransform * pendulumTransform;

        rodF.transformation(pendulumTransform);
        rodB.transformation(pendulumTransform);
        rodL.transformation(pendulumTransform);
        rodR.transformation(pendulumTransform);
        rodT.transformation(pendulumTransform);
        rodD.transformation(pendulumTransform);


        boxF.draw(ourShader);
        boxB.draw(ourShader);
        boxL.draw(ourShader);
        boxR.draw(ourShader);
        boxT.draw(ourShader);
        boxD.draw(ourShader);


        clockFace.draw(ourShader);


        rodF.draw(ourShader);
        rodB.draw(ourShader);
        rodL.draw(ourShader);
        rodR.draw(ourShader);
        rodT.draw(ourShader);
        rodD.draw(ourShader);

        clockHand.draw(ourShader);


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

    const float cameraSpeed = 0.005f;


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

    float rotationAngle = 0.002f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        mat4 rotationMatrix = glm::rotate(mat4(1.0f), rotationAngle, vec3(0.0f, 1.0f, 0.0f));
        cameraFront = vec3(rotationMatrix * vec4(cameraFront, 1.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        mat4 rotationMatrix = glm::rotate(mat4(1.0f), -0.01f, vec3(0.0f, 1.0f, 0.0f));
        cameraFront = vec3(rotationMatrix * vec4(cameraFront, 1.0f));
    }
}