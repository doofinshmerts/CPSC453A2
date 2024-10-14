/**
 * CPSC 453 F24 Assignment 2
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-A21 project files 
 */

#pragma once

class Ship;

/**
 * handles input from the user and sends it to the ship
 */
class InputManager
{
private:
    // private variables here
    // the ship to send input to
    Ship *ship = nullptr;

    // the window height
    int window_height = 100;
    int window_width = 100;

public:
    void AssignShip(Ship *_ship);

    /**
     * handle keyboard input from the user
     * @param key: key code
     * @param scancode: scancode
     * @param action: action
     */
    void KeyboardInput(int key, int scancode, int action);

    /**
     * handle mouse input
     * @param xpos: the x position of the cursor
     * @param ypos: the y position of the cursor
     */
    void MouseInput(double xpos, double ypos);

    /**
     * handle window resize input
     * @param _width: the width of the window
     * @param _height: the height of the window
     */
    void WindowResizeInput(int _width, int _height);
};