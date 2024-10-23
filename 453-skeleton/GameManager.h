/**
 * CPSC 453 F24 Assignment 2
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-A21 project files 
 */

#pragma once

#include <vector>
#include "Rotation.h"

class Ship;
class InputManager;
class GraphicsManager;
class Diamond;

/**
 * Hi level game logic, manages and updates game objects, runs the game loop
 */
class GameManager
{
private:
    // private variables here
    // set max speed of diamond
    const float DIAMOND_MAX_SPEED = 0.4f; // 2.0f would cross screen in one second
    const float DIAMOND_MIN_SPEED = 0.1f;
    const float ORBIT_SPEED = 2.0f; // the speed that the fire orbits the dimonds

    // the radial position of all fire sprites relative to their parents coordinate system
    Rotation fire_rotation = 0.0f;

    // the number of pick up dimonds in the game
    int num_dimonds = 3;
    // the player ship
    Ship *ship = nullptr;
    // the input manager
    InputManager *input_manager = nullptr;
    // the graphics manager
    GraphicsManager *graphics_manager;
    // the game score
    int score = 0;
    // the collection of pickup dimonds
    std::vector<Diamond *> dimonds;

    // should the game restart
    bool should_restart = false;

    // has the game been won
    bool has_won = false;

public:
    // public function here

    /**
     * sets up the game, initalizes the ship, dimonds, InputManager, Graphics Manager
     */
    GameManager();

    /**
     * Initalize with specified number of pick up dimonds
     * @param _num: the number of pick ups
     */
    GameManager(int _num);

    /**
     * starts the game playing
     */
    void StartGame();

private:
    // private functions here

    /**
     * creates the game loop
     */
    void CreateGameLoop();

    /**
     * setup the game
     */
    void SetupGame();

    /**
     * updates the game to the next frame
     * @param delta_time_s: the time since the last frame
     */
    void UpdateGame(float delta_time_s);

    /**
     * resets the score and positions of the other objects
     */
    void ResetGame();
};