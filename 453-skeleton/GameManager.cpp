/**
 * CPSC 453 F24 Assignment 2
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-A21 project files 
 */

#include "GameManager.h"
#include "Ship.h"
#include "InputManager.h"
#include "GraphicsManager.h"
#include "Dimond.h"

#include <chrono>
#include <iostream>

GameManager::GameManager()
{
}

GameManager::GameManager(int _num)
{
    num_dimonds = _num;
}

void GameManager::SetupGame()
{
    // initialize score to zero
    score = 0;
    // create a graphics manager
    graphics_manager = new GraphicsManager((num_dimonds * 2 + 1));

    // initialize the ship
    ship = new Ship(graphics_manager);

    // create an input manager and assign it a ship
    input_manager = new InputManager();
    input_manager->AssignShip(ship);

    // create the dimonds
    dimonds.resize(num_dimonds);
    for (int i = 0; i < num_dimonds; i++)
    {
        // give each diamond random position, speed, and direction
        float speed = (((float)(rand() % 1000)) * 0.001f) * (DIAMOND_MAX_SPEED - DIAMOND_MIN_SPEED) + DIAMOND_MIN_SPEED;
        float rotation = (((float)(rand() % 1000)) * 0.006283185f);
        float x = (((float)(rand() % 1000)) * 0.001f) * 2.0f - 1.0f;
        float y = (((float)(rand() % 1000)) * 0.001f) * 2.0f - 1.0f;
        Diamond *diamond = new Diamond(speed, rotation, x, y, graphics_manager);
        dimonds[i] = diamond;
    }

    // setup the graphics manager and assign it the input manager and expected number of sprites
    graphics_manager->SetupGraphicsManager(input_manager);
}

void GameManager::StartGame()
{
    SetupGame();
    CreateGameLoop();
}

void GameManager::CreateGameLoop()
{

    should_restart = false;
    // time keeping
    std::chrono::high_resolution_clock clock;
    int64_t time = std::chrono::duration_cast<std::chrono::microseconds>(clock.now().time_since_epoch()).count();
    int64_t last_time = time;
    int64_t delta_time = 0;
    float delta_time_seconds = 0.0f;

    // start the game loop
    while (!graphics_manager->ShouldStop())
    {
        // measure time in seconds since the start
        time = std::chrono::duration_cast<std::chrono::microseconds>(clock.now().time_since_epoch()).count();
        delta_time = time - last_time;
        last_time = time;
        delta_time_seconds = (float)(delta_time) * 0.000001f;

        // reset the game if this is true
        if (should_restart)
        {
            should_restart = false;
            ResetGame();
            delta_time = 0.0f;
        }

        // update the geometry and graphics data
        UpdateGame(delta_time_seconds);
    }

    // make sure to terminate opengl stuff properly
    graphics_manager->StopGraphics();
}

void GameManager::UpdateGame(float delta_time)
{

    // update the ship
    ship->Update(delta_time);

    // update each diamond and check for collisions
    for (int i = 0; i < num_dimonds; i++)
    {
        // update the positions of each diamond
        dimonds[i]->Update(delta_time);

        // do not check for collisions if the player has not moved the ship at all
        if (!ship->HasShipMoved())
        {
            continue;
        }

        // check to see if the diamond or fire is hitting the ship
        switch (dimonds[i]->ShipCollisionResult(ship->GetWorldPosition(), ship->GetBoundRadius()))
        {

        case 1:
            // ship pickup diamond
            score++;
            dimonds[i]->ParentToShip(ship, score);
            ship->IncrementSize(1.2f);
            graphics_manager->UpdateScore(score);

            // if all diamonds are collected then dispaly message
            if (score == num_dimonds)
            {
                graphics_manager->DisplayWinMessage();
            }

            break;
        case 2:
            // ship hit the fire, restart game
            should_restart = true;
            break;
        }
    }

    // update the graphics
    graphics_manager->UpdateGraphics();
}

void GameManager::ResetGame()
{
    // reset the graphics
    graphics_manager->ResetGraphics();

    // create new ship
    ship = new Ship(graphics_manager);
    input_manager->AssignShip(ship);

    // reset the score to 0
    score = 0;

    // create new diamonds
    for (int i = 0; i < num_dimonds; i++)
    {
        float speed = (((float)(rand() % 1000)) * 0.001f) * (DIAMOND_MAX_SPEED - DIAMOND_MIN_SPEED) + DIAMOND_MIN_SPEED;
        float rotation = (((float)(rand() % 1000)) * 0.006283185f);
        float x = (((float)(rand() % 1000)) * 0.001f) * 2.0f - 1.0f;
        float y = (((float)(rand() % 1000)) * 0.001f) * 2.0f - 1.0f;
        Diamond *diamond = new Diamond(speed, rotation, x, y, graphics_manager);
        dimonds[i] = diamond;
    }
}

GameManager::~GameManager()
{
    delete ship;
    delete input_manager;
    delete graphics_manager;
    for (int i = 0; i < num_dimonds; i++)
    {
        delete dimonds[i];
    }
}