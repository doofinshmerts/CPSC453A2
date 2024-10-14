/**
 * CPSC 453 F24 Assignment 2
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-A21 project files 
 */

#pragma once
#include "GameObject.h"

class Ship;
class GraphicsManager;

/**
 * Diamond class, the diamond game object can be picked up by the ship, has collision dettection
 * has a fire obstical that the ship can hit
 */
class Diamond : public GameObject
{
private:
    // the constant factors for the orbit speed and distance of the fire sprite
    const float ORBIT_DIST = 0.15f;
    const float ORBIT_SPEED = 2.0f;

    // spacing from the ship when parented to the ship
    const float COLLECTED_SPACING = 0.2f;

    // private variables here
    GameObject *fire_object = nullptr;

    // the speed and direction of this diamond
    float speed = 0.0f;
    glm::vec2 direction = glm::vec2(1.0f, 0.0f);

    // the graphics manager that will render this objects sprite
    GraphicsManager *graphics_manager = nullptr;

    // has the ship collected this diamond
    bool is_collected = false;

public:
    // public function here

    /**
     * creates the dimond object including the fire object as its child
     * @param _speed: the speed of this diamonds movement
     * @param _direction: the direction of this diamonds movement
     */
    Diamond(float _speed, float _direction, float x, float y, GraphicsManager *_manager);

    /**
     * Updates the game object and all of its children, sends coordinate information to its sprite
     * makes the fire sprite move around the dimond sprite
     * makes the dimond move
     * makes the dimond bounce of the walls of the screen
     * @param deltaTime: the time that has passed since the last update
     */
    virtual void Update(float deltaTime);

    /**
     * checks to see if the ship is colliding with the object or not
     * @param ship_position: the position of the ship in world space
     * @param ship_radius: the radius of the ship in world space
     * @return: 0 if not colliding, 1 if colliding with dimond, 2 if colliding with fire
     */
    int ShipCollisionResult(glm::vec2 ship_position, float ship_radius);

    /**
     * parents the dimonds coordinate system to the ship and stops the dimond from moving freely
     * @param ship: the ship to parent to
     * @param score: the current score so we know where to place the diamond on the ship
     */
    void ParentToShip(Ship *ship, int score);
};