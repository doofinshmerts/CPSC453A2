/**
 * CPSC 453 F24 Assignment 2
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-A21 project files 
 */

#include "Ship.h"
#include "Sprite.h"

#include <iostream>

Ship::Ship(GraphicsManager *_manager) : GameObject(nullptr)
{
    // create the ship sprite
    sprite = new Sprite(0, _manager);
    sprite->sprite_dims = glm::vec2(0.18f, 0.12f);

    // set the ship bound radius (used for collision)
    bound_radius = 0.06f;
    // set the scale of its coordinate system (will make the child diamonds smaller)
    axis_scale = 0.5f;
}

void Ship::Update(float delta_time)
{
    // update position based on move speed, direction, and delta time
    rel_position = rel_position + glm::vec2(-glm::sin(world_rotation.GetRawValue()), glm::cos(world_rotation.GetRawValue())) * speed * delta_time;
    sprite->position = GetWorldPosition();
    sprite->rotation = world_rotation;
    sprite->scale = local_scale * GetParentScaleFactor();

    // update the children
    for (int i = 0; i < children.size(); i++)
    {
        GameObject *child = children[i];
        if (child != nullptr)
        {
            child->Update(delta_time);
        }
    }
}

void Ship::UpdateMouseInput(float pos_x, float pos_y)
{
    // use the sprite location becuase that is what the player sees
    float y_delta = pos_y - sprite->position.y;
    float x_delta = pos_x - sprite->position.x;

    // if the mouse is too close to the ship, then do not update the rotation
    float sq_dist = (y_delta * y_delta) + x_delta * x_delta - DEAD_ZONE * DEAD_ZONE;
    if (sq_dist < 0)
    {
        speed = 0.0f;
        return;
    }

    // update the rotation to point the ship at the mouse
    world_rotation = std::atan2(y_delta, x_delta) - 1.570796327f;
    axis_rotation = world_rotation;
}

void Ship::UpdateMoveInput(float _move_speed)
{
    speed = _move_speed;

    // check that move input has been recived (should be -1 or 1 )
    if (abs(speed) > 0.9f && has_moved == false)
    {
        has_moved = true;
    }
}

bool Ship::HasShipMoved()
{
    return has_moved;
}

void Ship::IncrementSize(float factor)
{
    local_scale = local_scale * factor;
}