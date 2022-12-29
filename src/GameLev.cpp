//
// Created by Ze Pan on 11/30/22.
//
#include "GameLev.h"

#include <fstream>
#include <sstream>
#include <string>


void GameLevel::Load(const char *file, unsigned int levelWidth, unsigned int levelHeight)
{
    // clear old data
    this->Cubes.clear();
    // load from file
    unsigned int tileCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream("../levels/"+std::string(file));
    std::vector<std::vector<unsigned int>> tileData;
    if (fstream)
    {
        while (std::getline(fstream, line)) // read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode) // read each word separated by spaces
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            this->init(tileData, levelWidth, levelHeight);
    }
}

void GameLevel::Draw(BoxRenderer &renderer,Texture& depthMap,glm::mat4 light, glm::vec3 camPos,glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
    for(GameObject& iter: this->Walls)
        iter.Draw(renderer,depthMap,light, camPos,viewMatrix,projMatrix);
    for (GameObject &iter : this->Cubes)
        if (!iter.Destroyed)
            iter.Draw(renderer,depthMap, light,camPos,viewMatrix,projMatrix);
}

void GameLevel::Draw(ShadowRenderer &renderer,glm::vec3 camPos,glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
    for(GameObject& iter: this->Walls)
        iter.Draw(renderer,camPos,viewMatrix,projMatrix);
    for (GameObject &iter : this->Cubes)
        if (!iter.Destroyed)
            iter.Draw(renderer,camPos,viewMatrix,projMatrix);
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    // calculate dimensions
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size(); // note we can index vector at [0] since this function is only called if height > 0
    float unit_width = 1, unit_height = 1;

    // initialize all the walls
    this->Walls.push_back(GameObject(glm::vec3((width-1)/2.f,-2,0),glm::vec3(width+1,0.5,1.5),Resources::GetTexture("brick_wall")));
    this->Walls.push_back(GameObject(glm::vec3((width-1)/2.f,height+1,0),glm::vec3(width+1,0.5,1.5),Resources::GetTexture("brick_wall")));
    this->Walls.push_back(GameObject(glm::vec3(-1,(height-1)/2.f,0),glm::vec3(0.5,height+3.5,1.5),Resources::GetTexture("brick_wall")));
    this->Walls.push_back(GameObject(glm::vec3(width,(height-1)/2.f,0),glm::vec3(0.5,height+3.5,1.5),Resources::GetTexture("brick_wall")));
    this->Walls.push_back(GameObject(glm::vec3((width-1)/2.f,(height-1)/2.f,-0.55),glm::vec3(width+1,height+3.5,0.1),Resources::GetTexture("snow_ground")));

    // initialize level tiles based on tileData
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            // check block type from level data (2D level array)
            if (tileData[y][x] == 1) // start point
            {
                glm::vec3 pos(unit_width * x, unit_height * y, 0);
                glm::vec3 size(unit_width, unit_height, 1);
                GameObject obj(pos, size, Resources::GetTexture("wood_container"));
                obj.IsSolid = true;
                this->Start=obj;
                this->Cubes.push_back(obj);
            }
            else if (tileData[y][x] == 2) // end point
            {
                glm::vec3 pos(unit_width * x, unit_height * y, 0);
                glm::vec3 size(unit_width, unit_height, 1);
                GameObject obj(pos, size, Resources::GetTexture("gift_wrap"), glm::vec3(1.f, 1.f, 1.f));
                obj.IsSolid = true;
                this->End=obj;
                this->Cubes.push_back(obj);
            }
            else if (tileData[y][x] >2)	// non-solid; now determine its color based on level data
            {
                glm::vec3 color = glm::vec3(0.87f,0.72f,0.53f); // original: white

                glm::vec3 pos(unit_width * x, unit_height * y, 0);
                glm::vec3 size(unit_width, unit_height, 1);
                this->Cubes.push_back(GameObject(pos, size, Resources::GetTexture("wood_container")));
            }
        }
    }
}