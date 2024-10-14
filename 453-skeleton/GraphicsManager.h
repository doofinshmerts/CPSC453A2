/**
 * CPSC 453 F24 Assignment 2
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-A21 project files 
 */

#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class WindowManager;
class ShaderProgram;
class Texture;
class GUIManager;
class Sprite;
class InputManager;

/**
 * Graphics stuff, records and update data needed for rendering graphical information to the screen
 */
class GraphicsManager
{
private:
    // private variables here
    // settings
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    // the transform buffer object id
    unsigned int TBO;
    // the texture id buffer object id
    unsigned int IBO;
    // the vertex buffer object
    unsigned int VBO;
    // the element buffer object
    unsigned int EBO;
    // the vertex array object
    unsigned int VAO;

    // the array of vertices
    float vertices[20] = {
        // x     y     z    texture coordinates
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f   // top left
    };
    // the array of indices
    unsigned int indices[6] = {
        // note that we start from 0!
        0, 1, 3, // first Triangle
        1, 2, 3  // second Triangle
    };

    // the array of sprites that are to be drawn
    std::vector<Sprite *> sprites;
    // sprite counter counts how many sprites have actually been added
    int sprite_counter = 0;
    int num_sprites = 0;

    // the array of transforms for the sprites
    std::vector<glm::mat4> sprite_transforms;

    // the array of texture ids for each sprite
    std::vector<glm::int32> texture_ids;
    // the window
    WindowManager *window = nullptr;
    // the shader program
    ShaderProgram *shader_program = nullptr;
    // the GUI Manager
    GUIManager *gui_manager = nullptr;
    // the input manager
    InputManager *input_manager = nullptr;
    // the textures:
    Texture *ship_texture = nullptr;
    Texture *dimond_texture = nullptr;
    Texture *fire_texture = nullptr;

    // variables for the gui
    bool has_won = false;
    int score = 0;

public:
    // public function here
    // constructor
    GraphicsManager(int _num_sprites);

    /**
     * sets up everything needed for rendering
     * 1- initializes the arrays for the sprite data
     * 2- creates the window
     * 3- binds the input manager to the window
     * 4- setup glad
     * 5- load shaders
     * 6- load textures
     * 7- create Vertex buffer objects and vertex array pointers
     *
     * @param num_sprites: the number of pickup dimonds to allocate for
     * @param _input: the input manager
     * @return: false if a system could not setup
     */
    bool SetupGraphicsManager(InputManager *_input);

    /**
     * @return: returns true if the window was closed
     */
    bool ShouldStop();

    /**
     * tells the gui manager to display a game won message
     */
    void DisplayWinMessage();

    /**
     * tells the gui manager to update the score
     */
    void UpdateScore(int _score);

    /**
     * updates the graphics data and draws to the screen
     */
    void UpdateGraphics();

    /**
     * Adds a sprite to the graphics manager
     * @param _sprite: the reference to the sprite to be added
     */
    void AddSprite(Sprite *_sprite);

    /**
     * deactivates all processes related to graphics
     */
    void StopGraphics();

    /**
     * resets transform and sprite arrays
     */
    void ResetGraphics();

private:
    // private functions here

    /**
     * moves data from the sprites into the texture_ids and sprite_transforms arrays,
     * then uploads the arrays to the gpu
     */
    void UpdateSpriteData();

    /**
     * uploads transform and texture data to the gpu
     */
    void UploadData();

    /**
     * updates the gui
     */
    void UpdateGUI();
};