/**
 * CPSC 453 F24 Assignment 2
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-A21 project files 
 */

#pragma once
#include <GLFW/glfw3.h>

class InputManager;


/**
 * handles creating GLFWwindow
 */
class WindowManager
{
private:
    // private variables here
    // the width and height of the window
    int width = 0;
    int height = 0;

    // pointer to the glfw window
    GLFWwindow *window = nullptr;

    // the input manager to send input to
    InputManager *input_manager = nullptr;

public:
    // public function here

    // constructor
    WindowManager(int width, int height);

    // destructor
    ~WindowManager();

    /**
     * sets up the GLFW window
     * @return: false if window could not be created
     */
    bool SetupWindow();

    /**
     * sets the input manager
     * @param _input: the pointer to the input manager
     */
    void SetInputManager(InputManager *_input);

    /**
     * @return: true if the window should close
     */
    bool ShoudWindowClose();

    /**
     * @return: a pointer to the GLFWwindow
     */
    GLFWwindow *GetWindowPointer();

private:
    // private functions here

    /**
     * callback to resize the window on window resize event
     * @param _window: the window (dummy)
     * @param width: the width of the window
     * @param height: the height of the window
     */
    static void UpdateWindowSize(GLFWwindow *_window, int _width, int _height);

    // callback functions allowing input to the inputmanager
    static void KeyboardInputHandler(GLFWwindow *_window, int key, int scancode, int action, int mods);
};