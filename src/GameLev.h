//
// Created by Ze Pan on 11/30/22.
//

#ifndef ASSIGNMENT4TEX_GAMELEV_H
#define ASSIGNMENT4TEX_GAMELEV_H

#include <vector>

#include "GameObj.h"
#include "HopObj.h"
#include "BoxRenderer.h"
#include "ShadowRenderer.h"
#include "Resources.h"


class GameLevel
{
public:
    // level state
    std::vector<GameObject> Cubes;
    std::vector<GameObject> Walls;
    // constructor
    GameLevel() { }
    GameObject Start, End;
    // loads level from file
    void Load(const char *file, unsigned int levelWidth, unsigned int levelHeight);
    // render level
    void Draw(BoxRenderer &renderer,Texture& depthMap, glm::mat4 light, glm::vec3 camPos, glm::mat4 viewMatrix, glm::mat4 projMatrix);
    void Draw(ShadowRenderer &renderer,glm::vec3 camPos, glm::mat4 viewMatrix, glm::mat4 projMatrix);
private:
    // initialize level from tile data
    void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};


#endif //ASSIGNMENT4TEX_GAMELEV_H
