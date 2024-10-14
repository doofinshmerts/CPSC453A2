/**
 * CPSC 453 F24 Assignment 2
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-A21 project files 
 */

#include "Sprite.h"
#include "GraphicsManager.h"

#include <iostream>

Sprite::Sprite(int _texture_id, GraphicsManager *_manager)
{
    if (_manager == nullptr)
    {
        return;
    }

    // add self to the graphics manager
    _manager->AddSprite(this);
    texture_id = _texture_id;
}