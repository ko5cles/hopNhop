//
// Created by Ze Pan on 11/27/22.
//

#ifndef ASSIGNMENT4TEX_GAME_H
#define ASSIGNMENT4TEX_GAME_H
// OpenGL Helpers to reduce the clutter

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
// GLFW is necessary to handle the OpenGL context
#include <GLFW/glfw3.h>
#endif

// OpenGL Mathematics Library
#include <glm/glm.hpp> // glm::vec3
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include "Resources.h"
#include "BoxRenderer.h"
#include "GameLev.h"
#include "Camera.h"

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};
enum CollideState{
    NONE,
    DROP,
    STAY
};



// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    // game state
    GameState               State;
    bool                    Keys[1024];
    unsigned int            Width, Height;
    std::vector<GameLevel> Levels;
    unsigned int Level;
    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    void CheckCollision();
    bool CheckComplete();
};

#endif //ASSIGNMENT4TEX_GAME_H
