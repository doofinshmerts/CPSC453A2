/**
 * CPSC 453 F24 Assignment 2
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-A21 project files
 */

#include "Dimond.h"
#include "Sprite.h"
#include "Rotation.h"
#include "Ship.h"
#include <iostream>

Diamond::Diamond(float _speed, float _direction, float x, float y, GraphicsManager *_manager) : GameObject(nullptr)
{
    // initialize the diamond sprite
    sprite = new Sprite(2, _manager);
    sprite->sprite_dims = glm::vec2(0.14f, 0.14f);
    bound_radius = 0.07f;

    // create the fire object
    Sprite *fire = new Sprite(1, _manager);
    fire->sprite_dims = glm::vec2(0.1f, 0.1f);
    fire_object = new GameObject(fire);
    fire_object->SetBoundRadius(0.05f);

    // make the fire object a child object
    AddChild(fire_object);
    fire_object->SetRelativePosition(glm::vec2(ORBIT_DIST, 0.0f));

    // initialize position and speed
    speed = _speed;
    direction = glm::vec2(glm::cos(_direction), glm::sin(_direction));
    rel_position = glm::vec2(x, y);
}

void Diamond::Update(float delta_time)
{
    // if the diamond has not been collected by the ship then make the diamond move
    if (!is_collected)
    {

        // update position based on move speed, direction, and delta time
        rel_position = rel_position + direction * delta_time * speed;

        // bound the diamonds position to between -1.0 and 1.0 and reflect it off walls
        if (rel_position.x > 1.0f)
        {
            rel_position.x = 1.0f;
            direction = glm::vec2(-direction.x, direction.y);
        }
        else if (rel_position.x < -1.0f)
        {
            rel_position.x = -1.0f;
            direction = glm::vec2(-direction.x, direction.y);
        }

        if (rel_position.y > 1.0f)
        {
            rel_position.y = 1.0f;
            direction = glm::vec2(direction.x, -direction.y);
        }
        else if (rel_position.y < -1.0f)
        {
            rel_position.y = -1.0f;
            direction = glm::vec2(direction.x, -direction.y);
        }
    }

    if (parent != nullptr)
    {
        if (is_collected && (has_won == false))
        {
            // rotate the diamond with the parent
            world_rotation = parent->GetWorldRotation() + 1.570796327f;
        }
        else if (has_won == true)
        {
            world_rotation = world_rotation - WIN_SPIN_SPEED * delta_time;
        }

        // make the fire object inherit the rotation of the ship
        fire_object->SetWorldRotation(parent->GetWorldRotation() + 1.570796327f);
    }

    // get position scale and rotation data and send it to the sprite
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

int Diamond::ShipCollisionResult(glm::vec2 ship_position, float ship_radius)
{
    if (is_collected)
    {
        // do nothing if this diamond has already been collected
        return 0;
    }

    // get the distance to the position of the fire
    glm::vec2 diff_vec = (ship_position - fire_object->GetWorldPosition());
    // get the squared distance to the fire
    float sq_dist = glm::dot(diff_vec, diff_vec);
    // get the squared min distance before collision
    float bound = ship_radius + fire_object->GetBoundRadius();
    bound = bound * bound;

    // if the ships distance to the fire is less than sum of the two radii then it has collided
    if (sq_dist < bound)
    {
        return 2;
    }

    // get the difference vector to the position of the diamond
    diff_vec = (ship_position - GetWorldPosition());
    // get the squared distance to the diamond
    sq_dist = glm::dot(diff_vec, diff_vec);
    // get the squared min distance before collision
    bound = ship_radius + GetBoundRadius();
    bound = bound * bound;

    if (sq_dist < bound)
    {
        return 1;
    }

    // no collision occured
    return 0;
}

void Diamond::ParentToShip(GameObject *_ship, int score)
{
    is_collected = true;
    AssignParent(_ship);

    // place the diamond at the appropriate position in the ship
    rel_position = glm::vec2(0.0f, -COLLECTED_SPACING * (float)score);
}

void Diamond::SetFireRotation(Rotation _rotation)
{
    // make the fire rotate around by rotating the coordinate system of the diamond
    axis_rotation = _rotation;
}

void Diamond::SetGameWon(bool _game_won)
{
    has_won = _game_won;
}