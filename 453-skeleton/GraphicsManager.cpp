/**
 * CPSC 453 F24 Assignment 2
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-A21 project files 
 */

#include "GraphicsManager.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "WindowManager.h"
#include "Sprite.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h> // glfw is library that provides tools for creating an OpenGl context, defineing window parameters, and handling user input
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "InputManager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

GraphicsManager::GraphicsManager(int _num_sprites)
{
    // preallocate the sprites array for the intended number of sprites
    sprites.resize(_num_sprites);
    this->num_sprites = _num_sprites;
    // set sprite counter to zero
    sprite_counter = 0;
}

bool GraphicsManager::SetupGraphicsManager(InputManager *_input)
{
    // sprite setup
    sprite_counter = 0;
    sprite_transforms.resize(num_sprites);
    texture_ids.resize(num_sprites);

    // setup the window and input manager
    window = new WindowManager(SCR_WIDTH, SCR_HEIGHT);
    if (!window->SetupWindow())
    {
        return false;
    }

    // give the input manager to the window
    window->SetInputManager(_input);
    input_manager = _input;
    input_manager->WindowResizeInput(SCR_WIDTH, SCR_HEIGHT);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    // build and compile our shader program
    shader_program = new ShaderProgram("shaders/test.vert", "shaders/test.frag");

    // generating textures
    fire_texture = new Texture("textures/fire.png", GL_NEAREST);
    dimond_texture = new Texture("textures/diamond.png", GL_NEAREST);
    ship_texture = new Texture("textures/ship.png", GL_NEAREST);

    // setup imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->GetWindowPointer(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // create the transform buffer object
    glGenBuffers(1, &TBO);
    glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * num_sprites, sprite_transforms.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // create the texture id buffer object
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ARRAY_BUFFER, IBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::int32) * num_sprites, texture_ids.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &VAO); // vertex array object, tell the gpu we want to allocate memory for an array of values
    glGenBuffers(1, &VBO);      // vertex buffer object, the buffer to place values in. this will be use to put values into the vertex array
    glGenBuffers(1, &EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO); // bind vertex array means what is being placed in the buffers is put into this vertex array

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // this is to a element_array_buffer so it does not interfer with the array_buffer data being setup

    // place the position attributes at location 0 in the shader
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);

    // place the texture coordinates into position 1
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, IBO);

    // place the texture ids in position 2
    glEnableVertexAttribArray(2);
    glVertexAttribIPointer(2, 1, GL_INT, sizeof(glm::int32), (void *)0);
    // make it change with instances not vertices or fragments
    glVertexAttribDivisor(2, 1);

    glBindBuffer(GL_ARRAY_BUFFER, TBO);

    // place the transforms in position 3 to 6
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(0));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(glm::vec4)));

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(2 * sizeof(glm::vec4)));

    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(3 * sizeof(glm::vec4)));

    // make the transforms change instances not vertices or fragments
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    shader_program->use();
    glUniform1i(glGetUniformLocation(shader_program->GetShaderProgramID(), "texture1"), 0); // set the position of the first texture to 0 (TEXTURE0)
    glUniform1i(glGetUniformLocation(shader_program->GetShaderProgramID(), "texture2"), 1); // set the position of the second texture to 1 (TEXTURE1)
    glUniform1i(glGetUniformLocation(shader_program->GetShaderProgramID(), "texture3"), 2); // set the position of the third texture to 2 (TEXTURE2)

    // activate the textures
    glActiveTexture(GL_TEXTURE0);
    ship_texture->bind();
    glActiveTexture(GL_TEXTURE1);
    fire_texture->bind();
    glActiveTexture(GL_TEXTURE2);
    dimond_texture->bind();

    // we only have the one vertex array object so keep it bound
    glBindVertexArray(VAO);

    return true;
}

bool GraphicsManager::ShouldStop()
{
    return window->ShoudWindowClose();
}

void GraphicsManager::UpdateGraphics()
{
    // poll events
    glfwPollEvents();

    // loops through all sprites and converts their position and scale data into tranform data
    UpdateSpriteData();

    // upload the new transform data and texture ids to the gpu
    UploadData();

    glEnable(GL_FRAMEBUFFER_SRGB);
    // clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // One draw call, don't get no better
    // ####################################################################
    // ONE DRAW CALL!!!!!!!!
    // instance draw all elements
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, num_sprites);

    glDisable(GL_FRAMEBUFFER_SRGB);

    // update the GUI
    UpdateGUI();

    // swap buffers
    glfwSwapBuffers(window->GetWindowPointer());

    // check to see if escape key has been pressed
    if (glfwGetKey(window->GetWindowPointer(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window->GetWindowPointer(), true);
    }

    // send cursor position to the input manager
    double cursor_x;
    double cursor_y;
    glfwGetCursorPos(window->GetWindowPointer(), &cursor_x, &cursor_y);
    input_manager->MouseInput(cursor_x, cursor_y);
}

void GraphicsManager::AddSprite(Sprite *_sprite)
{
    // add a sprite at the last counter position
    sprites[sprite_counter] = _sprite;
    // increment the counter
    sprite_counter++;
}

void GraphicsManager::StopGraphics()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &TBO);
    glDeleteBuffers(1, &IBO);

    shader_program->DeleteShaderProgram();
    glfwTerminate();
}

void GraphicsManager::UpdateSpriteData()
{
    // for each sprite calculate its transform
    for (int i = 0; i < num_sprites; i++)
    {
        Sprite *sprite = sprites[i];
        glm::mat4 transform_mat = glm::mat4(1.0f);

        // apply position transform
        transform_mat = glm::translate(transform_mat, glm::vec3(sprite->position.x, sprite->position.y, 0.0f));
        // apply rotation transform
        transform_mat = glm::rotate(transform_mat, sprite->rotation.GetRawValue(), glm::vec3(0.0f, 0.0f, 1.0f));
        // apply scale transform
        transform_mat = glm::scale(transform_mat, glm::vec3(sprite->sprite_dims.x * sprite->scale, sprite->sprite_dims.y * sprite->scale, 1.0f));

        sprite_transforms[i] = transform_mat;
        // record texture id
        texture_ids[i] = sprite->texture_id;
    }
}

void GraphicsManager::UploadData()
{
    // upload data to the transform buffer object (TBO)
    glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * num_sprites, sprite_transforms.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // upload data to the texture ids buffer object (IBO)
    glBindBuffer(GL_ARRAY_BUFFER, IBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::int32) * num_sprites, texture_ids.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GraphicsManager::ResetGraphics()
{
    sprite_counter = 0;
    score = 0;
}

void GraphicsManager::UpdateGUI()
{
    // Starting the new ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // Putting the text-containing window in the top-left of the screen.
    ImGui::SetNextWindowPos(ImVec2(5, 5));

    // Setting flags
    ImGuiWindowFlags textWindowFlags =
        ImGuiWindowFlags_NoMove |           // text "window" should not move
        ImGuiWindowFlags_NoResize |         // should not resize
        ImGuiWindowFlags_NoCollapse |       // should not collapse
        ImGuiWindowFlags_NoSavedSettings |  // don't want saved settings mucking things up
        ImGuiWindowFlags_AlwaysAutoResize | // window should auto-resize to fit the text
        ImGuiWindowFlags_NoBackground |     // window should be transparent; only the text should be visible
        ImGuiWindowFlags_NoDecoration |     // no decoration; only the text should be visible
        ImGuiWindowFlags_NoTitleBar;        // no title; only the text should be visible

    if (has_won == false)
    {
        // Begin a new window with these flags. (bool *)0 is the "default" value for its argument.
        ImGui::Begin("scoreText", (bool *)0, textWindowFlags);

        // Scale up text a little, and set its value
        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("Score: %d", score); // Second parameter gets passed into "%d"
    }
    else
    {
        // Begin a new window with these flags. (bool *)0 is the "default" value for its argument.
        ImGui::Begin("scoreText", (bool *)0, textWindowFlags);

        // Dispaly you win message
        ImGui::SetWindowFontScale(2.5f);
        ImGui::Text("YOU WIN"); // Second parameter gets passed into "%d"
    }

    // End the window.
    ImGui::End();

    ImGui::Render();                                        // Render the ImGui window
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Some middleware thing
}

void GraphicsManager::DisplayWinMessage()
{
    has_won = true;
}

void GraphicsManager::UpdateScore(int _score)
{
    score = _score;
}