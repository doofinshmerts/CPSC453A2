/**
 * CPSC 453 F24 Assignment 2
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-A21 project files 
 */

#include "GameObject.h"
#include "Sprite.h"

GameObject::GameObject(Sprite *_sprite)
{
    // assign the sprite
    sprite = _sprite;
}

void GameObject::AddChild(GameObject *child)
{
    // add this child to our list of children
    children.push_back(child);
    // make this object the parent of the given child
    child->parent = this;
}

void GameObject::AssignParent(GameObject *parent)
{
    parent->AddChild(this);
}

void GameObject::Update(float deltaTime)
{
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
            child->Update(deltaTime);
        }
    }
}

glm::vec2 GameObject::GetWorldPosition()
{
    if (parent != nullptr)
    {
        // convert coordinates from local to the parent to World
        float angle = parent->axis_rotation.GetRawValue();
        glm::vec2 non_rel_position = glm::vec2(rel_position.x * glm::cos(angle) - rel_position.y * glm::sin(angle), rel_position.x * glm::sin(angle) + rel_position.y * glm::cos(angle));
        return non_rel_position * GetParentScaleFactor() + parent->GetWorldPosition();
    }
    else
    {
        return rel_position;
    }
}

Rotation GameObject::GetWorldRotation()
{
    return world_rotation;
}

float GameObject::GetParentScaleFactor()
{
    if (parent == nullptr)
    {
        // world coordinate system has axis scaling = 1
        return 1;
    }
    else
    {
        // recursively calculate the total scaling from all parent coordinate systems
        return parent->axis_scale * parent->GetParentScaleFactor();
    }
}

float GameObject::GetBoundRadius()
{
    // return the bound radius scaled to world
    return bound_radius * local_scale * GetParentScaleFactor();
}

void GameObject::SetBoundRadius(float radius)
{
    bound_radius = radius;
}

void GameObject::SetRelativePosition(glm::vec2 pos)
{
    rel_position = pos;
}