/**
 * CPSC 453 F24 Assignment 2
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-A21 project files 
 */

#include "InputManager.h"
#include "Ship.h"

#include <iostream>

void InputManager::AssignShip(Ship *_ship)
{
    ship = _ship;
}

void InputManager::KeyboardInput(int key, int scancode, int action)
{
    // if action is 0 then key has been released
    if (action == 0)
    {
        if (key == 87)
        {
            // stop moving on key released
            ship->UpdateMoveInput(0.0f);
        }

        if (key == 83)
        {
            // stop moving on key released
            ship->UpdateMoveInput(0.0f);
        }
    }
    else if (action == 1 || action == 2)
    {
        if (key == 87)
        {
            // start moving on key down
            ship->UpdateMoveInput(1.0f);
        }

        if (key == 83)
        {
            // start moving on key down
            ship->UpdateMoveInput(-1.0f);
        }
    }

    // std::cout << "key: " << key << std::endl;
}

void InputManager::MouseInput(double xpos, double ypos)
{
    float x_pos = (xpos * 2.0f / (float)window_width) - 1.0f;
    float y_pos = (ypos * 2.0f / (float)window_height) - 1.0f;
    // std::cout << "cursor pos: " << x_pos << ", " << y_pos << std::endl;
    ship->UpdateMouseInput(x_pos, -y_pos);
}

void InputManager::WindowResizeInput(int _width, int _height)
{
    window_height = _height;
    window_width = _width;
}
