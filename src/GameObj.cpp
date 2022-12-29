//
// Created by Ze Pan on 11/30/22.
//
#include "GameObj.h"
GameObject::GameObject()
: Position{0.f,0.f,0.f}, Size{1.0f, 1.0f,1.0f}, Velocity{0.0f}, Color{1.0f}, Rotation{0.0f}, Box{}, IsSolid{false}, Destroyed{false} { };

GameObject::GameObject(glm::vec3 pos, glm::vec3 size, Texture box, glm::vec3 color, glm::vec3 velocity)
        : Position{pos}, Size{size}, Velocity{velocity}, Color{color}, Rotation{0.0f}, Box{box}, IsSolid(false), Destroyed(false) { };

void GameObject::Draw(BoxRenderer &renderer,Texture& depthMap, glm::mat4 light, glm::vec3 camPos, glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
    renderer.DrawBox(this->Box, depthMap, light, camPos,viewMatrix, projMatrix, this->Position, this->Color, this->Size, this->Rotation);
}

void GameObject::Draw(ShadowRenderer &renderer,glm::vec3 camPos, glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
    renderer.DrawBox(this->Box, camPos,viewMatrix, projMatrix, this->Position, this->Color, this->Size, this->Rotation);
}