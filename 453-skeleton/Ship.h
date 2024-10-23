/**
 * CPSC 453 F24 Assignment 2
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-A21 project files
 */

#pragma once

#include "GameObject.h"
class GraphicsManager;
class Diamond;

/**
 * type of game object that can be controlled by the player
 */
class Ship : public GameObject
{
private:
    // spacing of the diamond holder from the ship
    const float INITIAL_SPACING = 0.2f;

    // private variables here
    // the graphics manager that will render this objects sprite
    GraphicsManager *graphics_manager = nullptr;

    // the maximum speed that this ship can move at
    const float MAX_SPEED = 0.3f;
    // if the mouse is closer than this then do not update rotation
    const float DEAD_ZONE = 0.01f;
    // the speed that the ship should move in the next frame
    float speed = 0.0f;

    // has the ship recived any move input from the player
    bool has_moved = false;

    // holds the diamonds behind the ship
    GameObject *diamond_holder = nullptr;

public:
    // public function here

    // constructor
    Ship(GraphicsManager *_manager);

    /**
     * Updates the game object and all of its children, sends coordinate information to its sprite
     * @param deltaTime: the time that has passed since the last update
     */
    virtual void Update(float deltaTime);

    /**
     * update the rotation of the ship to point towards the given coordinates
     * @param pos_x: x position of cursor (-1 to 1)
     * @param pos_y: y position of cursor (-1 to 1)
     */
    void UpdateMouseInput(float pos_x, float pos_y);

    /**
     * moves the ship forward or back based on the move speed
     * @param move_speed: the amount to move forward (negative values make it go backwards)
     */
    void UpdateMoveInput(float move_speed);

    /**
     * has the ship moved from its initial position
     */
    bool HasShipMoved();

    /**
     * increases the size of the ship in proportion to the score
     * @param factor: multiplies the existing ship size by factor
     */
    void IncrementSize(float factor);

    /**
     * parents a diamond to this ship
     * @param _diamond: the diamond to pick up
     */
    void PickUpDiamond(Diamond* _diamond, int score);
};