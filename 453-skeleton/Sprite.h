/**
 * CPSC 453 F24 Assignment 2
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-A21 project files 
 */

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Rotation.h"

class GraphicsManager;

/**
 * holds position, scale, rotation, and texture id needed to render a sprite
 */
class Sprite
{
public:
    // private variables here
    // the position of the sprite on the screen
    glm::vec2 position = glm::vec2(0.0f, 0.0f);
    // the dimensions of this sprite
    glm::vec2 sprite_dims = glm::vec2(0.14, 0.14);
    // the scale of this sprite
    float scale = 1.0f;

    // the rotation of the sprite on the screen
    Rotation rotation = 0.0f;
    // the id of the texture being used
    int texture_id = 0;

    // the graphics manager that will render this objects sprite
    GraphicsManager *manager = nullptr;

public:
    // public function here
    /**
     * the constructor sets the texture id(the texture that this sprite will be rendered with)
     */
    Sprite(int texture_id, GraphicsManager *manager);
};