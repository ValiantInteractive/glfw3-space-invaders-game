// Main Program v1.0

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstdio>
#include "logic.h"

int keysArePressed[512];
const float movementSpeed = 0.001f;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    keysArePressed[key] = (glfwGetKey(window, key) == GLFW_PRESS);

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        shoot();
        updateScore(-10);
    }
}

void keyInput()
{
    if(player.x < BORDER && player.x > -BORDER) {
        if (keysArePressed[GLFW_KEY_RIGHT]) {
            player.x += movementSpeed;
        }
        if (keysArePressed[GLFW_KEY_LEFT]) {
            player.x -= movementSpeed;
        }
    } else if(player.x <= -BORDER) {
        player.x += movementSpeed;
    } else if(player.x >= BORDER) {
        player.x -= movementSpeed;
    }
}

int main(int argc, char *argv[])
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(800, 600, "Arcade Shooter", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);

    initValues();

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = (float) width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        update();
        glfwSwapBuffers(window);
        keyInput();
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
