/**
 * CPSC 453 F24 Assignment 2
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-A21 project files 
 */

#include "WindowManager.h"
#include "InputManager.h"

#include <iostream>

WindowManager::WindowManager(int width, int height)
{
    this->width = width;
    this->height = height;
}

WindowManager::~WindowManager()
{
    delete window;
}

bool WindowManager::SetupWindow()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(width, height, "Assignment2", NULL, NULL);
    if (window == NULL)
    {

        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, UpdateWindowSize);

    return true;
}

void WindowManager::SetInputManager(InputManager *_input)
{

    glfwSetWindowUserPointer(window, _input);
    // bind meta callbacks to actual callbacks
    glfwSetKeyCallback(window, KeyboardInputHandler);
}

bool WindowManager::ShoudWindowClose()
{
    return glfwWindowShouldClose(window);
}

GLFWwindow *WindowManager::GetWindowPointer()
{
    return window;
}

void WindowManager::UpdateWindowSize(GLFWwindow *_window, int _width, int _height)
{
    InputManager *_input = static_cast<InputManager *>(glfwGetWindowUserPointer(_window));
    if (_input != nullptr)
    {
        _input->WindowResizeInput(_width, _height);
    }
    // TODO: use input manager
    glViewport(0, 0, _width, _height);
}

void WindowManager::KeyboardInputHandler(GLFWwindow *_window, int key, int scancode, int action, int mods)
{
    // TODO: use input manager
    InputManager *_input = static_cast<InputManager *>(glfwGetWindowUserPointer(_window));
    if (_input != nullptr)
    {
        _input->KeyboardInput(key, scancode, action);
    }
}