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

Diamond::~Diamond()
{
    delete fire_object;
}

void Diamond::Update(float delta_time)
{
    if (!is_collected)
    {
        // if the diamond has not been collected by the ship then make the diamond move
        glm::vec2 pos = GetWorldPosition();

        // reflect off of walls of the world
        if ((pos.x > 1.0f) || (pos.x < -1.0f))
        {
            direction = glm::vec2(-direction.x, direction.y);
        }
        else if ((pos.y > 1.0f) || (pos.y < -1.0f))
        {
            direction = glm::vec2(direction.x, -direction.y);
        }

        // update position based on move speed, direction, and delta time
        rel_position = rel_position + direction * delta_time * speed;
    }

    if (is_collected && parent != nullptr)
    {
        // rotate the diamond with the parent
        world_rotation = parent->GetWorldRotation() - 1.570796327f;
    }

    // make the fire rotate around by rotating the coordinate system of the diamond
    axis_rotation = axis_rotation + ORBIT_SPEED * delta_time;

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

void Diamond::ParentToShip(Ship *_ship, int score)
{
    is_collected = true;
    AssignParent(_ship);

    // place the diamond at the appropriate position in the ship
    rel_position = glm::vec2(0.0f, -COLLECTED_SPACING * (float)score - 0.1f);
}