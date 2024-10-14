/**
 * CPSC 453 F24 Assignment 2
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-A21 project files 
 */

#pragma once
#include "Rotation.h"
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Sprite;

/**
 * Has a coordinate system and an associated renderable sprite object,
 * can be parented to or be a parent of another game object
 */
class GameObject
{
protected:
    // private variables here
    // the sprite associated with this game object
    Sprite *sprite = nullptr;

    // transform
    // the position relative to the parent in the parents coordinate system (world position if no parent)
    glm::vec2 rel_position = glm::vec2(0.0f, 0.0f); // this is also the origin of this objects local coordinate system
    // rotation of this object (world rotation, is not effected by parent rotation)
    Rotation world_rotation = 0.0f;
    // rotation of this objects coordinate system
    Rotation axis_rotation = 0.0f;
    // the scale applied to this object (is multiplied by the scale of the parent coordinate system)
    float local_scale = 1.0f;
    // the scale of the coordinate system (does not effect this object, only its children)
    float axis_scale = 1.0f;

    // the children of this object
    std::vector<GameObject *> children;
    GameObject *parent = nullptr;

    // the bounding radius of this object
    float bound_radius = 0.0f;

public:
    // public function here

    // constructor
    GameObject(Sprite *_sprite);

    // destructor
    ~GameObject();

    /**
     * add a child game object to this game object
     * @param child: the child game object to add
     */
    void AddChild(GameObject *child);

    /**
     * Assign a parent game object (will call add child on the parent with this object as the argument)
     * @param parent: the parent to assign
     */
    void AssignParent(GameObject *parent);

    /**
     * Updates the game object and all of its children, sends coordinate information to its sprite
     * @param deltaTime: the time that has passed since the last update
     */
    virtual void Update(float deltaTime);

    /**
     * gets the position of this Game Object in the world (the non-relative position)
     */
    glm::vec2 GetWorldPosition();

    /**
     * gets the rotation of the object
     */
    Rotation GetWorldRotation();

    /**
     * gets the bounding radius of this object in world scale
     */
    float GetBoundRadius();

    /**
     * sets the local size of the bounding radius
     * @param radius: the bounding radius if world scale = 1
     */
    void SetBoundRadius(float radius);

    /**
     * gets the world scale factor of this object
     */
    float GetParentScaleFactor();

    /**
     * sets the relative position of this object
     */
    void SetRelativePosition(glm::vec2 pos);
};
